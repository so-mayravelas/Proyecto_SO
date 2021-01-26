
namespace Juego_version_1
{
    partial class FormRegistrar
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.iconButton3 = new FontAwesome.Sharp.IconButton();
            this.Contraseña2_textBox1 = new System.Windows.Forms.TextBox();
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.Registrar_button1 = new System.Windows.Forms.Button();
            this.contraseña1_textBox2 = new System.Windows.Forms.TextBox();
            this.iconButton2 = new FontAwesome.Sharp.IconButton();
            this.panel3 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.iconButton1 = new FontAwesome.Sharp.IconButton();
            this.usuario1_textBox1 = new System.Windows.Forms.TextBox();
            this.Salir_iconButton3 = new FontAwesome.Sharp.IconButton();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.panel1.Controls.Add(this.Registrar_button1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Margin = new System.Windows.Forms.Padding(2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(800, 54);
            this.panel1.TabIndex = 1;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.MistyRose;
            this.panel2.Controls.Add(this.iconButton3);
            this.panel2.Controls.Add(this.Contraseña2_textBox1);
            this.panel2.Controls.Add(this.linkLabel1);
            this.panel2.Controls.Add(this.contraseña1_textBox2);
            this.panel2.Controls.Add(this.iconButton2);
            this.panel2.Controls.Add(this.panel3);
            this.panel2.Controls.Add(this.iconButton1);
            this.panel2.Controls.Add(this.usuario1_textBox1);
            this.panel2.Location = new System.Drawing.Point(235, 81);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(332, 357);
            this.panel2.TabIndex = 5;
            // 
            // iconButton3
            // 
            this.iconButton3.AutoSize = true;
            this.iconButton3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.iconButton3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.iconButton3.IconChar = FontAwesome.Sharp.IconChar.Lock;
            this.iconButton3.IconColor = System.Drawing.Color.Maroon;
            this.iconButton3.IconFont = FontAwesome.Sharp.IconFont.Auto;
            this.iconButton3.IconSize = 30;
            this.iconButton3.Location = new System.Drawing.Point(21, 217);
            this.iconButton3.Name = "iconButton3";
            this.iconButton3.Size = new System.Drawing.Size(38, 38);
            this.iconButton3.TabIndex = 7;
            this.iconButton3.UseVisualStyleBackColor = true;
            // 
            // Contraseña2_textBox1
            // 
            this.Contraseña2_textBox1.BackColor = System.Drawing.Color.Snow;
            this.Contraseña2_textBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Contraseña2_textBox1.Font = new System.Drawing.Font("ROG Fonts", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Contraseña2_textBox1.ForeColor = System.Drawing.Color.DimGray;
            this.Contraseña2_textBox1.Location = new System.Drawing.Point(55, 217);
            this.Contraseña2_textBox1.Multiline = true;
            this.Contraseña2_textBox1.Name = "Contraseña2_textBox1";
            this.Contraseña2_textBox1.Size = new System.Drawing.Size(263, 38);
            this.Contraseña2_textBox1.TabIndex = 6;
            this.Contraseña2_textBox1.Text = "  REPETIR  PASSWORD";
            this.Contraseña2_textBox1.Enter += new System.EventHandler(this.Contraseña1_textBox1_Enter);
            this.Contraseña2_textBox1.Leave += new System.EventHandler(this.Contraseña1_textBox1_Leave);
            // 
            // linkLabel1
            // 
            this.linkLabel1.AutoSize = true;
            this.linkLabel1.Font = new System.Drawing.Font("Microsoft YaHei UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.linkLabel1.LinkColor = System.Drawing.Color.FromArgb(((int)(((byte)(10)))), ((int)(((byte)(30)))), ((int)(((byte)(255)))));
            this.linkLabel1.Location = new System.Drawing.Point(17, 324);
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.Size = new System.Drawing.Size(160, 19);
            this.linkLabel1.TabIndex = 0;
            this.linkLabel1.TabStop = true;
            this.linkLabel1.Text = "Ya tengo cuenta en Mus";
            this.linkLabel1.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // Registrar_button1
            // 
            this.Registrar_button1.FlatAppearance.BorderSize = 0;
            this.Registrar_button1.FlatAppearance.MouseDownBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(74)))), ((int)(((byte)(64)))));
            this.Registrar_button1.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Teal;
            this.Registrar_button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Registrar_button1.Font = new System.Drawing.Font("ROG Fonts", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Registrar_button1.ForeColor = System.Drawing.SystemColors.InfoText;
            this.Registrar_button1.Location = new System.Drawing.Point(65, 413);
            this.Registrar_button1.Name = "Registrar_button1";
            this.Registrar_button1.Size = new System.Drawing.Size(297, 40);
            this.Registrar_button1.TabIndex = 3;
            this.Registrar_button1.Text = "CONFIRMAR";
            this.Registrar_button1.UseVisualStyleBackColor = true;
            this.Registrar_button1.Click += new System.EventHandler(this.Registrar_button1_Click);
            // 
            // contraseña1_textBox2
            // 
            this.contraseña1_textBox2.BackColor = System.Drawing.Color.Snow;
            this.contraseña1_textBox2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.contraseña1_textBox2.Font = new System.Drawing.Font("ROG Fonts", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.contraseña1_textBox2.ForeColor = System.Drawing.Color.DimGray;
            this.contraseña1_textBox2.Location = new System.Drawing.Point(55, 159);
            this.contraseña1_textBox2.Multiline = true;
            this.contraseña1_textBox2.Name = "contraseña1_textBox2";
            this.contraseña1_textBox2.Size = new System.Drawing.Size(263, 38);
            this.contraseña1_textBox2.TabIndex = 2;
            this.contraseña1_textBox2.Text = "    PASSWORD";
            this.contraseña1_textBox2.Enter += new System.EventHandler(this.Passw_textBox2_Enter);
            this.contraseña1_textBox2.Leave += new System.EventHandler(this.Passw_textBox2_Leave);
            // 
            // iconButton2
            // 
            this.iconButton2.AutoSize = true;
            this.iconButton2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.iconButton2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.iconButton2.IconChar = FontAwesome.Sharp.IconChar.Lock;
            this.iconButton2.IconColor = System.Drawing.Color.Maroon;
            this.iconButton2.IconFont = FontAwesome.Sharp.IconFont.Auto;
            this.iconButton2.IconSize = 30;
            this.iconButton2.Location = new System.Drawing.Point(21, 159);
            this.iconButton2.Name = "iconButton2";
            this.iconButton2.Size = new System.Drawing.Size(38, 38);
            this.iconButton2.TabIndex = 5;
            this.iconButton2.UseVisualStyleBackColor = true;
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(74)))), ((int)(((byte)(64)))));
            this.panel3.Controls.Add(this.label1);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel3.Location = new System.Drawing.Point(0, 0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(332, 36);
            this.panel3.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("ROG Fonts", 9.749999F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.label1.Location = new System.Drawing.Point(3, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(315, 16);
            this.label1.TabIndex = 0;
            this.label1.Text = "Crea tu cuenta y empieza a jugar";
            // 
            // iconButton1
            // 
            this.iconButton1.AutoSize = true;
            this.iconButton1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.iconButton1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.iconButton1.IconChar = FontAwesome.Sharp.IconChar.UserAlt;
            this.iconButton1.IconColor = System.Drawing.Color.DarkGreen;
            this.iconButton1.IconFont = FontAwesome.Sharp.IconFont.Auto;
            this.iconButton1.IconSize = 30;
            this.iconButton1.Location = new System.Drawing.Point(21, 93);
            this.iconButton1.Name = "iconButton1";
            this.iconButton1.Size = new System.Drawing.Size(38, 38);
            this.iconButton1.TabIndex = 2;
            this.iconButton1.UseVisualStyleBackColor = true;
            // 
            // usuario1_textBox1
            // 
            this.usuario1_textBox1.BackColor = System.Drawing.Color.Snow;
            this.usuario1_textBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.usuario1_textBox1.Font = new System.Drawing.Font("ROG Fonts", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.usuario1_textBox1.ForeColor = System.Drawing.Color.DimGray;
            this.usuario1_textBox1.Location = new System.Drawing.Point(55, 93);
            this.usuario1_textBox1.Multiline = true;
            this.usuario1_textBox1.Name = "usuario1_textBox1";
            this.usuario1_textBox1.Size = new System.Drawing.Size(263, 38);
            this.usuario1_textBox1.TabIndex = 1;
            this.usuario1_textBox1.Text = "      Nombre de jugador";
            this.usuario1_textBox1.TextChanged += new System.EventHandler(this.usuario_textBox1_TextChanged);
            this.usuario1_textBox1.Enter += new System.EventHandler(this.usuario_textBox1_Enter);
            this.usuario1_textBox1.Leave += new System.EventHandler(this.usuario_textBox1_Leave_1);
            // 
            // Salir_iconButton3
            // 
            this.Salir_iconButton3.BackColor = System.Drawing.Color.Transparent;
            this.Salir_iconButton3.FlatAppearance.BorderSize = 0;
            this.Salir_iconButton3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Salir_iconButton3.IconChar = FontAwesome.Sharp.IconChar.SignOutAlt;
            this.Salir_iconButton3.IconColor = System.Drawing.Color.Navy;
            this.Salir_iconButton3.IconFont = FontAwesome.Sharp.IconFont.Auto;
            this.Salir_iconButton3.ImageAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.Salir_iconButton3.Location = new System.Drawing.Point(689, 396);
            this.Salir_iconButton3.Name = "Salir_iconButton3";
            this.Salir_iconButton3.Size = new System.Drawing.Size(44, 57);
            this.Salir_iconButton3.TabIndex = 6;
            this.Salir_iconButton3.UseVisualStyleBackColor = false;
            this.Salir_iconButton3.Click += new System.EventHandler(this.iconButton3_Click);
            // 
            // FormRegistrar
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Juego_version_1.Properties.Resources.registro_bc1;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.Salir_iconButton3);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "FormRegistrar";
            this.Text = "FormRegistrar";
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.LinkLabel linkLabel1;
        private System.Windows.Forms.Button Registrar_button1;
        private System.Windows.Forms.TextBox contraseña1_textBox2;
        private FontAwesome.Sharp.IconButton iconButton2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label label1;
        private FontAwesome.Sharp.IconButton iconButton1;
        private System.Windows.Forms.TextBox usuario1_textBox1;
        private FontAwesome.Sharp.IconButton Salir_iconButton3;
        private FontAwesome.Sharp.IconButton iconButton3;
        private System.Windows.Forms.TextBox Contraseña2_textBox1;
    }
}