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
        delegate void DelegadoPanel(int i);
        public FormSalaPartida(int numPartida, Socket sock)
        {
            this.numPartida = numPartida;
            this.sock = sock;
            InitializeComponent();
        }
        public void ActualizacionPartida(Partida partida)
        {
            this.partida = partida;
            MessageBox.Show(partida.DameParticipante(0));
            for (int i=0; i < 4; i++) {
                if (partida.DameParticipante(i) != "") {
                    DelegadoPanel Delegadopanel = new DelegadoPanel(VerPanel);
                    
                    switch (i)
                    {
                        case 1:
                            panelJug1.Invoke(Delegadopanel, new object[] { i });
                            break;
                        case 2:
                            panelJug2.Invoke(Delegadopanel, new object[] { i });
                            break;
                        case 3:
                            panelJug3.Invoke(Delegadopanel, new object[] { i });
                            break;
                        case 4:
                            panelJug4.Invoke(Delegadopanel, new object[] { i });
                            break;
                    }
                    
                }
            }
        }
        public void VerPanel(int i)
        {
            
            switch (i)
            {
                case 1:
                    MessageBox.Show("Participan1");
                    panelJug1.Visible = false;
                    break;
                case 2:
                    MessageBox.Show("Participan2");
                    panelJug2.Visible = false;
                    break;
                case 3:
                    panelJug3.Visible = false;
                    break;
                case 4:
                    panelJug4.Visible = false;
                    break;
            }
        }
    }
}
