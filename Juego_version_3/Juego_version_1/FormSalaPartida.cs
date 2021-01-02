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
        delegate void DelegadoInvitar(string[] jugadores);
        private Form activeForm = null;
        FormPartida hijosForm;
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
            OpenhijoForm(hijosForm);
            string mensaje;
            byte[] msg;
            mensaje = "8/8/" + numPartida +"/"+ MiUsuario;

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);

        }
        public void EmpezarPartida()
        {
            DelegadoComienzoPartida dcp = new DelegadoComienzoPartida(OpenhijoForm);
            this.Invoke(dcp, new object[] { hijosForm}); 
        }
        public void ActualizarJugadores(string[] jugadores)
        {
            DelegadoInvitar di = new DelegadoInvitar(actualizarJugadores);
            this.Invoke(di, new object[] { jugadores });
        }
        private void actualizarJugadores(string[] jugadores)
        {

            dataGridView1.RowCount = jugadores.Length;
            for (int i = 0; i < jugadores.Length; i++)
            {
                if (partida.ExisteParticipante(jugadores[i])==-1)
                dataGridView1[0, i].Value = jugadores[i];
            }
            dataGridView2.RowCount = jugadores.Length;
            for (int i = 0; i < jugadores.Length; i++)
            {
                if (partida.ExisteParticipante(jugadores[i]) == -1)

                    dataGridView2[0, i].Value = jugadores[i];
            }
            dataGridView3.RowCount = jugadores.Length;
            for (int i = 0; i < jugadores.Length; i++)
            {
                if (partida.ExisteParticipante(jugadores[i]) == -1)

                    dataGridView3[0, i].Value = jugadores[i];
            }
            dataGridView4.RowCount = jugadores.Length;
            for (int i = 0; i < jugadores.Length; i++)
            {
                if (partida.ExisteParticipante(jugadores[i]) == -1)

                    dataGridView4[0, i].Value = jugadores[i];
            }


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
        public void CambiarBotones(int tipoRonda)
        {
            hijosForm.cambBotones(tipoRonda);
        }
        public void Bocatas(string texto, int jugador)
        {
            hijosForm.bocatas(texto, jugador);
        }

        private void dataGridView4_CellClick(object sender, DataGridViewCellEventArgs e)
        {

            int num = e.RowIndex; //Vector de filas
            dataGridView4.Rows[num].Cells[0].Style.BackColor = Color.Green; //La celda seleccionada se pondrá de color azul
            string nombre = Convert.ToString(dataGridView3.Rows[num].Cells[0].Value);
            dataGridView4.ClearSelection();
            string mensaje;
            byte[] msg;
            mensaje = "8/1/" + numPartida + "/" + nombre;

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);

        }

        private void dataGridView2_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int num = e.RowIndex; //Vector de filas
            dataGridView2.Rows[num].Cells[0].Style.BackColor = Color.Green; //La celda seleccionada se pondrá de color azul
            string nombre = Convert.ToString(dataGridView3.Rows[num].Cells[0].Value);
            dataGridView2.ClearSelection();
            string mensaje;
            byte[] msg;
            mensaje = "8/1/" + numPartida + "/" + nombre;

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);

        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int num = e.RowIndex; //Vector de filas
            dataGridView1.Rows[num].Cells[0].Style.BackColor = Color.Green; //La celda seleccionada se pondrá de color azul
            string nombre = Convert.ToString(dataGridView3.Rows[num].Cells[0].Value);
            dataGridView1.ClearSelection();
            string mensaje;
            byte[] msg;
            mensaje = "8/1/" + numPartida + "/" + nombre;

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);
        }

        private void dataGridView3_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int num = e.RowIndex; //Vector de filas
            dataGridView3.Rows[num].Cells[0].Style.BackColor = Color.Green; //La celda seleccionada se pondrá de color azul
            string nombre = Convert.ToString(dataGridView3.Rows[num].Cells[0].Value);
            dataGridView3.ClearSelection();
            string mensaje;
            byte[] msg;
            mensaje = "8/1/" + numPartida + "/" + nombre;

            // Enviamos al servidor los nombres de usuario
            msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            sock.Send(msg);
        }
    }
}
