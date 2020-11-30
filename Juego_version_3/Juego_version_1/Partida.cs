using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Juego_version_1
{
    public class Partida
    {
        //Definimos una lista de FlightPlans tipo Lists<>
        List<string> Participantes = new List<string>();
        int ID_Partida;
 
        public void AñadirParticipante(string participante)
        {
            bool existe = false;
            for (int i = 0; i < Participantes.Count; i++)
            {
                if (participante == Participantes[i]);
            }
            if (existe == false)
            {
                Participantes.Add(participante);
            }
        }
        public void QuitarpParticipante(string participante)
        {
            bool existe = false;
            for (int i = 0; i < Participantes.Count; i++)
            {
                if (participante == Participantes[i])
                    existe = true;
            }
            if (existe == true)
            {
                Participantes.Remove(participante);
            }
        }
        public int DameNum()
        {
            return Participantes.Count;
        }
        public int DameID()
        {
            return ID_Partida;
        }
        public void PonID(int id)
        {
            ID_Partida = id;
        }

        public Boolean ExixteParticipante(string usuario)
        {
            for (int i = 0; i < Participantes.Count; i++)
            {
                if (Participantes[i] == usuario)
                    return true;
            }
            return false;
        }
    }
}
