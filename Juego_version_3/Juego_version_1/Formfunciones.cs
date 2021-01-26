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
using FontAwesome.Sharp;

namespace Juego_version_1
{
    public partial class Formfunciones : Form
    {
        List<Partida> Partidas = new List<Partida>();
        List<String> ListaConectados = new List<String>();
        List<FormSalaPartida> formularios = new List<FormSalaPartida>();
        delegate void DelegadoGrid(List<String> Conectados);
        delegate void DelegadoIS();
        delegate void DelegadoPreChat(int ID);
        delegate void DelegadoChat(string usuario, string comentario);
        delegate void DelegadoInvitacion(string partida, string usuario);
        String MiUsuario, invitador;
        Socket server;
        Thread atender;
        Thread crearForm;
        private static Mutex mut = new Mutex();
        int num, idpartidainvitacion, iseleccionado = 0;
        bool loged = false, conectado = false;
        List<String> Conectados = new List<String>();


        public Formfunciones()
        {         
            InitializeComponent();
            Consultas_groupBox1.Visible = false;
            groupBoxInvitacion.Visible = false;
            groupBoxChat.Visible = false;
            OcultarRegistro();
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
                    int numPartida;
                    int ronda;
                    string caso;
                    int apuesta;
                    int jugador;
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
                                Conectados.Clear();
                                for (int i = 1; i < mensaje.Length && mensaje[i] != ""; i++)
                                {
                                    if (mensaje[i] != MiUsuario)
                                        Conectados.Add(mensaje[i]);
                                }

                                DelegadoGrid delegadoDG = new DelegadoGrid(RellenarDataGrid);
                                ConectadosGrid.Invoke(delegadoDG, new object[] {Conectados});
                                for(int i=0;i<formularios.Count;i++)
                                formularios[i].ActualizarJugadores(Conectados);
                                break;
                            case 8://Invitaciones
                                int subidentificador = Convert.ToInt32(mensaje[1]);
                                if (subidentificador == 1)
                                {
                                    DelegadoInvitacion delegadoInv = new DelegadoInvitacion(mostrarInvitacion);
                                    ConectadosGrid.Invoke(delegadoInv, new object[] { mensaje[2], mensaje[3] });
                                    CrearPartida(mensaje[3], Convert.ToInt32(mensaje[2]));
                                    if (mensaje[3] == MiUsuario)
                                    {
                                        ThreadStart ts = delegate { CrearForm(Convert.ToInt32(mensaje[2]), server); };
                                        crearForm = new Thread(ts);
                                        crearForm.Start();
                                        Thread.Sleep(2500);
                                        ActualizarPartidasEnForms(Convert.ToInt32(mensaje[2]));
                                        for (int i = 0; i < formularios.Count; i++)
                                            formularios[i].ActualizarJugadores(Conectados);
                                    }
                                }
                                else if (subidentificador == 2)
                                {
                                    if (mensaje[3] != "lleno")
                                    {

                                        if (mensaje[3] == MiUsuario)
                                        {
                                            MessageBox.Show("miUsuario==" + mensaje[3]);
                                            ThreadStart ts = delegate { CrearForm(Convert.ToInt32(mensaje[2]), server); };
                                            crearForm = new Thread(ts);
                                            crearForm.Start();
                                            Thread.Sleep(1500);
                                            DelegadoPreChat DelegadoPC = new DelegadoPreChat(PreparacionChat);
                                            ConectadosGrid.Invoke(DelegadoPC, new object[] { Convert.ToInt32(mensaje[2]) });
                                        }


                                    }
                                    else
                                    {
                                        MessageBox.Show("La partida esta llena");
                                    }

                                }
                                else if (subidentificador == 3)
                                    MessageBox.Show(mensaje[3] + "ha rechazado la invitacion");
                                else if (subidentificador == 6)
                                {
                                    Partida p = new Partida();
                                    p.PonID(Convert.ToInt32(mensaje[2]));

                                    if (mensaje[3] != "")
                                    {
                                        p.AñadirParticipante(mensaje[3], 0);
                                    }
                                    if (mensaje[4] != "")
                                    {
                                        p.AñadirParticipante(mensaje[4], 1);
                                    }
                                    if (mensaje[5] != "")
                                    {
                                        p.AñadirParticipante(mensaje[5], 2);
                                    }
                                    if (mensaje[6] != "")
                                    {
                                        p.AñadirParticipante(mensaje[6], 3);
                                    }
                                    Partidas[Convert.ToInt32(mensaje[2])] = p;
                                    Thread.Sleep(1000);
                                    ActualizarPartidasEnForms(Convert.ToInt32(mensaje[2]));
                                    formularios[Convert.ToInt32(mensaje[2])].ActualizarJugadores(Conectados);
                                    
                                }
                                else if (subidentificador == 7)
                                {
                                    var resultado = MessageBox.Show("Deseas Cambiar el lugar con el jugador en la posicion" + Convert.ToInt32(mensaje[3]), "Cambiar Posicion", MessageBoxButtons.OKCancel);
                                    if (resultado == DialogResult.OK)
                                    {

                                        mensajeC = "8/7/" + mensaje[2] + "/" + mensaje[3] + "/" + mensaje[4];

                                        // Enviamos al servidor los nombres de usuario
                                        msg = System.Text.Encoding.ASCII.GetBytes(mensajeC);
                                        server.Send(msg);
                                    }
                                }
                                else if (subidentificador == 8)
                                {
                                    formularios[Convert.ToInt32(mensaje[2])].EmpezarPartida();
                                }
                                break;

                            case 9:
                                    DelegadoChat delegadoCha = new DelegadoChat(ActualizarChat);
                                    ConectadosGrid.Invoke(delegadoCha, new object[] { mensaje[2], mensaje[3] });
                                break;
                            case 10:
                                numPartida = Convert.ToInt32(mensaje[1]);
                                ronda = Convert.ToInt32(mensaje[2]);
                                formularios[numPartida].Ronda(ronda);
                                switch (ronda)
                                {

                                    case 0:
                                        formularios[numPartida].CambiarBotones(0);
                                        break;
                                    case 1:
                                        formularios[numPartida].CambiarBotones(1);
                                        break;
                                    case 2:
                                        if (mensaje[3] == "P")
                                        {
                                            apuesta = 0;
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(3);
                                        }
                                        else
                                        {
                                            apuesta = Convert.ToInt32(mensaje[4]);
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(4);
                                        }
                                        break;
                                    case 3:
                                        if (mensaje[3] == "P")
                                        {
                                            apuesta = 0;
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(3);
                                        }
                                        else
                                        {
                                            apuesta = Convert.ToInt32(mensaje[4]);
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(4);
                                        }
                                        break;
                                    case 4:
                                        formularios[numPartida].CambiarBotones(2);
                                        break;
                                    case 5:
                                        if (mensaje[3] == "P")
                                        {
                                            apuesta = 0;
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(3);
                                        }
                                        else
                                        {
                                            apuesta = Convert.ToInt32(mensaje[4]);
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(4);
                                        }
                                        break;
                                    case 6:
                                        formularios[numPartida].CambiarBotones(2);
                                        break;
                                    case 7:
                                        if (mensaje[3] == "P")
                                        {
                                            apuesta = 0;
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(3);
                                        }
                                        else
                                        {
                                            apuesta = Convert.ToInt32(mensaje[4]);
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(4);
                                        }
                                        break;
                                    case 8:
                                        if (mensaje[3] == "P")
                                        {
                                            apuesta = 0;
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(3);
                                        }
                                        else
                                        {
                                            apuesta = Convert.ToInt32(mensaje[4]);
                                            formularios[numPartida].valorapuesta(apuesta);
                                            formularios[numPartida].CambiarBotones(4);
                                        }
                                        break;
                                }
                                break;
                            case 11:
                                numPartida = Convert.ToInt32(mensaje[1]);
                                ronda = Convert.ToInt32(mensaje[2]);
                                switch (ronda)
                                {
                                    case 0:
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador, ronda);
                                        break;
                                    case 1:
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador,ronda);
                                        break;
                                    case 2:
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador, ronda);
                                        break;
                                    case 3:
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador, ronda);
                                        break;
                                    case 4:
                                        caso = mensaje[3];
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador, ronda);
                                        break;
                                    case 5:
                                        caso = mensaje[3];
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador, ronda);
                                        break;
                                    case 6:
                                        caso = mensaje[3];
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador, ronda);
                                        break;
                                    case 7:
                                        caso = mensaje[3];
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador, ronda);
                                        break;
                                    case 8:
                                        caso = mensaje[3];
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador, ronda);
                                        break;
                                    case 11:
                                        for (int i = 0; i < 4; i++)
                                        {
                                            int[] cartas = { Convert.ToInt32(mensaje[3+i*4]), Convert.ToInt32(mensaje[4 + i * 4]), Convert.ToInt32(mensaje[5 + i * 4]), Convert.ToInt32(mensaje[6 + i * 4]) };
                                            formularios[numPartida].Repartir(i, cartas);
                                        }

                                        formularios[numPartida].Cartas(0);
                                        break;
                                    case 12:
                                        int[] puntos = { Convert.ToInt32(mensaje[3]), Convert.ToInt32(mensaje[4]), Convert.ToInt32(mensaje[5]), Convert.ToInt32(mensaje[6]) };
                                        formularios[numPartida].puntuaciones(puntos);
                                        break;
                                    case 20://Gana la Pareja 0
                                        break;
                                    case 21://Gana la Pareja 1
                                        break;
                                }
                                break;
                        }
                    }
                }
            }
        }
        public void CrearForm(int numPartida, Socket sock)
        {
            FormSalaPartida frm = new FormSalaPartida(numPartida,sock,MiUsuario);
            formularios.Add(frm);
            frm.ShowDialog();


        }
        public void ActualizarPartidasEnForms(int numPartida)
        {
            formularios[numPartida].ActualizacionPartida(Partidas[numPartida]);

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

                mensaje = "8/1/-1/" + ListaConectados[iseleccionado - 1];
                // Enviamos al servidor los nombres de usuario
                labelInvitacion.Text = mensaje;
                msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                if (conectado == true)
                    server.Send(msg);
            }
            else

            {
                DialogResult opcion = MessageBox.Show("Elige el usuario al que quieres invitar", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Information);


            }
        }

        public void AñadirAPartida(String miusuario, int numPartida)
        {
            for (int i = 0; i < 4; i++) {
                if (Partidas[numPartida].DameParticipante(1) == "")
                {
                    Partidas[numPartida].AñadirParticipante(miusuario,1);
                }
                else if (Partidas[numPartida].DameParticipante(2) == "")
                {
                    Partidas[numPartida].AñadirParticipante(miusuario, 2);
                }
                else if (Partidas[numPartida].DameParticipante(3) == "")
                {
                    Partidas[numPartida].AñadirParticipante(miusuario, 3);
                }
                else if(Partidas[numPartida].DameParticipante(4) == "")
                {
                    Partidas[numPartida].AñadirParticipante(miusuario, 4);
                }
            }
        }
        public void CrearPartida(String miusuario, int numPartida)
        {

                Partida p = new Partida();
                p.PonID(numPartida);
                p.AñadirParticipante(miusuario, numPartida);
                Partidas.Add(p);

        }
        private void buttonAceptar_Click(object sender, EventArgs e)
        {

            string mensaje;
            byte[] msg;
            AñadirAPartida(MiUsuario,Convert.ToInt32(idpartidainvitacion));
            mensaje = "8/2/" + Convert.ToString(idpartidainvitacion) + "/" + MiUsuario;

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

        private void ConectadosGrid_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        //para poder hacer el chat 
        //tenemos que pasar el chat entre partidas 
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


        private void FormFunciones_Load(object sender, EventArgs e)
        {
            this.Hide();

            
        }

        //Lo que tenemos que esconder para llamar a cada momento 

        private void OcultarRegistro()
        {
            Conectar_button1.Visible = false;
            Desconectar_button2.Visible = false;
            /*Consultas_groupBox1.Visible = false;
            groupBoxChat.Visible = false;
            label5.Visible = false;
            InvitarButton.Visible = false;
            Consultas_groupBox1.Visible = false;
            ConectadosGrid.Visible = false;
            InvitarButton.Visible = false;*/
        }
        private void MostrarInicio()
        {
            Iniciar_button4.Visible = true;
            Registro_button3.Visible = false;
        }

        private void Mostrarperfil()
        {
            ConectadosGrid.Visible = true;
            groupBoxInvitacion.Visible = true;

        
        }


    }
}

