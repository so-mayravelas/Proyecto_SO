using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Juego_version_1
{
    public partial class FormIntrucciones : Form
    {
        public FormIntrucciones()
        {
            InitializeComponent();
        }




        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void Ocultar()
        {
            this.pictureBox1.Visible = false;
            this.pictureBox2.Visible = false;
            this.pictureBox3.Visible = false;
            this.pictureBox4.Visible = false;
            this.pictureBox5.Visible = false;
            this.pictureBox6.Visible = false;
            this.pictureBox7.Visible = false;
        }

        private void Objetivo_button1_Click(object sender, EventArgs e)
        {
            Ocultar();
            this.pictureBox1.Visible = true;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Ocultar();
            this.pictureBox2.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Ocultar();
            this.pictureBox3.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Ocultar();
            this.pictureBox4.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Ocultar();
            this.pictureBox5.Show();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Ocultar();
            this.pictureBox6.Show();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Ocultar();
            this.pictureBox7.Show();
        }

        private void Cerrar_iconButton1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
