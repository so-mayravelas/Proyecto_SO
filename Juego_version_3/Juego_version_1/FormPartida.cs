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

        
        public FormPartida()
        {
            InitializeComponent();
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

        private void FormPartida_Load(object sender, EventArgs e)
        {

        }

        //Aceptamos la partida



        //Metodos cuando alguien gana
        //public void Cerrar(string ganador)
        //{
        //    this.timer1.Stop();
        //    if (ganador == this.jinferior_label.Text)
        //    {
        //        string consulta = "22/" + this.id + "/" + this.segundos;
        //        byte[] msg = System.Text.Encoding.ASCII.GetBytes(consulta);
        //        server.Send(msg);
        //    }
        //    this.cerrar = true;
        //    this.Close();
        //}


        //public void CancelarPartida()
        //{
        //    this.cerrar = true;
        //    this.Close();
        //}
        //public void SetTurno(int turno)
        //{
        //    this.turno = turno;
        //    this.textBoxChat.Items.Add("Es el turno de " + this.jugadores[this.turno]);
        //    this.textBoxChat.TopIndex = this.textBoxChat.Items.Count - 1;
        //}
        //public void SetSentido(int sentido)
        //{
        //    this.sentido = sentido;
        //}




        //Añade una carta al centro de la mesa para ver que carta se esta jugando en ese momento
        //public void HaveCard(int num)
        //{
        //    try { cartaEnMesa.Dispose(); }
        //    catch { };

        //    PictureBox PicBx = new PictureBox();
        //    PicBx.Size = new Size(cdWidth / 2, cdHeight / 2);
        //    PicBx.Location = new Point(this.cdWidth / 2 - cdWidth / 2, this.cdHeight / 2 - cdHeight / 4);

        //    Rectangle rect = new Rectangle(1 + cdWidth * (num % 14), 1 + cdHeight * (int)Math.Floor((double)num / 14), cdWidth, cdHeight);
        //    Image card = cropImage(this.deck, rect);
        //    PicBx.Image = card;
        //    PicBx.SizeMode = PictureBoxSizeMode.StretchImage;
        //    PicBx.Name = num.ToString();

        //    cartaEnMesa = PicBx;
        //    this.Controls.Add(PicBx);

        //}



        ////Funcion recortar imagen revisar compatibilidad ponerlas directas sin usar bitmap
        //private static Image cropImage(Image img, Rectangle cropArea)
        //{
        //    Bitmap bmpImage = new Bitmap(img);
        //    Bitmap bmpCrop = bmpImage.Clone(cropArea, bmpImage.PixelFormat);
        //    return (Image)(bmpCrop);
        //}

        //private void PicBx_Click(object sender, EventArgs e)
        //{
        //    PictureBox target = (PictureBox)sender;
        //    //this.MensajeRecibido("Carta nº" + target.Name, "(consola)");

        //    string mensaje = "21/" + this.id + "/" + target.Name;
        //    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
        //    server.Send(msg);
        //}

        //private void EnviarBtn_Click(object sender, EventArgs e)
        //{
        //    if (this.textBoxComentario.Text != "")
        //    {
        //        string mensaje = "12/" + this.id + "|" + this.textBoxComentario.Text;
        //        byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
        //        server.Send(msg);
        //    }
        //    this.textBoxComentario.Clear();
        //}

        //private void MensajeTxt_KeyPress(object sender, KeyPressEventArgs e)
        //{
        //    if (e.KeyChar == (char)Keys.Enter)
        //        this.buttonChat.PerformClick();
        //}

        //private void Mesa_FormClosing(object sender, FormClosingEventArgs e)
        //{
        //    if (this.cerrar == false)
        //    {
        //        DialogResult res = MessageBox.Show("¿Estás seguro que quieres salir de la partida?", "Salir", MessageBoxButtons.YesNo);
        //        if (res == DialogResult.Yes)
        //        {
        //            string cancelar = "23/" + this.id;
        //            byte[] msg2 = System.Text.Encoding.ASCII.GetBytes(cancelar);
        //            server.Send(msg2);
        //        }
        //        e.Cancel = true;
        //    }
        //}

        //private void buttonChat_Click(object sender, EventArgs e)
        //{
        //    string mensaje;
        //    byte[] msg;
        //    mensaje = "9/" + Convert.ToString(idpartidainvitacion) + "/" + MiUsuario + "/" + Convert.ToString(textBoxComentario.Text);
        //    textBoxChat.Text = MiUsuario + ": " + Convert.ToString(textBoxComentario.Text) + Environment.NewLine;
        //    // Enviamos al servidor los nombres de usuario
        //    msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
        //    if (conectado == true)
        //        server.Send(msg);
        //}
        //public void PreparacionChat(int ID)
        //{
        //    groupBoxChat.Visible = true;
        //    labelChat.Text = "Partida: " + Convert.ToString(ID);
        //}

        //public void ActualizarChat(string Usuario, string comentario)
        //{
        //    textBoxChat.Text = textBoxChat.Text + Usuario + ": " + comentario + Environment.NewLine;
        //}

        //private void Pasoturno_Button_Click(object sender, EventArgs e)
        //{
        //    string paso = "20/" + this.id;
        //    byte[] msg2 = System.Text.Encoding.ASCII.GetBytes(paso);
        //    server.Send(msg2);
        //}
    }
}
