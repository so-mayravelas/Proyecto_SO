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
        delegate void DelegadoPuntuaciones(int[] puntos);
        delegate void DelegadoChat(string usuario,string mensaje);
        Partida partida;
        int apuesta;
        int ronda=0;
        int numPartida;
        int jugador;
        Socket socket;
        string miUsuario;
        int[] descartes= { 0,0,0,0,0};

        public FormPartida(Socket socket,int numPartida, string miUsuario)
        {
            this.socket = socket;
            this.numPartida = numPartida;
            this.miUsuario = miUsuario;
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
        public void ValorPartida(Partida p)//seter de partida
        {
            this.partida = p;
        }
        public void ValorApuesta(int a)//seter de apuesta
        {
            this.apuesta = a;
        }
        public void repartir(int numjugador, int[] c)//seter de las cartas dentro de la partida
        {
            this.partida.AsignarCartas(numjugador, c);
        }
        
        public void rondas(int Ronda)//seter de ronda
        {
            this.ronda = Ronda;
        }
        public int rondaDevol()//geter de ronda
        {
            return this.ronda;    
        }
        private void FinpartidaButton1_Click(object sender, EventArgs e)//Final de la partida
        {
            Application.Exit();
        }

        private void ganar_Button_Click(object sender, EventArgs e)//Metodo de Ganador de partida
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
        public void puntuaciones(int[] puntos)// delegado de marcador de puntuacion
        {
            DelegadoPuntuaciones pun = new DelegadoPuntuaciones(Puntuaciones);
            this.Invoke(pun, new object[] { puntos });
        }
        public void bocatas(string texto,int num)// delegado de labels de los bocatas
        {
            DelegadoBocatas db = new DelegadoBocatas(Bocatas);
            this.Invoke(db, new object[] { texto, num });
        }
        private void Bocatas(string texto,int num)// asigna el valor de las labels de los bocatas segun la situacion 
        {
            switch (num-jugador)
            {
                case 0:
                    label5.Visible = true;
                    label5.Text = texto;
                    pictureBox16.Visible = true;
 
                    break;
                case 1:
                case -3:
                    label2.Visible = true;
                    label2.Text = texto;
                    pictureBox12.Visible = true;
                    break;
                case 2:
                case -2:
                    label3.Visible = true;
                    label3.Text = texto;
                    pictureBox9.Visible = true;
                    break;
                case -1:
                case 3:
                    label4.Visible = true;
                    label4.Text = texto;
                    pictureBox5.Visible = true;
                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                    label5.Visible = false;
                    label3.Visible = false;
                    label4.Visible = false;
                    label2.Visible = false;
                    pictureBox16.Visible = false;
                    pictureBox12.Visible = false;
                    pictureBox9.Visible = false;
                    pictureBox5.Visible = false;
                    break;
            }
            
        }
        private Image[] Repartir(int jugador)//00-09 oros--10-19-bastos--20-29-espadas--30-39-copas Reparte segun las cartas que toquen, asignando las imagenes y devolviendolas en un array Image[4]
        {
            Image[] cartas= new Image[4];
            for (int i = 0; i < 4; i++)
            {
                switch (this.partida.DameCarta(jugador, i))
                {
                    case 1:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory+"Resources\\1_oros.jpg");
                        break;
                    case 2:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\2_oros.jpg");
                        break;
                    case 3:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\3_oros.jpg");
                        break;
                    case 4:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\4_oros.jpg");
                        break;
                    case 5:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\5_oros.jpg");
                        break;
                    case 6:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\6_oros.jpg");
                        break;
                    case 7:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\7_oros.jpg");
                        break;
                    case 8:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\10_oros.jpg");
                        break;
                    case 9:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\11_oros.jpg");
                        break;
                    case 10:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\12_oros.jpg");
                        break;
                    case 11:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\1_bastos.jpg");
                        break;
                    case 12:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\2_bastos.jpg");
                        break;
                    case 13:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\3_bastos.jpg");
                        break;
                    case 14:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\4_bastos.jpg");
                        break;
                    case 15:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\5_bastos.jpg");
                        break;
                    case 16:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\6_bastos.jpg");
                        break;
                    case 17:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\7_bastos.jpg");
                        break;
                    case 18:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\10_bastos.jpg");
                        break;
                    case 19:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\11_bastos.jpg");
                        break;
                    case 20:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\12_bastos.jpg");
                        break;
                    case 21:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\1_espadas.jpg");
                        break;
                    case 22:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\2_espadas.jpg");
                        break;
                    case 23:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\3_espadas.jpg");
                        break;
                    case 24:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\4_espadas.jpg");
                        break;
                    case 25:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\5_espadas.jpg");
                        break;
                    case 26:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\6_espadas.jpg");
                        break;
                    case 27:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\7_espadas.jpg");
                        break;
                    case 28:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\10_espadas.jpg");
                        break;
                    case 29:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\11_espadas.jpg");
                        break;
                    case 30:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\12_espadas.jpg");
                        break;
                    case 31:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\1_copas.jpg");
                        break;
                    case 32:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\2_copas.jpg");
                        break;
                    case 33:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\3_copas.jpg");
                        break;
                    case 34:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\4_copas.jpg");
                        break;
                    case 35:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\5_copas.jpg");
                        break;
                    case 36:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\6_copas.jpg");
                        break;
                    case 37:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\7_copas.jpg");
                        break;
                    case 38:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\10_copas.jpg");
                        break;
                    case 39:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\11_copas.jpg");
                        break;
                    case 40:
                        cartas[i] = Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\12_copas.jpg");
                        break;
                }
            }

            return cartas;
        }
        public void cartasJugador(int inicio)// asigna las imagenes a las cartas, si inicio es 0 solo muestra las cartas del jugador, si es 1 muestra las de los otros 3 jugadores, y si es 2 esconde de nuevo las de lo3 jugadores
        {
            int[] pos= { 0,1,2};
            switch (jugador)
            {
                case 0:
                    pos[0] = 1;
                    pos[1] = 2;
                    pos[2] = 3;
                    break;
                case 1:
                    pos[0] = 2;
                    pos[1] = 3;
                    pos[2] = 0;
                    break;
                case 2:
                    pos[0] = 3;
                    pos[1] = 0;
                    pos[2] = 1;
                    break;
            }
            Image[] cartas;
            if (inicio == 0)
            {
                cartas = Repartir(jugador);
                pictureBox20.Image = cartas[0];
                pictureBox19.Image = cartas[1];
                pictureBox18.Image = cartas[2];
                pictureBox17.Image = cartas[3];
            }
            else if (inicio == 1)
            {

                cartas = Repartir(pos[0]);
                for (int i = 0; i < 4; i++)
                    cartas[i].RotateFlip(RotateFlipType.Rotate90FlipNone);
                pictureBox8.Image = cartas[0];
                pictureBox13.Image = cartas[1];
                pictureBox6.Image = cartas[2];
                pictureBox7.Image = cartas[3];

                cartas = Repartir(pos[1]);
                pictureBox1.Image = cartas[0];
                pictureBox2.Image = cartas[1];
                pictureBox3.Image = cartas[2];
                pictureBox4.Image = cartas[3];

                cartas = Repartir(pos[2]);
                for (int i = 0; i < 4; i++)
                    cartas[i].RotateFlip(RotateFlipType.Rotate270FlipNone);
                pictureBox15.Image = cartas[0];
                pictureBox14.Image = cartas[1];
                pictureBox11.Image = cartas[2];
                pictureBox10.Image = cartas[3];

            }
            else
            {
                Image carta=Image.FromFile(System.AppDomain.CurrentDomain.BaseDirectory + "Resources\\reversocarta.jpg");
                /*pictureBox20.Image = carta;
                pictureBox19.Image = carta;
                pictureBox18.Image = carta;
                pictureBox17.Image = carta;*/



                pictureBox1.Image = carta;
                pictureBox2.Image = carta;
                pictureBox3.Image = carta;
                pictureBox4.Image = carta;

                Thread.Sleep(50);
                carta.RotateFlip(RotateFlipType.Rotate90FlipNone);

                pictureBox8.Image = carta;
                pictureBox13.Image = carta;
                pictureBox6.Image = carta;
                pictureBox7.Image = carta;

                Thread.Sleep(50);

                pictureBox15.Image = carta;
                pictureBox14.Image = carta;
                pictureBox11.Image = carta;
                pictureBox10.Image = carta;
            }
        }
        public void cambBotones(int tipoRonda)// deledado para cambiar las etiquetas de los botones segun la ronda
        {
            DelegadoBotones db = new DelegadoBotones(CambiarBotones);
            this.Invoke(db, new object[] { tipoRonda });
        }
        private void CambiarBotones(int tipoRonda)// judga el tipo de ronda en los cuales los mensajes tiene que ser distintos y segun eso los cambia
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
                    case 5:
                        button3.Visible = true;
                        button3.Text = "Siguiente Ronda";
                        button1.Visible = false;
                        button2.Visible = false;
                        label1.Visible = false;
                        hScrollBar1.Visible = false;
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

        private void button1_Click(object sender, EventArgs e)//acciones de los botones que son las jugadas
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
                    if(button1.Text=="Paso")
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/PASO";
                    else
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO QUIERO" + "/" + apuesta;
                    break;
                case 3:
                    if (button1.Text == "Paso")
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/PASO";
                    else
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO QUIERO" + "/" + apuesta;
                    break;
                case 4:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO";
                    break;
                case 5:
                    if (button1.Text == "Paso")
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/PASO";
                    else
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO QUIERO" + "/" + apuesta;
                    break;
                case 6:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO";
                    break;
                case 7:
                    if (button1.Text == "Paso")
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/PASO";
                    else
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO QUIERO" + "/" + apuesta;
                    break;
                case 8:
                    if (button1.Text == "Paso")
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/PASO";
                    else
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO QUIERO" + "/" + apuesta;
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
            mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/QUIERO" + "/" + apuesta;
            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            socket.Send(msg);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            CambiarBotones(-1);
            string mensaje = "";
            int apt;
            byte[] msg;
            switch (ronda)
            {
                case 0:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/NO";
                    break;
                case 1:
                    if (descartes[0] > 0)
                    {
                        for (int i = 0; i < 4; i++)
                            mensaje = 0 != descartes[i + 1] ? mensaje + "/" + i : mensaje + "";
                        mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/" + Convert.ToString(descartes[0]) + mensaje;
                        descartes[0] = 0;
                        descartes[1] = 0;
                        descartes[2] = 0;
                        descartes[3] = 0;
                        descartes[4] = 0;
                        pictureBox17.BorderStyle = System.Windows.Forms.BorderStyle.None;
                        pictureBox18.BorderStyle = System.Windows.Forms.BorderStyle.None;
                        pictureBox19.BorderStyle = System.Windows.Forms.BorderStyle.None;
                        pictureBox20.BorderStyle = System.Windows.Forms.BorderStyle.None;
                    }
                    break;
                case 2:
                    apt = apuesta + Convert.ToInt32(hScrollBar1.Value);
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/APUESTO/" + apuesta +"/"+ apt;
                    break;
                case 3:
                    apt = apuesta + Convert.ToInt32(hScrollBar1.Value);
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/APUESTO/" + apuesta + "/" + apt;
                    break;
                case 4:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/SI";
                    break;
                case 5:
                    apt = apuesta + Convert.ToInt32(hScrollBar1.Value);
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/APUESTO/" + apuesta + "/" + apt;
                    break;
                case 6:
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/SI";
                    break;
                case 7:
                    apt = apuesta + Convert.ToInt32(hScrollBar1.Value);
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/APUESTO/" + apuesta + "/" + apt;
                    break;
                case 8:
                    apt = apuesta + Convert.ToInt32(hScrollBar1.Value);
                    mensaje = "10/" + numPartida + "/" + ronda + "/" + jugador + "/APUESTO/" + apuesta + "/" + apt;
                    break;
                case 13:
                    mensaje = "10/" + numPartida + "/13/" + jugador;
                    break;
            }


            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            socket.Send(msg);
        }
        private void Puntuaciones(int[] puntos)//metodo que cabia el valor de los puntos
        {
            labelP0.Text = "PAREJA 0: Juegos:" + puntos[0] + " Piedras:" + puntos[1];
            labelP1.Text = "PAREJA 1: Juegos:" + puntos[2] + " Piedras:" + puntos[3];
        }
        private void hScrollBar1_ValueChanged(object sender, EventArgs e)//metodo que cambia el valor de la label de hscrollbar segun su valor
        {
            int piedras = apuesta + Convert.ToInt32(hScrollBar1.Value);
            label1.Text = "Apuesta: " + piedras;
        }

        private void pictureBox20_Click(object sender, EventArgs e)// metodos para seleccionar cartas para el descarte
        {
            if (ronda == 1)
            {
                if (pictureBox20.BorderStyle != System.Windows.Forms.BorderStyle.FixedSingle)
                {
                    pictureBox20.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
                    descartes[1] = 1;
                    descartes[0]++;
                }
                else
                {
                    pictureBox20.BorderStyle = System.Windows.Forms.BorderStyle.None;
                    descartes[1] = 0;
                    descartes[0]--;
                }
            }
        }

        private void pictureBox19_Click(object sender, EventArgs e)
        {
            if (ronda == 1)
            {
                if (pictureBox19.BorderStyle != System.Windows.Forms.BorderStyle.FixedSingle)
                {
                    pictureBox19.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
                    descartes[2] = 1;
                    descartes[0]++;
                }
                else
                {
                    pictureBox19.BorderStyle = System.Windows.Forms.BorderStyle.None;
                    descartes[2] = 0;
                    descartes[0]--;
                }
            }
        }

        private void pictureBox18_Click(object sender, EventArgs e)
        {
            if (ronda == 1)
            {
                if (pictureBox18.BorderStyle != System.Windows.Forms.BorderStyle.FixedSingle)
                {
                    pictureBox18.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
                    descartes[3] = 1;
                    descartes[0]++;
                }
                else
                {
                    pictureBox18.BorderStyle = System.Windows.Forms.BorderStyle.None;
                    descartes[3] = 0;
                    descartes[0]--;
                }
            }
        }

        private void pictureBox17_Click(object sender, EventArgs e)
        {
            if (ronda == 1)
            {
                if (pictureBox17.BorderStyle != System.Windows.Forms.BorderStyle.FixedSingle)
                {
                    pictureBox17.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
                    descartes[4] = 1;
                    descartes[0]++;
                }
                else
                {
                    pictureBox17.BorderStyle = System.Windows.Forms.BorderStyle.None;
                    descartes[4] = 0;
                    descartes[0]--;
                }
            }
        }
        public void ChatDelegado(string usuario, string mensaje)// delegado del chat
        {
            DelegadoChat delegadoCha = new DelegadoChat(ActualizarChat);
            this.Invoke(delegadoCha, new object[] { usuario, mensaje });
        }
        public void ActualizarChat(string Usuario, string comentario)// metodo llamado por el delegado para cambiar el texto del chat
        {
            textBoxChat.Text = textBoxChat.Text + Usuario + ": " + comentario + Environment.NewLine;
        }
        private void buttonChat_Click(object sender, EventArgs e)// boton de enviar del chat que hace que el mensaje se envie y se actualice en pantalla
        {
            if (textBoxComentario.Text != "")
            {
                string mensaje;
                byte[] msg;
                mensaje = "9/" + numPartida + "/" + miUsuario + "/" + Convert.ToString(textBoxComentario.Text);
                textBoxChat.Text = textBoxChat.Text + miUsuario + ": " + Convert.ToString(textBoxComentario.Text) + Environment.NewLine;
                textBoxComentario.Text = "";
                // Enviamos al servidor los nombres de usuario
                msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                socket.Send(msg);
            }
        }


    }
}
