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
using System.Media;
using FontAwesome.Sharp;

namespace Juego_version_1
{
    public partial class FormPartida : Form

    {
        delegate void DelegadoBotones(int i);
        delegate void DelegadoBocatas(string texto, int num);
        Partida partida;
        int ronda;
        int numPartida;
        int jugador;
        Socket socket;

        public FormPartida(Socket socket,int numPartida)
        {
            this.socket = socket;
            this.numPartida = numPartida;
            InitializeComponent();
        }
        public void ValorJugador(int jugador)
        {
            this.jugador = jugador;
            if (jugador == 0)
                cambBotones(0);
            else
                cambBotones(-1);
        }
        public void ValorPartida(Partida p)
        {
            this.partida = p;
        }
        public void repartir(int numjugador, int[] c)
        {
            partida.AsignarCartas(numjugador, c);
        }
        
        public void rondas(int Ronda)
        {
            this.ronda = Ronda;
        }

        private void FinpartidaButton1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void ganar_Button_Click(object sender, EventArgs e)
        {
            AbrirFormfills(new FormFinPartida());
        }

        private void AbrirFormfills(object formfill)
        {

            if (this.finjuegopanel1.Controls.Count > 0)
                this.finjuegopanel1.Controls.RemoveAt(0);
            Form fillg = formfill as Form;
            fillg.TopLevel = false;
            fillg.Dock = DockStyle.None;
            this.finjuegopanel1.Controls.Add(fillg);
            this.finjuegopanel1.Tag = fillg;
            fillg.Show();
        }

        public void bocatas(string texto,int num)
        {
            DelegadoBocatas db = new DelegadoBocatas(Bocatas);
            this.Invoke(db, new object[] { texto, num });
        }
        private void Bocatas(string texto,int num)
        {
            switch (num)
            {
                case 0:
                    label5.Visible = true;
                    label5.Text = texto;
                    label3.Visible = false;
                    label4.Visible = false;
                    label2.Visible = false;
                    pictureBox16.Visible = true;
                    pictureBox12.Visible = false;
                    pictureBox9.Visible = false;
                    pictureBox5.Visible=false;
 
                    break;
                case 1:
                    label2.Visible = true;
                    label2.Text = texto;
                    pictureBox12.Visible = true;
                    break;
                case 2:
                    label3.Visible = true;
                    label3.Text = texto;
                    pictureBox9.Visible = true;
                    break;
                case 3:
                    label4.Visible = true;
                    label4.Text = texto;
                    pictureBox5.Visible = true;
                    break;
            }
            
        }
        public void cambBotones(int tipoRonda)
        {
            DelegadoBotones db = new DelegadoBotones(CambiarBotones);
            this.Invoke(db, new object[] { tipoRonda });
        }
        private void CambiarBotones(int tipoRonda)
        {
                switch (tipoRonda)
                {
                    case 0:
                        button1.Visible = true;
                        button1.Text = "Mus";
                        button2.Visible = false;
                        button3.Visible = true;
                        button3.Text = "No hay Mus";
                        label1.Visible = false;
                        hScrollBar1.Visible = false;
                        break;
                    case 1:
                        button3.Visible = true;
                        button3.Text = "Descartar";
                        button1.Visible = false;
                        button2.Visible = false;
                        label1.Visible = false;
                        hScrollBar1.Visible = false;
                        break;
                    case 2:
                        button1.Visible = true;
                        button1.Text = "No";
                        button3.Visible = true;
                        button3.Text = "Si";
                        button2.Visible = false;
                        label1.Visible = false;
                        hScrollBar1.Visible = false;
                        break;
                    case 3:
                        button1.Visible = true;
                        button1.Text = "Paso";
                        button3.Visible = true;
                        button3.Text = "Apuesto";
                        hScrollBar1.Visible = true;
                        label1.Visible = true;
                        button2.Visible = false;
                        label1.Visible = true;
                        hScrollBar1.Visible = true;
                        break;
                    case 4:
                        button1.Visible = true;
                        button1.Text = "No Quiero";
                        button2.Visible = true;
                        button2.Text = "Quiero";
                        button3.Visible = true;
                        button3.Text = "Apuesto";
                        hScrollBar1.Visible = true;
                        label1.Visible = true;
                        break;
                    case -1:
                        button1.Visible = false;
                        button2.Visible = false;
                        button3.Visible = false;
                        label1.Visible = false;
                        hScrollBar1.Visible = false;
                        break;
                }
            } 

        private void button1_Click(object sender, EventArgs e)
        {
            CambiarBotones(-1);
            string mensaje="";
            byte[] msg;
            switch (ronda)
            {
                case 0:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/MUS" ;
                    break;
                case 2:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO";
                    break;
                case 3:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/PASO";
                    break;
                case 4:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO QUIERO";
                    break;
            }


            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            socket.Send(msg);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            CambiarBotones(-1);
            string mensaje = "";
            byte[] msg;
            switch (ronda)
            {
                case 4:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/QUIERO";
                    break;
            }


            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            socket.Send(msg);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            CambiarBotones(-1);
            string mensaje = "";
            byte[] msg;
            switch (ronda)
            {
                case 0:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO";
                    break;
                case 1:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/A/" +Convert.ToInt32(hScrollBar1.Value);
                    break;
                case 2:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/SI";
                    break;
                case 3:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/APUESTO/" + Convert.ToInt32(hScrollBar1.Value);
                    break;
                case 4:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/APUESTO/" + Convert.ToInt32(hScrollBar1.Value);
                    break;
            }


            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            socket.Send(msg);
        }

        private void hScrollBar1_ValueChanged(object sender, EventArgs e)
        {
            label1.Text = "Apuesta: " + Convert.ToInt32(hScrollBar1.Value);
        }
    }
}
