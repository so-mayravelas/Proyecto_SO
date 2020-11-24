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
        Socket server;
        Thread atender;
        bool loged=false;
        public Form1()
        {
            
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
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
            IPEndPoint ipep = new IPEndPoint(direc, 9000);


            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
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
            server.Send(msg);
            loged = false;
            // Nos desconectamos
            this.BackColor = Color.Gray;
            server.Shutdown(SocketShutdown.Both);
            server.Close();
        }
        //Para que un usuario se pueda registrar
        private void Registro_button3_Click(object sender, EventArgs e)
        {
            //Cuando un usuario quiera registrarse le tendremos que agregar a la BBDD 
            string mensaje = "2/" + Convert.ToString(usuario_textBox1.Text) + "/" +  Convert.ToString(contraseña_textBox2.Text);
            // Enviamos al servidor el usuario que queremos registrar y guardar en BBDD
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

        }

        //Si ya estamos registardos o nos acabos de registra ya podemos ingresar ya estaremso dados de alta en la BBDD
        private void Iniciar_button4_Click(object sender, EventArgs e)
        {
            // Quiere realizar un inicio de sesión
            string mensaje = "1/" +  Convert.ToString(usuario_textBox1.Text) + "/" + Convert.ToString(contraseña_textBox2.Text) ;
            // Enviamos al servidor el nombre del usuario y la contraseña
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

        }

        private void enviar_button5_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            byte[] msg2;
            if (Consulta_Galder.Checked == true && loged==true)
            {
                // Realizamos la consulta escogida
                mensaje = "3/" + Convert.ToString(nombre_textBox3.Text);
                // Enviamos al servidor el nombre del usuario
                msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
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
                server.Send(msg);

            }
            else if (Servicios.Checked==true && loged == true)
            {
                // Quiere realizar la consulta escogida
                mensaje = "6/";
                // Enviamos al servidor los nombres de usuario
                msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

            }

            else
            {
                MessageBox.Show("Inicie sesion para hacer alguna consulta");
            }
            
        }
        private void AtenderServidor()
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
                identificador = Convert.ToInt32(mensaje[0]);
                switch (identificador)
                {
                    case 1://log in
                        
                        if (mensaje[1].Equals("si"))
                        {
                            loged = true;
                            MessageBox.Show("Has iniciado sesion correctamente");
                        }
                        else
                        {
                            MessageBox.Show("No has iniciado sesion correctamente");
                        }
                        break;
                    case 2://registrarse


                        if (mensaje[1] == "si")
                        {
                            loged = true;
                            MessageBox.Show("Te has registrado correctamente");
                        }
                        else
                        {
                            MessageBox.Show("Error: Usuario ya en uso");
                        }
                        break;
                    case 3://servicio Galder
                        string lista="";
                        
                        
                        for (int i=1;i<mensaje.Length;i++)
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
                        lista = "";


                        for (int i = 1; i < mensaje.Length; i++)
                        {

                            lista = lista + mensaje[i] + "\n";
                        }
                        listaClientes.Text= lista;
                        break;

                }
            }
        }
    }
}

