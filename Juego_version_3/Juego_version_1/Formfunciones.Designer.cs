namespace Juego_version_1
{
    partial class Formfunciones
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
            this.Conectar_button1 = new System.Windows.Forms.Button();
            this.Desconectar_button2 = new System.Windows.Forms.Button();
            this.Registro_button3 = new System.Windows.Forms.Button();
            this.Iniciar_button4 = new System.Windows.Forms.Button();
            this.Consultas_groupBox1 = new System.Windows.Forms.GroupBox();
            this.Servicios = new System.Windows.Forms.RadioButton();
            this.TBConsultaAndoni = new System.Windows.Forms.TextBox();
            this.nombre_textBox3 = new System.Windows.Forms.TextBox();
            this.Consulta_Mayra = new System.Windows.Forms.RadioButton();
            this.Consulta_Andoni = new System.Windows.Forms.RadioButton();
            this.Consulta_Galder = new System.Windows.Forms.RadioButton();
            this.label2 = new System.Windows.Forms.Label();
            this.enviar_button5 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.usuario_textBox1 = new System.Windows.Forms.TextBox();
            this.contraseña_textBox2 = new System.Windows.Forms.TextBox();
            this.listaClientes = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.ConectadosGrid = new System.Windows.Forms.DataGridView();
            this.InvitarButton = new System.Windows.Forms.Button();
            this.labelInvitacion = new System.Windows.Forms.Label();
            this.buttonAceptar = new System.Windows.Forms.Button();
            this.buttonRechazar = new System.Windows.Forms.Button();
            this.groupBoxInvitacion = new System.Windows.Forms.GroupBox();
            this.buttonChat = new System.Windows.Forms.Button();
            this.textBoxChat = new System.Windows.Forms.TextBox();
            this.textBoxComentario = new System.Windows.Forms.TextBox();
            this.labelChat = new System.Windows.Forms.Label();
            this.groupBoxChat = new System.Windows.Forms.GroupBox();
            this.Consultas_groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ConectadosGrid)).BeginInit();
            this.groupBoxInvitacion.SuspendLayout();
            this.groupBoxChat.SuspendLayout();
            this.SuspendLayout();
            // 
            // Conectar_button1
            // 
            this.Conectar_button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Conectar_button1.Location = new System.Drawing.Point(60, 41);
            this.Conectar_button1.Name = "Conectar_button1";
            this.Conectar_button1.Size = new System.Drawing.Size(99, 33);
            this.Conectar_button1.TabIndex = 0;
            this.Conectar_button1.Text = "CONECTAR";
            this.Conectar_button1.UseCompatibleTextRendering = true;
            this.Conectar_button1.UseVisualStyleBackColor = true;
            this.Conectar_button1.Click += new System.EventHandler(this.Conectar_button1_Click);
            // 
            // Desconectar_button2
            // 
            this.Desconectar_button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Desconectar_button2.Location = new System.Drawing.Point(223, 41);
            this.Desconectar_button2.Name = "Desconectar_button2";
            this.Desconectar_button2.Size = new System.Drawing.Size(113, 33);
            this.Desconectar_button2.TabIndex = 1;
            this.Desconectar_button2.Text = "DESCONECTAR";
            this.Desconectar_button2.UseCompatibleTextRendering = true;
            this.Desconectar_button2.UseVisualStyleBackColor = true;
            this.Desconectar_button2.Click += new System.EventHandler(this.Desconectar_button2_Click);
            // 
            // Registro_button3
            // 
            this.Registro_button3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Registro_button3.Location = new System.Drawing.Point(60, 203);
            this.Registro_button3.Name = "Registro_button3";
            this.Registro_button3.Size = new System.Drawing.Size(99, 44);
            this.Registro_button3.TabIndex = 2;
            this.Registro_button3.Text = "Registrarse";
            this.Registro_button3.UseCompatibleTextRendering = true;
            this.Registro_button3.UseVisualStyleBackColor = true;
            this.Registro_button3.Click += new System.EventHandler(this.Registro_button3_Click);
            // 
            // Iniciar_button4
            // 
            this.Iniciar_button4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Iniciar_button4.Location = new System.Drawing.Point(223, 203);
            this.Iniciar_button4.Name = "Iniciar_button4";
            this.Iniciar_button4.Size = new System.Drawing.Size(99, 44);
            this.Iniciar_button4.TabIndex = 3;
            this.Iniciar_button4.Text = "Entrar";
            this.Iniciar_button4.UseCompatibleTextRendering = true;
            this.Iniciar_button4.UseVisualStyleBackColor = true;
            this.Iniciar_button4.Click += new System.EventHandler(this.Iniciar_button4_Click);
            // 
            // Consultas_groupBox1
            // 
            this.Consultas_groupBox1.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.Consultas_groupBox1.Controls.Add(this.Servicios);
            this.Consultas_groupBox1.Controls.Add(this.TBConsultaAndoni);
            this.Consultas_groupBox1.Controls.Add(this.nombre_textBox3);
            this.Consultas_groupBox1.Controls.Add(this.Consulta_Mayra);
            this.Consultas_groupBox1.Controls.Add(this.Consulta_Andoni);
            this.Consultas_groupBox1.Controls.Add(this.Consulta_Galder);
            this.Consultas_groupBox1.Controls.Add(this.label2);
            this.Consultas_groupBox1.Controls.Add(this.enviar_button5);
            this.Consultas_groupBox1.Location = new System.Drawing.Point(39, 282);
            this.Consultas_groupBox1.Name = "Consultas_groupBox1";
            this.Consultas_groupBox1.Size = new System.Drawing.Size(363, 240);
            this.Consultas_groupBox1.TabIndex = 8;
            this.Consultas_groupBox1.TabStop = false;
            this.Consultas_groupBox1.Text = "Peticion";
            // 
            // Servicios
            // 
            this.Servicios.AutoSize = true;
            this.Servicios.Location = new System.Drawing.Point(116, 145);
            this.Servicios.Name = "Servicios";
            this.Servicios.Size = new System.Drawing.Size(151, 17);
            this.Servicios.TabIndex = 11;
            this.Servicios.TabStop = true;
            this.Servicios.Text = "Consulta cuantos servicios";
            this.Servicios.UseVisualStyleBackColor = true;
            // 
            // TBConsultaAndoni
            // 
            this.TBConsultaAndoni.Location = new System.Drawing.Point(224, 119);
            this.TBConsultaAndoni.Name = "TBConsultaAndoni";
            this.TBConsultaAndoni.Size = new System.Drawing.Size(119, 20);
            this.TBConsultaAndoni.TabIndex = 10;
            // 
            // nombre_textBox3
            // 
            this.nombre_textBox3.Location = new System.Drawing.Point(126, 30);
            this.nombre_textBox3.Name = "nombre_textBox3";
            this.nombre_textBox3.Size = new System.Drawing.Size(169, 20);
            this.nombre_textBox3.TabIndex = 9;
            // 
            // Consulta_Mayra
            // 
            this.Consulta_Mayra.AutoSize = true;
            this.Consulta_Mayra.Location = new System.Drawing.Point(116, 91);
            this.Consulta_Mayra.Name = "Consulta_Mayra";
            this.Consulta_Mayra.Size = new System.Drawing.Size(179, 17);
            this.Consulta_Mayra.TabIndex = 7;
            this.Consulta_Mayra.TabStop = true;
            this.Consulta_Mayra.Text = "Partidas jugadas por el \"usuario\"";
            this.Consulta_Mayra.UseVisualStyleBackColor = true;
            // 
            // Consulta_Andoni
            // 
            this.Consulta_Andoni.AutoSize = true;
            this.Consulta_Andoni.Location = new System.Drawing.Point(116, 119);
            this.Consulta_Andoni.Name = "Consulta_Andoni";
            this.Consulta_Andoni.Size = new System.Drawing.Size(102, 17);
            this.Consulta_Andoni.TabIndex = 7;
            this.Consulta_Andoni.TabStop = true;
            this.Consulta_Andoni.Text = "Consulta Andoni";
            this.Consulta_Andoni.UseVisualStyleBackColor = true;
            // 
            // Consulta_Galder
            // 
            this.Consulta_Galder.AutoSize = true;
            this.Consulta_Galder.Checked = true;
            this.Consulta_Galder.Location = new System.Drawing.Point(116, 68);
            this.Consulta_Galder.Name = "Consulta_Galder";
            this.Consulta_Galder.Size = new System.Drawing.Size(100, 17);
            this.Consulta_Galder.TabIndex = 8;
            this.Consulta_Galder.TabStop = true;
            this.Consulta_Galder.Text = "Consulta Galder";
            this.Consulta_Galder.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(23, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(87, 25);
            this.label2.TabIndex = 1;
            this.label2.Text = "Nombre";
            // 
            // enviar_button5
            // 
            this.enviar_button5.Location = new System.Drawing.Point(126, 189);
            this.enviar_button5.Name = "enviar_button5";
            this.enviar_button5.Size = new System.Drawing.Size(75, 23);
            this.enviar_button5.TabIndex = 5;
            this.enviar_button5.Text = "Enviar";
            this.enviar_button5.UseVisualStyleBackColor = true;
            this.enviar_button5.Click += new System.EventHandler(this.enviar_button5_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(57, 117);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Usuario";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(57, 161);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Password";
            // 
            // usuario_textBox1
            // 
            this.usuario_textBox1.Location = new System.Drawing.Point(125, 117);
            this.usuario_textBox1.Name = "usuario_textBox1";
            this.usuario_textBox1.Size = new System.Drawing.Size(156, 20);
            this.usuario_textBox1.TabIndex = 11;
            // 
            // contraseña_textBox2
            // 
            this.contraseña_textBox2.Location = new System.Drawing.Point(125, 161);
            this.contraseña_textBox2.Name = "contraseña_textBox2";
            this.contraseña_textBox2.PasswordChar = '·';
            this.contraseña_textBox2.Size = new System.Drawing.Size(156, 20);
            this.contraseña_textBox2.TabIndex = 12;
            // 
            // listaClientes
            // 
            this.listaClientes.AutoSize = true;
            this.listaClientes.Location = new System.Drawing.Point(74, 49);
            this.listaClientes.Name = "listaClientes";
            this.listaClientes.Size = new System.Drawing.Size(0, 13);
            this.listaClientes.TabIndex = 13;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12.25F);
            this.label5.Location = new System.Drawing.Point(572, 27);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(103, 20);
            this.label5.TabIndex = 14;
            this.label5.Text = "Conectados:";
            // 
            // ConectadosGrid
            // 
            this.ConectadosGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ConectadosGrid.Location = new System.Drawing.Point(576, 50);
            this.ConectadosGrid.Name = "ConectadosGrid";
            this.ConectadosGrid.RowHeadersWidth = 62;
            this.ConectadosGrid.Size = new System.Drawing.Size(99, 150);
            this.ConectadosGrid.TabIndex = 15;
            this.ConectadosGrid.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.ConectadosGrid_CellClick);
            this.ConectadosGrid.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.ConectadosGrid_CellContentClick);
            // 
            // InvitarButton
            // 
            this.InvitarButton.BackColor = System.Drawing.SystemColors.ControlDark;
            this.InvitarButton.Location = new System.Drawing.Point(576, 206);
            this.InvitarButton.Name = "InvitarButton";
            this.InvitarButton.Size = new System.Drawing.Size(99, 31);
            this.InvitarButton.TabIndex = 16;
            this.InvitarButton.Text = "Invitar";
            this.InvitarButton.UseVisualStyleBackColor = false;
            this.InvitarButton.Click += new System.EventHandler(this.InvitarButton_Click);
            // 
            // labelInvitacion
            // 
            this.labelInvitacion.AutoSize = true;
            this.labelInvitacion.Location = new System.Drawing.Point(13, 28);
            this.labelInvitacion.Name = "labelInvitacion";
            this.labelInvitacion.Size = new System.Drawing.Size(35, 13);
            this.labelInvitacion.TabIndex = 17;
            this.labelInvitacion.Text = "label3";
            // 
            // buttonAceptar
            // 
            this.buttonAceptar.Location = new System.Drawing.Point(15, 55);
            this.buttonAceptar.Name = "buttonAceptar";
            this.buttonAceptar.Size = new System.Drawing.Size(72, 21);
            this.buttonAceptar.TabIndex = 18;
            this.buttonAceptar.Text = "Aceptar";
            this.buttonAceptar.UseVisualStyleBackColor = true;
            this.buttonAceptar.Click += new System.EventHandler(this.buttonAceptar_Click);
            // 
            // buttonRechazar
            // 
            this.buttonRechazar.Location = new System.Drawing.Point(16, 85);
            this.buttonRechazar.Name = "buttonRechazar";
            this.buttonRechazar.Size = new System.Drawing.Size(72, 21);
            this.buttonRechazar.TabIndex = 19;
            this.buttonRechazar.Text = "Rechazar";
            this.buttonRechazar.UseVisualStyleBackColor = true;
            this.buttonRechazar.Click += new System.EventHandler(this.buttonRechazar_Click);
            // 
            // groupBoxInvitacion
            // 
            this.groupBoxInvitacion.BackColor = System.Drawing.Color.Transparent;
            this.groupBoxInvitacion.Controls.Add(this.buttonRechazar);
            this.groupBoxInvitacion.Controls.Add(this.buttonAceptar);
            this.groupBoxInvitacion.Controls.Add(this.labelInvitacion);
            this.groupBoxInvitacion.Controls.Add(this.listaClientes);
            this.groupBoxInvitacion.Location = new System.Drawing.Point(420, 52);
            this.groupBoxInvitacion.Name = "groupBoxInvitacion";
            this.groupBoxInvitacion.Size = new System.Drawing.Size(133, 129);
            this.groupBoxInvitacion.TabIndex = 20;
            this.groupBoxInvitacion.TabStop = false;
            this.groupBoxInvitacion.Text = "Invitacion";
            // 
            // buttonChat
            // 
            this.buttonChat.Location = new System.Drawing.Point(195, 262);
            this.buttonChat.Name = "buttonChat";
            this.buttonChat.Size = new System.Drawing.Size(49, 21);
            this.buttonChat.TabIndex = 24;
            this.buttonChat.Text = "Enviar";
            this.buttonChat.UseVisualStyleBackColor = true;
            this.buttonChat.Click += new System.EventHandler(this.buttonChat_Click);
            // 
            // textBoxChat
            // 
            this.textBoxChat.Location = new System.Drawing.Point(23, 32);
            this.textBoxChat.Multiline = true;
            this.textBoxChat.Name = "textBoxChat";
            this.textBoxChat.ReadOnly = true;
            this.textBoxChat.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxChat.Size = new System.Drawing.Size(169, 213);
            this.textBoxChat.TabIndex = 21;
            // 
            // textBoxComentario
            // 
            this.textBoxComentario.Location = new System.Drawing.Point(23, 263);
            this.textBoxComentario.Name = "textBoxComentario";
            this.textBoxComentario.Size = new System.Drawing.Size(169, 20);
            this.textBoxComentario.TabIndex = 22;
            // 
            // labelChat
            // 
            this.labelChat.AutoSize = true;
            this.labelChat.Location = new System.Drawing.Point(26, 12);
            this.labelChat.Name = "labelChat";
            this.labelChat.Size = new System.Drawing.Size(35, 13);
            this.labelChat.TabIndex = 23;
            this.labelChat.Text = "label3";
            // 
            // groupBoxChat
            // 
            this.groupBoxChat.BackColor = System.Drawing.Color.Transparent;
            this.groupBoxChat.Controls.Add(this.labelChat);
            this.groupBoxChat.Controls.Add(this.buttonChat);
            this.groupBoxChat.Controls.Add(this.textBoxComentario);
            this.groupBoxChat.Controls.Add(this.textBoxChat);
            this.groupBoxChat.Location = new System.Drawing.Point(425, 246);
            this.groupBoxChat.Name = "groupBoxChat";
            this.groupBoxChat.Size = new System.Drawing.Size(250, 295);
            this.groupBoxChat.TabIndex = 25;
            this.groupBoxChat.TabStop = false;
            this.groupBoxChat.Text = "Chat";
            // 
            // Formfunciones
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Silver;
            this.BackgroundImage = global::Juego_version_1.Properties.Resources.fondoprincipal;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1005, 654);
            this.Controls.Add(this.groupBoxChat);
            this.Controls.Add(this.groupBoxInvitacion);
            this.Controls.Add(this.InvitarButton);
            this.Controls.Add(this.ConectadosGrid);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.contraseña_textBox2);
            this.Controls.Add(this.usuario_textBox1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Consultas_groupBox1);
            this.Controls.Add(this.Iniciar_button4);
            this.Controls.Add(this.Registro_button3);
            this.Controls.Add(this.Desconectar_button2);
            this.Controls.Add(this.Conectar_button1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "Formfunciones";
            this.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultBounds;
            this.Text = "Form1";
            this.Consultas_groupBox1.ResumeLayout(false);
            this.Consultas_groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ConectadosGrid)).EndInit();
            this.groupBoxInvitacion.ResumeLayout(false);
            this.groupBoxInvitacion.PerformLayout();
            this.groupBoxChat.ResumeLayout(false);
            this.groupBoxChat.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Conectar_button1;
        private System.Windows.Forms.Button Desconectar_button2;
        private System.Windows.Forms.Button Registro_button3;
        private System.Windows.Forms.Button Iniciar_button4;
        private System.Windows.Forms.GroupBox Consultas_groupBox1;
        private System.Windows.Forms.RadioButton Consulta_Mayra;
        private System.Windows.Forms.RadioButton Consulta_Andoni;
        private System.Windows.Forms.RadioButton Consulta_Galder;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button enviar_button5;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox usuario_textBox1;
        private System.Windows.Forms.TextBox contraseña_textBox2;
        private System.Windows.Forms.TextBox nombre_textBox3;
        private System.Windows.Forms.TextBox TBConsultaAndoni;
        private System.Windows.Forms.RadioButton Servicios;
        private System.Windows.Forms.Label listaClientes;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DataGridView ConectadosGrid;
        private System.Windows.Forms.Button InvitarButton;
        private System.Windows.Forms.Label labelInvitacion;
        private System.Windows.Forms.Button buttonAceptar;
        private System.Windows.Forms.Button buttonRechazar;
        private System.Windows.Forms.GroupBox groupBoxInvitacion;
        private System.Windows.Forms.Button buttonChat;
        private System.Windows.Forms.TextBox textBoxChat;
        private System.Windows.Forms.TextBox textBoxComentario;
        private System.Windows.Forms.Label labelChat;
        private System.Windows.Forms.GroupBox groupBoxChat;
    }
}

