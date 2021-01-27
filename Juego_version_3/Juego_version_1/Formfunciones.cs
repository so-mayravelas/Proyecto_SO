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
using System.Runtime.InteropServices;


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
       
        
        public Formfunciones()
        {         
            InitializeComponent();
            Consultas_groupBox1.Visible = false;
            groupBoxInvitacion.Visible = false;
            groupBoxChat.Visible = false;
            OcultarRegistro();
            BordeBotones();
            //CheckForIllegalCrossThreadCalls = false;

            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.56.102");
            IPEndPoint ipep = new IPEndPoint(direc, 9050);
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
            IPEndPoint ipep = new IPEndPoint(direc, 9050);

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
            #region Datos Validos 

            if (usuario1_textBox1.Text == "NOMBRE DE JUGADOR " || contraseñaA_textBox2.Text == "PASSWORD" || ContraseñaB_textBox1.Text == "REPETIR PASSWORD")
            {
                MessageBox.Show("Rellena todos los campos correctamente");
                return;
            }
            if (contraseñaA_textBox2.Text != ContraseñaB_textBox1.Text)
            {
                MessageBox.Show("Los passwords deben coindicir");
                return;
            }
            #endregion

            //Cuando un usuario quiera registrarse le tendremos que agregar a la BBDD 
            string mensaje = "2/" + Convert.ToString(usuario1_textBox1.Text) + "/" +  Convert.ToString(contraseñaA_textBox2.Text);
            // Enviamos al servidor el usuario que queremos registrar y guardar en BBDD
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            if (conectado == true)
                server.Send(msg);

        }

        //Si ya estamos registardos o nos acabos de registra ya podemos ingresar ya estaremso dados de alta en la BBDD
        private void Iniciar_button4_Click(object sender, EventArgs e)
        {
            #region Validar Datos
            if (usuario_textBox1.Text != "USUARIO")
            {
                if (contraseña_textBox2.Text != "CONTRASEÑA")
                {

                }
                else msgError("Introducir la Contraseña");

            }
            else msgError("Introducir nombre de Usuario");
            #endregion
            // Quiere realizar un inicio de sesión
            MiUsuario = Convert.ToString(usuario_textBox1.Text);
                string mensaje = "1/" + Convert.ToString(usuario_textBox1.Text) + "/" + Convert.ToString(contraseña_textBox2.Text);
                // Enviamos al servidor el nombre del usuario y la contraseña
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                if (conectado == true)
                    server.Send(msg);
            panelPantallaJugador.Show();
            label9.Text = usuario_textBox1.Text;
            label7.Text = usuario_textBox1.Text;
            

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
                        MessageBox.Show("El mensaje es:" + mensajeC);
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
                                    CrearPartida(mensaje[3], Convert.ToInt32(mensaje[2]));
                                    if (mensaje[3] == MiUsuario)
                                    {
                                        ThreadStart ts = delegate { CrearForm(Convert.ToInt32(mensaje[2]), server); };
                                        crearForm = new Thread(ts);
                                        crearForm.Start();
                                        Thread.Sleep(150);
                                        ActualizarPartidasEnForms(Convert.ToInt32(mensaje[2]));
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
                                            Thread.Sleep(100);
                                        }

                                        AñadirAPartida(mensaje[3], Convert.ToInt32(mensaje[2]));
                                        ActualizarPartidasEnForms(Convert.ToInt32(mensaje[2]));

                                        DelegadoPreChat DelegadoPC = new DelegadoPreChat(PreparacionChat);
                                        ConectadosGrid.Invoke(DelegadoPC, new object[] { Convert.ToInt32(mensaje[2]) });
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
                                    ActualizarPartidasEnForms(Convert.ToInt32(mensaje[2]));
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
                                caso = mensaje[3];
                                switch (ronda)
                                {

                                    case 0:
                                        if (caso == "P")
                                        {
                                            formularios[numPartida].CambiarBotones(0);
                                        }
                                        else
                                        {
                                            formularios[numPartida].CambiarBotones(1);
                                        }
                                        break;
                                    case 1:
                                    case 2:
                                        apuesta = Convert.ToInt32(caso);
                                        if (apuesta == 0)
                                        {
                                            formularios[numPartida].CambiarBotones(3);
                                        }
                                        else
                                        {
                                            formularios[numPartida].CambiarBotones(4);
                                        }
                                        break;
                                    case 3:
                                    case 4:
                                        apuesta = Convert.ToInt32(mensaje[4]);
                                        if (caso == "P")
                                        {
                                            formularios[numPartida].CambiarBotones(1);
                                        }
                                        else
                                        {
                                            if (apuesta == 0)
                                            {
                                                formularios[numPartida].CambiarBotones(3);
                                            }
                                            else
                                            {
                                                formularios[numPartida].CambiarBotones(4);
                                            }
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
                                    case 3:
                                    case 4:
                                        caso = mensaje[3];
                                        jugador = Convert.ToInt32(mensaje[4]);
                                        formularios[numPartida].Bocatas(mensaje[5], jugador);
                                        break;
                                    case 1:
                                    case 2:
                                        jugador = Convert.ToInt32(mensaje[3]);
                                        formularios[numPartida].Bocatas(mensaje[4], jugador);
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
            Consultas_groupBox1.Visible = false;
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


        //Lista de botones 


        private void Conectar_iconButton1_Click(object sender, EventArgs e)
        {
            ActivarBoton(sender, RGBColors.color5);
            #region Conectar con el servidor por el boton
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.56.102");
            IPEndPoint ipep = new IPEndPoint(direc, 9050);

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
            #endregion


        }

        private void Desconectar_iconButton1_Click(object sender, EventArgs e)
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

        private void Registrarse_iconButton1_Click(object sender, EventArgs e)
        {
            ActivarBoton(sender, RGBColors.color1);
            panelRegistro.Show();
            OcultarRegistro();
            panelRegistro.Visible = true;

        }

        private void FormFunciones_Load(object sender, EventArgs e)
        {
            this.Hide();

            
        }


        #region OCULTACIONES 
        //Lo que tenemos que esconder para llamar a cada momento 

        private void OcultarRegistro()
        {
            Conectar_button1.Visible = false;
            Desconectar_button2.Visible = false;
            panelIniciarSesion.Visible = false;
            panelRegistro.Visible = false;
            panelPantallaJugador.Visible = false;




        }
        private void MostrarInicio()
        {
            Iniciar_button4.Visible = true;
            Registrar_button1.Visible = false;
        }

        private void Mostrarperfil()
        {
            ConectadosGrid.Visible = true;
            groupBoxInvitacion.Visible = true;

        
        }
        #endregion

        //lISTA DE BOTONES 



#region Funciones para el Formulario Principal 
        //Para poder arrastrar el formulario 
        [DllImport("user32.DLL", EntryPoint = "ReleaseCapture")]
        private extern static void ReleaseCapture();
        [DllImport("user32.DLL", EntryPoint = "SendMessage")]
        private extern static void SendMessage(System.IntPtr hwnd, int wmsg, int wparam, int lparam);

        //Para poder Redimensionar el formulario durante la ejecucion
        private int tolerance = 12;
        private const int WM_NCHITTEST = 132;
        private const int HTBOTTONRINGHT = 17;
        private Rectangle sizeGripRectangle;

        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)

            {
                case WM_NCHITTEST:
                    base.WndProc(ref m);
                    var hitPoint = this.PointToClient(new Point(m.LParam.ToInt32() & 0xffff, m.LParam.ToInt32() >> 16));
                    if (sizeGripRectangle.Contains(hitPoint))
                        m.Result = new IntPtr(HTBOTTONRINGHT);
                    break;
                default:
                    base.WndProc(ref m);
                    break;


            }


        }

        //Para dibujar el rectangulo

        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);
            var region = new Region(new Rectangle(0, 0, this.ClientRectangle.Width, this.ClientRectangle.Height));

            sizeGripRectangle = new Rectangle(this.ClientRectangle.Width - tolerance, this.ClientRectangle.Height - tolerance, tolerance, tolerance);

            region.Exclude(sizeGripRectangle);
            this.panelContenedor.Region = region;
            this.Invalidate();

        }

        //Para el color y el grip del rect inferiro

        protected override void OnPaint(PaintEventArgs e)
        {
            SolidBrush blueBush = new SolidBrush(Color.FromArgb(244, 244, 244));
            e.Graphics.FillRectangle(blueBush, sizeGripRectangle);
            //base.OnPaint(e);
            //ControlPaint.DrawSizeGrip(e.Graphics,Color.Transparent,sizeGripRectangle);

        }
        //Para cerrar el form
        private void Cerrar_iconButton1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        //para minimizar el form

        //Para los botns de cerrar/max/mins sigan al formulario
        int lx, ly;
        int sw, sh;

        //Restaurar
        private void Rests_iconButton1_Click(object sender, EventArgs e)
        {
            Rests_iconButton1.Visible = false;
            Maxi_iconButton2.Visible = true;
            this.Size = new Size(sw, sh);
            this.Location = new Point(lx, ly);
        }
        //Para arrastrar el form desde los paneles
        private void panelTitulo_MouseMove(object sender, MouseEventArgs e)
        {
            ReleaseCapture();
            SendMessage(this.Handle, 0x112, 0xf012, 0);
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            ReleaseCapture();
            SendMessage(this.Handle, 0x112, 0xf012, 0);
        }

        private void Mini_iconButton3_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        //Para maximizar
        private void Maxi_iconButton2_Click(object sender, EventArgs e)
        {

            lx = this.Location.X;
            ly = this.Location.Y;
            sw = this.Size.Width;
            sh = this.Size.Height;
            Rests_iconButton1.Visible = true;
            Maxi_iconButton2.Visible = false;
            this.Size = Screen.PrimaryScreen.WorkingArea.Size;
            this.Location = Screen.PrimaryScreen.WorkingArea.Location;
        }

        #endregion

      #region ABRIR FORMULARIOS
        //METODO PARA ABRIR FORMULARIOS DENTRO DE NUESTRO PANEL PANTALLA PRINCIPAL
        private void AbrirFormulario<MiForm>() where MiForm : Form, new()
        {
            Form formulario;
            //Buscamos en la coleccion el formulario
            formulario = panelFormulario.Controls.OfType<MiForm>().FirstOrDefault();
            //En caso que el formulario no existiera

            if (formulario == null)
            {
                formulario = new MiForm();
                formulario.TopLevel = false;
                panelFormulario.Controls.Add(formulario);
                panelFormulario.Tag = formulario;
                formulario.BringToFront();
                formulario.Show();
                //quitamos el borde al formulario y lo acoplamos al panel
                formulario.FormBorderStyle = FormBorderStyle.None;
                formulario.Dock = DockStyle.Fill;
            }
            //En caso que el formulario si existiera
            else
            {
                formulario.BringToFront();
            }


        }

        private void IniSe_iconButton2_Click(object sender, EventArgs e)
        {
            ActivarBoton(sender, RGBColors.color2);
            //Lamaremos a nuestro panel
            panelIniciarSesion.Show();
            

        }

        #endregion

        #region ResaltarBotones
        //PARA RESALTAR LOS BOTONES 
        private IconButton currentBtn;
        private Panel leftBorderBtn;

        private void BordeBotones()
        {
            leftBorderBtn = new Panel();
            leftBorderBtn.Size = new Size(7, 60);
            panelMenu.Controls.Add(leftBorderBtn);

        }

        private void ActivarBoton(object senderBtn, Color color)
        {
            if (senderBtn != null)
            {
                DesactivarBoton();
                currentBtn = (IconButton)senderBtn;
                currentBtn.BackColor = Color.FromArgb(37, 36, 81);
                currentBtn.ForeColor = color;
                currentBtn.TextAlign = ContentAlignment.MiddleCenter;
                currentBtn.IconColor = color;
                currentBtn.TextImageRelation = TextImageRelation.TextBeforeImage;
                currentBtn.ImageAlign = ContentAlignment.MiddleRight;

                leftBorderBtn.BackColor = color;
                leftBorderBtn.Location = new Point(0, currentBtn.Location.Y);
                leftBorderBtn.Visible = true;
                leftBorderBtn.BringToFront();
            }
        }



        private void DesactivarBoton()
        {
            if (currentBtn != null)
            {
                currentBtn.BackColor = Color.FromArgb(31, 30, 68);
                currentBtn.ForeColor = Color.Gainsboro;
                currentBtn.TextAlign = ContentAlignment.MiddleLeft;
                currentBtn.IconColor = Color.Gainsboro;
                currentBtn.TextImageRelation = TextImageRelation.ImageBeforeText;
                currentBtn.ImageAlign = ContentAlignment.MiddleLeft;
            }
        }

        private struct RGBColors
        {
            public static Color color1 = Color.FromArgb(172, 126, 241);
            public static Color color2 = Color.FromArgb(249, 118, 176);
            public static Color color3 = Color.FromArgb(253, 138, 114);
            public static Color color4 = Color.FromArgb(249, 88, 155);
            public static Color color5 = Color.FromArgb(253, 138, 114);
        }



        #endregion



        #region REGISTRAR
        //Ocultar elementos de la pantalla para registro
        private void MostrarparaRegistro()
        {
            label5.Visible = false;
            label1.Visible = false;
            label4.Visible = false;
            usuario_textBox1.Visible = false;
            Desconectar_button2.Visible = false;
            Iniciar_button4.Visible = false;
            InvitarButton.Visible = false;
            groupBoxChat.Visible = false;
            groupBoxInvitacion.Visible = false;
            Consultas_groupBox1.Visible = false;
            contraseña_textBox2.Visible = false;
            ConectadosGrid.Visible = false;

        }

        private void Consulta_Galder_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void Consulta1_iconButton2_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            // Realizamos la consulta escogida
            mensaje = "3/" + Convert.ToString(nombre_textBox3.Text);
            // Enviamos al servidor el nombre del usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            if (conectado == true)
                server.Send(msg);
        }

        private void Consulta3_iconButton3_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            // Quiere realizar la consulta escogida
            mensaje = "4/" + Convert.ToString(nombre_textBox3.Text);
            // Enviamos al servidor el nombre del usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);
        }

        private void Consulta2_iconButton2_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            // Quiere realizar la consulta escogida
            mensaje = "5/" + Convert.ToString(nombre_textBox3.Text) + "/" + Convert.ToString(TBConsultaAndoni.Text);
            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            if (conectado == true)
                server.Send(msg);
        }

        private void DarBajar_iconButton6_Click(object sender, EventArgs e)
        {
            string baja = "20/";
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(baja);
            server.Send(msg);
        }

        private void fq_iconButton3_Click(object sender, EventArgs e)
        {

        }

        private void Instr_iconButton4_Click(object sender, EventArgs e)
        {
            ActivarBoton(sender, RGBColors.color4);
            AbrirFormulario<FormIntrucciones>();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            
            panelIniciarSesion.Show();
            panelRegistro.Hide();

        }

        //mouse sale del texto

        private void usuario1_textBox1_Enter(object sender, EventArgs e)
        {
            if (usuario1_textBox1.Text == "      Nombre de jugador")
            {
                usuario1_textBox1.Text = "";
                usuario1_textBox1.ForeColor = Color.Black;
            }
        }

        private void usuario1_textBox1_Leave_1(object sender, EventArgs e)
        {
            if (usuario1_textBox1.Text == "")
            {
                usuario1_textBox1.Text = "      Nombre de jugador";
                usuario1_textBox1.ForeColor = Color.DimGray;
            }
        }


        private void contraseñaA_textBox2_Enter(object sender, EventArgs e)
        {
            if (contraseñaA_textBox2.Text == "    PASSWORD")
            {
                contraseñaA_textBox2.Text = "";
                contraseñaA_textBox2.ForeColor = Color.Black;
                contraseñaA_textBox2.UseSystemPasswordChar = true;
            }
        }

        private void contraseñaA_textBox2_Leave(object sender, EventArgs e)
        {
            if (contraseñaA_textBox2.Text == "")
            {
                contraseñaA_textBox2.Text = "    PASSWORD";
                contraseñaA_textBox2.ForeColor = Color.DimGray;
                contraseñaA_textBox2.UseSystemPasswordChar = false;
            }
        }

        private void ContraseñaB_textBox1_Enter(object sender, EventArgs e)
        {
            if (ContraseñaB_textBox1.Text == "    REPETIR PASSWORD")
            {
                ContraseñaB_textBox1.Text = "";
                ContraseñaB_textBox1.ForeColor = Color.Black;
                ContraseñaB_textBox1.UseSystemPasswordChar = true;
            }
        }



        private void DarBajar_iconButton6_Click_1(object sender, EventArgs e)
        {
            string mensaje = "20/" + MiUsuario + "/";
            // Enviamos al servidor 
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);
            MessageBox.Show("Te has dado de baja correctamente");
            Desconectar_button2.PerformClick();
        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void Exit_FPusericonButton1_Click(object sender, EventArgs e)
        {
            panelPantallaJugador.Hide();
        }
        #region BOTONES DE CONSULTAS
        private void Consulta_Mayra_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void Consulta1_iconButton2_Click_1(object sender, EventArgs e)
        {
            Consultas_groupBox1.Visible = true;
            label10.Visible = false;
            TBConsultaAndoni.Visible = false;
            Consulta_Mayra.Visible = false;
            Consulta_Andoni.Visible = false;
            Servicios.Visible = false;
        }

        private void Consulta2_iconButton2_Click_1(object sender, EventArgs e)
        {
            Consultas_groupBox1.Visible = true;
            label10.Visible = false;
            TBConsultaAndoni.Visible = false;
            Servicios.Visible = false;
            Consulta_Galder.Visible = false;
            Consulta_Andoni.Visible = false;


        }

        private void Consulta3_iconButton3_Click_1(object sender, EventArgs e)
        {
            Consultas_groupBox1.Visible = true;
            label10.Visible = true;
            TBConsultaAndoni.Visible = true;
            Consulta_Mayra.Visible = false;
            Servicios.Visible = false;
            Consulta_Galder.Visible = false;
        }

        private void iconButton5_Click(object sender, EventArgs e)
        {
            Consultas_groupBox1.Visible = true;
            Consulta_Galder.Visible = false;
            label10.Visible = false;
            TBConsultaAndoni.Visible = false;
            Consulta_Mayra.Visible = false;
            Consulta_Andoni.Visible = false;

        }
        #endregion

        private void ContraseñaB_textBox1_Leave(object sender, EventArgs e)
        {
            if (ContraseñaB_textBox1.Text == "")
            {
                ContraseñaB_textBox1.Text = "    REPETIR PASSWORD";
                ContraseñaB_textBox1.ForeColor = Color.DimGray;
                ContraseñaB_textBox1.UseSystemPasswordChar = false;
            }
        }

        #endregion


       #region Panel Inciar Sesion 

        //Nos mostrara el mensaje de error de loguin
        private void msgError(string msg)
        {
            MensError_label.Text = "   " + msg;
            MensError_label.Visible = true;
        }


        // CONTRASEÑA 
        private void contraseña_textBox2_Enter(object sender, EventArgs e)
        {
            if (contraseña_textBox2.Text == "CONTRASEÑA")
            {
                contraseña_textBox2.Text = "";
                contraseña_textBox2.ForeColor = Color.LightGray;
                contraseña_textBox2.UseSystemPasswordChar = true;
            }
        }

        private void contraseña_textBox2_Leave(object sender, EventArgs e)
        {
            if (contraseña_textBox2.Text == "")
            {
                contraseña_textBox2.Text = "CONTRASEÑA";
                contraseña_textBox2.ForeColor = Color.DimGray;
                contraseña_textBox2.UseSystemPasswordChar = false;
            }
        }


        //USUARIO

        private void usuario_textBox1_Enter(object sender, EventArgs e)
        {
            if (usuario_textBox1.Text == "USUARIO")
            {
                usuario_textBox1.Text = "";
                usuario_textBox1.ForeColor = Color.LightGray;
            }
        }

        private void usuario_textBox1_Leave(object sender, EventArgs e)
        {
            if (usuario_textBox1.Text == "")
            {
                usuario_textBox1.Text = "USUARIO";
                usuario_textBox1.ForeColor = Color.DimGray;
            }
        }



        #endregion

    }
}

