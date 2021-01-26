using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using FontAwesome.Sharp;
using System.Net;

namespace Juego_version_1
{
    public partial class FormRegistrar : Form
    {

        String MiUsuario, invitador;
        Socket server;
        Thread atender;
        Thread crearForm;
        bool loged = false, conectado = false;
        List<FormRegistrar> formularios = new List<FormRegistrar>();

        public FormRegistrar()
        {
            InitializeComponent();
        }




        #region ResaltarTexto

        //mouse sale del texto

        private void usuario_textBox1_Enter(object sender, EventArgs e)
        {
            if (usuario1_textBox1.Text == "      Nombre de jugador")
            {
                usuario1_textBox1.Text = "";
                usuario1_textBox1.ForeColor = Color.Black;
            }
        }

        private void usuario_textBox1_Leave_1(object sender, EventArgs e)
        {
            if (usuario1_textBox1.Text == "")
            {
                usuario1_textBox1.Text = "      Nombre de jugador";
                usuario1_textBox1.ForeColor = Color.DimGray;
            }
        }
       

        private void Passw_textBox2_Enter(object sender, EventArgs e)
        {
            if (contraseña1_textBox2.Text == "    PASSWORD")
            {
                contraseña1_textBox2.Text = "";
                contraseña1_textBox2.ForeColor = Color.Black;
                contraseña1_textBox2.UseSystemPasswordChar = true;
            }
        }

        private void Passw_textBox2_Leave(object sender, EventArgs e)
        {
            if (contraseña1_textBox2.Text == "")
            {
                contraseña1_textBox2.Text = "    PASSWORD";
                contraseña1_textBox2.ForeColor = Color.DimGray;
                contraseña1_textBox2.UseSystemPasswordChar = false;
            }
        }

        private void Contraseña1_textBox1_Enter(object sender, EventArgs e)
        {
            if (Contraseña2_textBox1.Text == "  REPETIR  PASSWORD")
            {
                Contraseña2_textBox1.Text = "";
                Contraseña2_textBox1.ForeColor = Color.Black;
                Contraseña2_textBox1.UseSystemPasswordChar = true;
            }
        }


        private void Contraseña1_textBox1_Leave(object sender, EventArgs e)
        {
            if (Contraseña2_textBox1.Text == "")
            {
                Contraseña2_textBox1.Text = "  REPETIR  PASSWORD";
                Contraseña2_textBox1.ForeColor = Color.DimGray;
                Contraseña2_textBox1.UseSystemPasswordChar = false;
            }
        }


        #endregion


        private void usuario_textBox1_TextChanged(object sender, EventArgs e)
        {

        }

     



        private void Registrar_button1_Click(object sender, EventArgs e)
        {
            // Datos Validos 

            if (usuario1_textBox1.Text == "NOMBRE DE JUGADOR " || contraseña1_textBox2.Text == "PASSWORD" || Contraseña2_textBox1.Text == "REPETIR PASSWORD")
            {
                MessageBox.Show("Rellena todos los campos correctamente");
                return;
            }
            if (contraseña1_textBox2.Text != Contraseña2_textBox1.Text)
            {
                MessageBox.Show("Los passwords deben coindicir");
                return;
            }

            //Preparamos la peticion
            //Cuando un usuario quiera registrarse le tendremos que agregar a la BBDD 
            string mensaje = "2/" + Convert.ToString(usuario1_textBox1.Text) + "/" + Convert.ToString(contraseña1_textBox2.Text);
            // Enviamos al servidor el usuario que queremos registrar y guardar en BBDD
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            if (conectado == true)
                server.Send(msg);
            this.Hide();
        }

    
        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
           
            
        }



        private void iconButton3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

    }
}
