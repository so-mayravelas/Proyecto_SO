using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FontAwesome.Sharp;

namespace Juego_version_1
{
    public class Partida
    {
        //Definimos una lista de FlightPlans tipo Lists<>
        string[] Participantes= { "", "", "", "" };
        int ID_Partida;
        int[] Puntuaciones = { 0, 0, 0, 0 };
        int[,] Cartas = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
        int Count = 0;
 
        public void AñadirParticipante(string participante,int pos)
        {
            bool existe = false;
            for (int i = 0; i < Count; i++)
            {
                if (participante == Participantes[i])
                    existe=true;
            }
            if (existe == false)
            {
                Participantes[pos]=participante;
                Count++;
                
            }
        }
        public void AsignarCartas(int jugador, int[] c)
        {
            for(int i=0; i<4; i++)
            {
                Cartas[jugador, i] = c[i];
            }
        }
        public void QuitarParticipante(string participante)
        {
            for (int i = 0; i < Count; i++)
            {
                if (participante == Participantes[i])
                    Participantes[i] = participante;
            }
            Count--;
        }
        public string DameParticipante(int i) {
            return Participantes[i];
        }

        public int DameNum()
        {
            return Count;
        }
        public int DameID()
        {
            return ID_Partida;
        }
        public void PonID(int id)
        {
            ID_Partida = id;
        }

        public int ExisteParticipante(string usuario)
        {
            for (int i = 0; i < 4; i++)
            {
                if (Participantes[i] == usuario)
                    return i;
            }
            return -1;
        }
    }
}
