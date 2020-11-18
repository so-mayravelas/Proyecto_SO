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

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        Socket server;
        bool conected = false;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (conected)
            {
                //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
                //al que deseamos conectarnos
                IPAddress direc = IPAddress.Parse(IP.Text);
                IPEndPoint ipep = new IPEndPoint(direc, 9100);


                //Creamos el socket 
                server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                try
                {
                    server.Connect(ipep);//Intentamos conectar el socket
                    conected = true;
                }
                catch (SocketException)
                {
                    //Si hay excepcion imprimimos error y salimos del programa con return 
                    MessageBox.Show("No he podido conectar con el servidor");
                    return;
                }



            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (conected)
            {
                byte[] msg;
                // Enviamos al servidor el nombre tecleado
                if (radioButton1.Checked)
                {
                    msg = System.Text.Encoding.ASCII.GetBytes("1/" + nombre.Text);
                }
                else
                {
                    msg = System.Text.Encoding.ASCII.GetBytes("2/" + nombre.Text);
                }
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                string mensaje = Encoding.ASCII.GetString(msg2);
                MessageBox.Show(mensaje);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (conected)
            {
                byte[] msg = System.Text.Encoding.ASCII.GetBytes("0/");
                server.Send(msg);
                server.Shutdown(SocketShutdown.Both);
                server.Close();
                conected = false;
            }
        }
    }
}
