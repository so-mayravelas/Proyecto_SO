using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Juego_version_1
{
    public partial class Form1 : Form
    {
        List<Partida> Partidas = new List<Partida>();
        List<String> ListaConectados = new List<String>();
        delegate void DelegadoGrid(List<String> Conectados);
        delegate void DelegadoIS();
        delegate void DelegadoPreChat(int ID);
        delegate void DelegadoChat(string usuario, string comentario);
        delegate void DelegadoInvitacion(string partida, string usuario);
        String MiUsuario, invitador;
        Socket server;
        Thread atender;
        int num, idpartidainvitacion, iseleccionado = 0;
        bool loged = false, conectado = false;
        public Form1()
        {         
            InitializeComponent();
            Consultas_groupBox1.Visible = false;
            groupBoxInvitacion.Visible = false;
            groupBoxChat.Visible = false;
            //CheckForIllegalCrossThreadCalls = false;

            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.56.102");
            IPEndPoint ipep = new IPEndPoint(direc, 9020);
            Consultas_groupBox1.Visible = false;

            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                conectado = true;

            }
            catch (SocketException)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }
            ThreadStart ts = delegate { AtenderServidor(); };
            atender = new Thread(ts);
            atender.Start();

        }

        private void Conectar_button1_Click(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.56.102");
            IPEndPoint ipep = new IPEndPoint(direc, 9020);

            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                conectado = true;
                ThreadStart ts = delegate { AtenderServidor(); };
                atender = new Thread(ts);
                atender.Start();
            }
            catch (SocketException)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }

        }
        //Nos desconectamos del servidor
        private void Desconectar_button2_Click(object sender, EventArgs e)
        {
            // Se terminó el servicio. 
            string mensaje = "0/";

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            if (conectado == true)
                server.Send(msg);
            loged = false;
            Consultas_groupBox1.Visible = false;
            if (conectado == true)
            {
                server.Shutdown(SocketShutdown.Both);
                server.Close();
                atender.Abort();
            }
            conectado = false;
            // Nos desconectamos
            this.BackColor = Color.Silver;
        }
        //Para que un usuario se pueda registrar
        private void Registro_button3_Click(object sender, EventArgs e)
        {
            //Cuando un usuario quiera registrarse le tendremos que agregar a la BBDD 
            string mensaje = "2/" + Convert.ToString(usuario_textBox1.Text) + "/" +  Convert.ToString(contraseña_textBox2.Text);
            // Enviamos al servidor el usuario que queremos registrar y guardar en BBDD
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            if (conectado == true)
                server.Send(msg);

        }

        //Si ya estamos registardos o nos acabos de registra ya podemos ingresar ya estaremso dados de alta en la BBDD
        private void Iniciar_button4_Click(object sender, EventArgs e)
        {
            if (usuario_textBox1.Text != "" && contraseña_textBox2.Text != "")
            {
                // Quiere realizar un inicio de sesión
                MiUsuario = Convert.ToString(usuario_textBox1.Text);
                string mensaje = "1/" + Convert.ToString(usuario_textBox1.Text) + "/" + Convert.ToString(contraseña_textBox2.Text);
                // Enviamos al servidor el nombre del usuario y la contraseña
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                if (conectado == true)
                    server.Send(msg);
            }

        }

        private void enviar_button5_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;

            if (Consulta_Galder.Checked == true && loged==true)
            {
                // Realizamos la consulta escogida
                mensaje = "3/" + Convert.ToString(nombre_textBox3.Text);
                // Enviamos al servidor el nombre del usuario
                msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                if (conectado == true)
                    server.Send(msg);
            }
            else if (Consulta_Mayra.Checked == true && loged == true)
            {
                // Quiere realizar la consulta escogida
                mensaje = "4/" + Convert.ToString(nombre_textBox3.Text);
                // Enviamos al servidor el nombre del usuario
                msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

            }
            else if (Consulta_Andoni.Checked == true && loged == true)
            {
                // Quiere realizar la consulta escogida
                mensaje = "5/" + Convert.ToString(nombre_textBox3.Text) + "/" + Convert.ToString(TBConsultaAndoni.Text);
                // Enviamos al servidor los nombres de usuario
                msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                if (conectado == true)
                    server.Send(msg);

            }

            else if (Servicios.Checked==true && loged == true)
            {
                // Quiere realizar la consulta escogida
                mensaje = "6/";
                // Enviamos al servidor los nombres de usuario
                msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                if (conectado == true)
                    server.Send(msg);

            }

            else
            {
                MessageBox.Show("Inicie sesion para hacer alguna consulta");
            }
            
        }
        private void AtenderServidor()
        {
            if (conectado == true)
            {
                while (true)
                {
                    byte[] msg = new byte[80];
                    string mensajeC;
                    string[] mensaje;
                    int identificador;
                    server.Receive(msg);
                    mensajeC = Encoding.ASCII.GetString(msg).Split('\0')[0];
                    mensaje = mensajeC.Split('/');
                    if (mensaje[0] != "")
                    {
                        identificador = Convert.ToInt32(mensaje[0]);
                        switch (identificador)
                        {
                            case 1://log in

                                if (mensaje[1].Equals("si"))
                                {
                                    loged = true;
                                    DelegadoIS delegadoIS = new DelegadoIS(SesionIniciada);
                                    ConectadosGrid.Invoke(delegadoIS);
                                }
                                else
                                {
                                    MessageBox.Show("No has iniciado sesion correctamente");
                                }
                                break;
                            case 2://registrarse


                                if (mensaje[1] == "si")
                                {
                                    MessageBox.Show("Te has registrado correctamente");
                                }
                                else
                                {
                                    MessageBox.Show("Error: Usuario ya en uso");
                                }
                                break;
                            case 3://servicio Galder
                                string lista = "";


                                for (int i = 1; i < mensaje.Length; i++)
                                {

                                    lista = lista + mensaje[i] + "\n";
                                }
                                MessageBox.Show(lista);
                                break;
                            case 4://servicio Mayra

                                MessageBox.Show(mensaje[1]);
                                break;
                            case 5://servicio Andoni

                                MessageBox.Show(mensaje[1]);
                                break;
                            case 6://cuantos servicios

                                MessageBox.Show(mensaje[1]);
                                break;
                            case 7://Lista clientes
                                List<String> Conectados = new List<String>();
                                Conectados.Clear();
                                for (int i = 1; i < mensaje.Length && mensaje[i] != ""; i++)
                                {
                                    if (mensaje[i] != MiUsuario)
                                        Conectados.Add(mensaje[i]);
                                }

                                DelegadoGrid delegadoDG = new DelegadoGrid(RellenarDataGrid);
                                ConectadosGrid.Invoke(delegadoDG, new object[] {Conectados});
                                break;
                            case 8://Invitaciones
                                int subidentificador = Convert.ToInt32(mensaje[1]);
                                if (subidentificador == 1)
                                {
                                    DelegadoInvitacion delegadoInv = new DelegadoInvitacion(mostrarInvitacion);
                                    ConectadosGrid.Invoke(delegadoInv, new object[] { mensaje[2], mensaje[3] });
                                }
                                else if (subidentificador == 2)
                                {
                                    if (mensaje[3] != MiUsuario)
                                    {
                                        AñadirAPrtida(Convert.ToInt32(mensaje[2]), MiUsuario, mensaje[3]);
                                        DelegadoPreChat DelegadoPC = new DelegadoPreChat(PreparacionChat);
                                        ConectadosGrid.Invoke(DelegadoPC, new object[] { Convert.ToInt32(mensaje[2]) });
                                    }
                                }
                                else if (subidentificador == 3)
                                    MessageBox.Show(mensaje[3] + "ha rechazado la invitacion");
                                break;

                            case 9:
                                    DelegadoChat delegadoCha = new DelegadoChat(ActualizarChat);
                                    ConectadosGrid.Invoke(delegadoCha, new object[] { mensaje[2], mensaje[3] });
                                break;

                        }
                    }
                }
            }
        }
        public void SesionIniciada()
        {
            Consultas_groupBox1.Visible = true;
            MessageBox.Show("Has iniciado sesion correctamente");
        }
        //Funcion que actualiza la DataGrid con los Usuarios
        public void RellenarDataGrid(List<String> Conectados)
        {
            ListaConectados = Conectados;
            ConectadosGrid.DataSource = null; //Volvemos a rellenar el dataGrid
            ConectadosGrid.RowCount = ListaConectados.Count + 1; //Crea tantas filas como usuarios conectados hay
            ConectadosGrid.ColumnCount = 1; //Número de columnas
            ConectadosGrid.ColumnHeadersVisible = false;
            ConectadosGrid.RowHeadersVisible = false;
            //ConectadosGrid.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
            ConectadosGrid.Rows[0].Cells[0].Value = "Usuario";   //Asignamos titulos a las celdas

            for (int i = 0; i < ListaConectados.Count(); i++) //Rellenamos la tabla con los Usuarios
            {
                ConectadosGrid.Rows[i + 1].Cells[0].Value = ListaConectados[i];
            }
        }
        public void mostrarInvitacion(string partida, string usuario)
        {
            idpartidainvitacion = Convert.ToInt32(partida);
            if (usuario != MiUsuario)
            {
                groupBoxInvitacion.Visible = true;
                invitador = usuario;
                labelInvitacion.Text = usuario + " te ha invitado";
            }
        }
        //Guardamos el usuario que hemos seleccionado en la DataGrid
        private void ConectadosGrid_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            ConectadosGrid.Rows[num].Cells[0].Style.BackColor = Color.White;
            num = e.RowIndex; //Vector de filas
            ConectadosGrid.Rows[num].Cells[0].Style.BackColor = Color.Green; //La celda seleccionada se pondrá de color azul
            ConectadosGrid.ClearSelection();
            iseleccionado = num; //Nos da la posición del avión seleccionado en el dataGrid
        }
        //Enviamos una invitacion al usuario seleccionado
        private void InvitarButton_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            if (loged == true) //Solo si no se seleccionan los títulos (posición 0)
            {
                // Quiere realizar la consulta escogida
                MessageBox.Show(iseleccionado.ToString());
                mensaje = "8/1/-1/" + ListaConectados[iseleccionado-1];
                // Enviamos al servidor los nombres de usuario
                labelInvitacion.Text = mensaje;
                msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                if (conectado == true)
                    server.Send(msg);
            }
            else
                MessageBox.Show("Elige el usuario al que quieres invitar", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        public void AñadirAPrtida(int ID, String miusuario, String usuario)
        {
            bool existe = false;
            for (int i = 0; i < Partidas.Count; i++)
            {
                if (Partidas[i].DameID() == ID)
                {
                    if (Partidas[i].ExixteParticipante(miusuario) == false)
                        Partidas[i].AñadirParticipante(miusuario);
                    if (Partidas[i].ExixteParticipante(usuario) == false)
                        Partidas[i].AñadirParticipante(usuario);
                    existe = true;
                }
            }
            if (existe == false)
            {
                Partida p = new Partida();
                p.PonID(ID);
                p.AñadirParticipante(miusuario);
                p.AñadirParticipante(usuario);
                Partidas.Add(p);
            }
        }

        private void buttonAceptar_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            AñadirAPrtida(Convert.ToInt32(idpartidainvitacion), MiUsuario, invitador);
            mensaje = "8/2/" + Convert.ToString(idpartidainvitacion) + "/" + MiUsuario;
            MessageBox.Show("El mensaje es:" + mensaje);
            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            if (conectado == true)
                server.Send(msg);
            groupBoxInvitacion.Visible = false;
            groupBoxChat.Visible = true;
            PreparacionChat(idpartidainvitacion);
        }

        private void buttonRechazar_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            mensaje = "8/3/" + Convert.ToString(idpartidainvitacion) + "/" + invitador;
            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            if (conectado == true)
                server.Send(msg);
            groupBoxInvitacion.Visible = false;
        }

        private void buttonChat_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            mensaje = "9/" + Convert.ToString(idpartidainvitacion) + "/" + MiUsuario + "/" + Convert.ToString(textBoxComentario.Text);
            textBoxChat.Text = MiUsuario + ": " + Convert.ToString(textBoxComentario.Text) + Environment.NewLine;
            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            if (conectado == true)
                server.Send(msg);
        }

        public void PreparacionChat(int ID)
        {
            groupBoxChat.Visible = true;
            labelChat.Text = "Partida: " + Convert.ToString(ID);
        }

        public void ActualizarChat(string Usuario, string comentario)
        {
            textBoxChat.Text = textBoxChat.Text+ Usuario + ": " + comentario + Environment.NewLine;
        }

    }
}

