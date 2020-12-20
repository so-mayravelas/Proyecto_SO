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
    public partial class FormPrincipal : Form
    {

        private IconButton currentBtn;
      
        
        
        public FormPrincipal()
        {
            InitializeComponent();
            Diseño();

            //Para quitar la barra del Form
            this.Text = String.Empty;
            this.ControlBox = false;
            this.DoubleBuffered = true;
            this.MaximizedBounds = Screen.FromHandle(this.Handle).WorkingArea;
        }

        private void Diseño()
        {
            submenufq_panel4.Visible = false;
        
        }
        //Para oculatar submenu
        private void ocultarsubmen()
        {
            if (submenufq_panel4.Visible == true)
                submenufq_panel4.Visible = false;
              
        }
        //Para mostrarsubmenu

        private void showsubmenu(Panel subMenu)
        
        {
            if (subMenu.Visible == false)
            {
                ocultarsubmen();
                subMenu.Visible = true;
            }
            else
                subMenu.Visible = false;
        }
        private void panel2pantallaprincipal_Paint(object sender, PaintEventArgs e)
        {

        }

        private void iconButton2_Click(object sender, EventArgs e)
        {
            showsubmenu(submenufq_panel4);
        }

        private void InstruccinesButton4_Click(object sender, EventArgs e)
        {
            ocultarsubmen();
        }

        //Para llamar al formulario hijo que aparecera enla pantalla principal
        //para que cerremos los formularios anteriores y no molesten

        private Form activeForm = null;
        private void OpenhijoForm(Form hijosForm)
        {
            if (activeForm != null)
                activeForm.Close();
            activeForm = hijosForm;
            hijosForm.TopLevel = false;
            hijosForm.FormBorderStyle = FormBorderStyle.None;
            hijosForm.Dock = DockStyle.Fill;
            panelhijos_panel2.Controls.Add(hijosForm);
            panelhijos_panel2.Tag = hijosForm;
            hijosForm.BringToFront();
            hijosForm.Show();
            Titulodeformulariohijo.Text = hijosForm.Text;
        }


         //cuando llamamos al formulario como objeto
        //private void AbrirFormsInPanel(object Formshijos)
        //{

        //    if (this.panelhijos_panel2.Controls.Count > 0)
        //        this.panelhijos_panel2.Controls.RemoveAt(0);
        //    Form fhijo = Formshijos as Form;
        //    fhijo.TopLevel = false;
        //    fhijo.Dock = DockStyle.Fill;
        //    this.panelhijos_panel2.Controls.Add(fhijo);
        //    this.panelhijos_panel2.Tag = fhijo;
        //    fhijo.Show();
            
        //}
       
        //PARA Abrir los formularios de las partidas dentro del panel buscremos el panel el formulario Partida
        public void AbrirFormPartida<MiForm>() where MiForm : Form, new()
        {
            Form formulario;
            formulario = panelhijos_panel2.Controls.OfType<MiForm>().FirstOrDefault();
            if (formulario == null)
            {
                formulario = new MiForm();
                formulario.TopLevel = false;
                panelhijos_panel2.Controls.Add(formulario);
                panelhijos_panel2.Tag = formulario;
                formulario.Show();
            }
            else
            {
                formulario.BringToFront();
            }


        }

        //Para activar Botones
        private void ActivarBoton(object senderBtn, Color color)
        {
            iconFormulariohijoactual.IconChar = currentBtn.IconChar;
            iconFormulariohijoactual.IconColor = color;



        
        }

        //Para desactivar Botonactual

        private void DesactivarBoton()
        { 
         
          
        }

        //Boton de reiniciar

        private void Reset()
        {
            DesactivarBoton();
            iconFormulariohijoactual.IconChar = IconChar.Home;
            iconFormulariohijoactual.IconColor = Color.MediumPurple;
            Titulodeformulariohijo.Text = "Home";


        }
         //boton registrarse
        private void RegistrarButton1_Click(object sender, EventArgs e)
        {
            OpenhijoForm(new Formfunciones());
            //AbrirFormsInPanel(new Formfunciones());
        }
        //Boton iniciar Sesion

        private void iconButton1_Click(object sender, EventArgs e)
        {
            OpenhijoForm(new Formfunciones());
            
            
        }

        //Para podr mover el formulario desde el panel
        [DllImport("user32.DLL", EntryPoint = "ReleaseCapture")]
        private extern static void ReleaseCapture();

        [DllImport("user32.DLL", EntryPoint = "SendMessage")]
        private extern static void SendMessage(System.IntPtr hwnd, int wMsg, int wParam, int lParam);

        private void barradetitulo_panel_MouseDown(object sender, MouseEventArgs e)
        {

            ReleaseCapture();
            SendMessage(this.Handle, 0x112, 0xf012, 0);

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {   //cerraremso el formulariohijos
            activeForm.Close();
            Reset();
        }

        private void iconPictureBox2_Click(object sender, EventArgs e)
        {

        }

        private void iconPictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void miniiconPictureBox1_Click(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Minimized;
        }

        private void menupp_panel1_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
