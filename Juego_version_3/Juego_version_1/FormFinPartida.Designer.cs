
namespace Juego_version_1
{
    partial class FormFinPartida
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
            this.panel3 = new System.Windows.Forms.Panel();
            this.Fin_iconButton1 = new FontAwesome.Sharp.IconButton();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.PaleGreen;
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(984, 100);
            this.panel1.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.Fin_iconButton1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel2.Location = new System.Drawing.Point(0, 563);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(984, 100);
            this.panel2.TabIndex = 1;
            // 
            // panel3
            // 
            this.panel3.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel3.Location = new System.Drawing.Point(710, 100);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(274, 463);
            this.panel3.TabIndex = 2;
            // 
            // Fin_iconButton1
            // 
            this.Fin_iconButton1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.Fin_iconButton1.FlatAppearance.BorderSize = 0;
            this.Fin_iconButton1.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.Fin_iconButton1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Fin_iconButton1.IconChar = FontAwesome.Sharp.IconChar.TimesCircle;
            this.Fin_iconButton1.IconColor = System.Drawing.Color.Red;
            this.Fin_iconButton1.IconFont = FontAwesome.Sharp.IconFont.Auto;
            this.Fin_iconButton1.IconSize = 60;
            this.Fin_iconButton1.Location = new System.Drawing.Point(927, 38);
            this.Fin_iconButton1.Name = "Fin_iconButton1";
            this.Fin_iconButton1.Size = new System.Drawing.Size(57, 62);
            this.Fin_iconButton1.TabIndex = 0;
            this.Fin_iconButton1.UseVisualStyleBackColor = true;
            this.Fin_iconButton1.Click += new System.EventHandler(this.iconButton1_Click);
            // 
            // FormFinPartida
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(984, 663);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "FormFinPartida";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "FormMesa";
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private FontAwesome.Sharp.IconButton Fin_iconButton1;
        private System.Windows.Forms.Panel panel3;
    }
}