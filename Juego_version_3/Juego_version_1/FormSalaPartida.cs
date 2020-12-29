using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace Juego_version_1
{
    public partial class FormSalaPartida : Form
    {
        int numPartida;
        Socket sock;
        Partida partida;
        string MiUsuario;
        delegate void DelegadoPanel(int i);
        delegate void DelegadoComienzoPartida(Form hijosForm);
        private Form activeForm = null;
        public FormSalaPartida(int numPartida, Socket sock,string MiUsuario)
        {
            this.numPartida = numPartida;
            this.sock = sock;
            this.MiUsuario = MiUsuario;
            InitializeComponent();
        }
        public void ActualizacionPartida(Partida partida)
        {
            this.partida = partida;
            for (int i=0; i < 4; i++) {
                if (partida.DameParticipante(i) != "") {
                    DelegadoPanel Delegadopanel = new DelegadoPanel(VerPanel);
                    
                    switch (i)
                    {
                        case 0:
                            panelJug1.Invoke(Delegadopanel, new object[] { i });
                            break;
                        case 1:
                            panelJug2.Invoke(Delegadopanel, new object[] { i });
                            break;
                        case 2:
                            panelJug3.Invoke(Delegadopanel, new object[] { i });
                            break;
                        case 3:
                            panelJug4.Invoke(Delegadopanel, new object[] { i });
                            break;
                    }
                    
                }
            }
        }
        public void VerPanel(int i)
        {
            button5.Visible = false;
            switch (i)
            {
                case 0:
                    label14.Text = "Username: " + partida.DameParticipante(i);
                    label13.Text = "Pareja: " + partida.DameParticipante(i);
                    panelJug1.Visible = false;
                    if (0 == partida.ExisteParticipante(MiUsuario))
                        button2.Visible = false;
                    else
                        button2.Visible = true;
                    break;
                case 1:
                    label9.Text = "Username: " + partida.DameParticipante(i);
                    label10.Text = "Pareja: " + partida.DameParticipante(i);
                    panelJug2.Visible = false;
                    if (1 == partida.ExisteParticipante(MiUsuario))
                        button3.Visible = false;
                    else
                        button3.Visible = true;
                    break;
                case 2:
                    label7.Text = "Username: " + partida.DameParticipante(i);
                    label8.Text = "Pareja: " + partida.DameParticipante(i);
                    panelJug3.Visible = false;
                    if (2 == partida.ExisteParticipante(MiUsuario))
                        button1.Visible = false;
                    else
                        button1.Visible = true;
                    break;
                case 3:
                    label11.Text = "Username: " + partida.DameParticipante(i);
                    label12.Text = "Pareja: " + partida.DameParticipante(i);
                    panelJug4.Visible = false;
                    if (3 == partida.ExisteParticipante(MiUsuario))
                        button4.Visible = false;
                    else
                        button4.Visible = true;
                    break;
            }
            if (0 == partida.ExisteParticipante(MiUsuario))
                button5.Visible = true;


        }

        private void button2_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            mensaje = "8/5/" + numPartida + "/0/" + partida.ExisteParticipante(MiUsuario);

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            mensaje = "8/5/" + numPartida + "/1/" + partida.ExisteParticipante(MiUsuario);

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            mensaje = "8/5/" + numPartida + "/2/" +partida.ExisteParticipante(MiUsuario);

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);
        }
        private void button4_Click(object sender, EventArgs e)
        {
            string mensaje;
            byte[] msg;
            mensaje = "8/5/"+numPartida+"/3/" + partida.ExisteParticipante(MiUsuario);

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            OpenhijoForm(new FormPartida());
            string mensaje;
            byte[] msg;
            mensaje = "8/8/" + numPartida +"/"+ MiUsuario;

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);

        }
        public void EmpezarPartida(Form hijosForm)
        {
            DelegadoComienzoPartida dcp = new DelegadoComienzoPartida(OpenhijoForm);
            this.Invoke(dcp, new object[] { hijosForm}); 
        }
        private void OpenhijoForm(Form hijosForm)
        {
            if (activeForm != null)
                activeForm.Close();
            activeForm = hijosForm;
            hijosForm.TopLevel = false;
            hijosForm.FormBorderStyle = FormBorderStyle.None;
            hijosForm.Dock = DockStyle.Fill;
            panel2.Controls.Add(hijosForm);
            panel2.Tag = hijosForm;
            panel2.Visible = true;
            hijosForm.BringToFront();
            hijosForm.Show();
        }
    }
}
