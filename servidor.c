#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <pthread.h>
#include<unistd.h>
#include <time.h>

//Declacion de la esturctura para conectados
int contadorservicios;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef struct {
	char nombre[20];
	int Cartas[4];
	int socket;
} Conectado;

typedef struct{
	Conectado conectados[100];
	int num;
} ListaConectados;
ListaConectados milistaConectados;
typedef struct {
	Conectado jugadores[4];
	int empezada;
	int Apuesta[5];
	int Mano[4];
	int Puntos[4];
	int Pares[4];
	int Juego[4];
	int Baraja[40];
} Partida;

typedef struct {
	Partida partidas[100];
	int num;
} ListaPartidas;
ListaPartidas milistaPartidas;
//COn tipo=1 Resetea los parametros de la partida con tipo=0 los fija
void InicioPartida(int numpartida, int tipo)
{
	pthread_mutex_lock(&mutex);
	if(tipo=0)
	{
		for(int i=0;i<5;i++)
		{
			if(i<4)
			{
				milistaPartidas.partidas[numpartida].Apuesta[i]=0;
				milistaPartidas.partidas[numpartida].Puntos[i]=0;
				milistaPartidas.partidas[numpartida].Pares[i]=0;
				milistaPartidas.partidas[numpartida].Juego[i]=0;
			}
			else
			   milistaPartidas.partidas[numpartida].Apuesta[i]=0;
		}
	}
	else
	{
		for(int i=0;i<5;i++)
		{
			if(i<4)
			{
				milistaPartidas.partidas[numpartida].Apuesta[i]=0;
				milistaPartidas.partidas[numpartida].Pares[i]=0;
				milistaPartidas.partidas[numpartida].Juego[i]=0;
			}
			else
			   milistaPartidas.partidas[numpartida].Apuesta[i]=0;
		}
	}
	pthread_mutex_unlock(&mutex);
}
//Retorna el numero del jugador que se envuentra en la posicion introducida
int DamejugadorPosicion(int numpartida, int posicionmano)
{
	int c = milistaPartidas.partidas[numpartida].Mano[posicionmano];
	return c;
}
//retorna el nombre del jugador en la posicion introducida
void DameNombre(int numPartida, int jugador, char nombre[20])
{
		strcpy(nombre, milistaPartidas.partidas[numPartida].jugadores[jugador].nombre);
}
// Utiliza Fisher-Yates shuffle -> Durstenfeld's version (Modern method) para barajar la baraja
void BarajarBaraja(int numPartida)
{
	int Bar[40];
	for (int i=0;i<40;i++)//Creo los valores de las cartas, del 1 al 40
		Bar[i] = i+1;
	
	srand(time(NULL));//Estructura para generar numeros aleatorios
	int n = 40;
	for(int i=0;i<40;i++)
	{
		int v = rand()%n;// nos genera un numero aleatorio entre 0 y n-1
		int p = Bar[v];
		Bar [v] = Bar[n-1];
		Bar[n-1] = p;
		n--;
	}
	pthread_mutex_lock(&mutex);
	for(int i=0;i<40;i++)
	{
		milistaPartidas.partidas[numPartida].Baraja[i]= Bar[i];
		printf("%d: %d\n", i, milistaPartidas.partidas[numPartida].Baraja[i]);
	}
	pthread_mutex_unlock(&mutex);
}
//Establece como es la mano inicias: [0,1,2,3]
void ManoInicial(numPartida)
{
	for(int i=0;i<4;i++)
	{
		pthread_mutex_lock(&mutex);
		milistaPartidas.partidas[numPartida].Mano[i]=i;
		pthread_mutex_unlock(&mutex);
	}
}
//Reparte 4 cartas a cada jugador
void Repartir(numPartida)
{
	pthread_mutex_lock(&mutex);
	for(int j=0;j<4;j++){
		int p = DamejugadorPosicion(numPartida, j);
		int cartas1[4] = {milistaPartidas.partidas[numPartida].Baraja[j],milistaPartidas.partidas[numPartida].Baraja[4+j],milistaPartidas.partidas[numPartida].Baraja[j+8],milistaPartidas.partidas[numPartida].Baraja[12+j]};
		for(int i=0;i<4;i++)
		{
			milistaPartidas.partidas[numPartida].jugadores[p].Cartas[i] = cartas1[i];
		}
		printf("Cartas: %d,%d,%d,%d\n", milistaPartidas.partidas[numPartida].jugadores[p].Cartas[0],milistaPartidas.partidas[numPartida].jugadores[p].Cartas[1],milistaPartidas.partidas[numPartida].jugadores[p].Cartas[2],milistaPartidas.partidas[numPartida].jugadores[p].Cartas[3]);
	}
	pthread_mutex_unlock(&mutex);
	
	for(int i=0; i<16;i++)
	{
		pthread_mutex_lock(&mutex);
		milistaPartidas.partidas[numPartida].Baraja[i]=0;
		pthread_mutex_unlock(&mutex);
	}
}

//Envia las cartas de todos los jugadores en un unico mensaje
void EnviarCartas(numPartida)
{
	char mensaje[200];
	sprintf(mensaje,"11/%d/11",numPartida);
	for (int i=0;i<4;i++)
	{
		sprintf(mensaje,"%s/%d/%d/%d/%d",mensaje,milistaPartidas.partidas[numPartida].jugadores[i].Cartas[0],milistaPartidas.partidas[numPartida].jugadores[i].Cartas[1],milistaPartidas.partidas[numPartida].jugadores[i].Cartas[2],milistaPartidas.partidas[numPartida].jugadores[i].Cartas[3]);
	}
	printf("Respuesta: %s\n", mensaje);
	EnviarAPatida("", mensaje , numPartida);
}
//Envia las cartas del jugador introduciodo en un unico mensaje
void EnviarCartasJugador(int numPartida, int jugador)
{
	char mensaje[200];
	sprintf(mensaje,"11/%d/10/%d/%d/%d/%d/%d",numPartida,jugador,milistaPartidas.partidas[numPartida].jugadores[jugador].Cartas[0],milistaPartidas.partidas[numPartida].jugadores[jugador].Cartas[1],milistaPartidas.partidas[numPartida].jugadores[jugador].Cartas[2],milistaPartidas.partidas[numPartida].jugadores[jugador].Cartas[3]);
	EnviarAPatida(milistaPartidas.partidas[numPartida].jugadores[jugador].nombre, mensaje , numPartida);
}
//Rota la mano a la siguiente posicion en el siguiente sentido: 0->1,1->2,2->3,3->0
void PasarMano(int numPartida)
{
	int ma = milistaPartidas.partidas[numPartida].Mano[0];
	if(ma == 0)
	{
		pthread_mutex_lock(&mutex);
		int mano[4] = {1,2,3,0};
		for(int i=0;i<4;i++)
			milistaPartidas.partidas[numPartida].Mano[i] = mano[i];
		pthread_mutex_unlock(&mutex);
	}
	else if(ma == 1)
	{
		pthread_mutex_lock(&mutex);
		int mano[4] = {2,3,0,1};
		for(int i=0;i<4;i++)
			milistaPartidas.partidas[numPartida].Mano[i] = mano[i];
		pthread_mutex_unlock(&mutex);
	}
	else if(ma == 2)
	{
		pthread_mutex_lock(&mutex);
		int mano[4] = {3,0,1,2};
		for(int i=0;i<4;i++)
			milistaPartidas.partidas[numPartida].Mano[i] = mano[i];
		pthread_mutex_unlock(&mutex);
	}
	else if(ma == 3)
	{
		pthread_mutex_lock(&mutex);
		int mano[4] = {0,1,2,4};
		for(int i=0;i<4;i++)
			milistaPartidas.partidas[numPartida].Mano[i] = mano[i];
		pthread_mutex_unlock(&mutex);
	}
}
//Asigna el valor de juego al la posicicion correspondiente al jugador en Pares de la partida
void HayPares(int numPartida, int jugador, int i)
{
	pthread_mutex_lock(&mutex);
	milistaPartidas.partidas[numPartida].Pares[jugador] = i;
	pthread_mutex_unlock(&mutex);
}
//Asigna el valor de juego al la posicicion correspondiente al jugador en Juego de la partida
void HayJuego(int numPartida, int jugador, int i)
{
	pthread_mutex_lock(&mutex);
	milistaPartidas.partidas[numPartida].Juego[jugador] = i;
	pthread_mutex_unlock(&mutex);
}
//Retorna 0 si ninguno tiene pares, 1 si las dos parejas tienen pares, 2 si solo la pareja 0 tiene pares y 3 si solo la pareja 1 tiene pares
int hayPares(int numPartida)
{
	int p=0;
	for(int i=0;i<4;i++)
	{
		if(milistaPartidas.partidas[numPartida].Pares[i]==1)
		{
			if(i==0 || i==2)
			{
				if(p==3 || p==1)
					p=1;
				else
					p=2;
			}
			else if(i==1 || i== 3)
			{
				if(p==2 || p==1)
					p=1;
				else
					p=3;
			}
				
		}
	}
	return p;
}
//Retorna 0 si ninguno tiene juego, 1 si las dos parejas tienen juego, 2 si solo la pareja 0 tiene juego y 3 si solo la pareja 1 tiene juego
int hayJuego(int numPartida)
{
	int p=0;
	for(int i=0;i<4;i++)
	{
		if(milistaPartidas.partidas[numPartida].Juego[i]==1)
		{
			if(i==0 || i==2)
			{
				if(p==3 || p==1)
					p=1;
				else
					p=2;
			}
			else if(i==1 || i== 3)
			{
				if(p==2 || p==1)
					p=1;
				else
					p=3;
			}
			
		}
	}
	return p;
}
//Intercambia la carta descartada por una nueva
void Mus(int numPartida, int jugador, int carta)
{
	int e = 0;
	int i = 0;
	while (e==0)
	{
		if(milistaPartidas.partidas[numPartida].Baraja[i]!=0)
		{
			milistaPartidas.partidas[numPartida].jugadores[jugador].Cartas[carta]=milistaPartidas.partidas[numPartida].Baraja[i];
			milistaPartidas.partidas[numPartida].Baraja[i]=0;
			e=1;
		}
		i++;
	}
}
//Fija el valor de la apuesta en la posicion correspondiente a la ronda en Apuesta
void Apostar(int numPartida, int ronda, int Apuesta)
{
	pthread_mutex_lock(&mutex);
	milistaPartidas.partidas[numPartida].Apuesta[ronda-1]= Apuesta;
	pthread_mutex_unlock(&mutex);
}
//Suma los puntos introducidos a la pareja introducida y retorna -10 si gana la pareja 0 y -11 si gana la pareja 1. Si todavia no gana nadie retorna 0
int SumarPuntos(int numPartida, int Pareja, int Puntos)
{
	char mensaje[200];
	if(milistaPartidas.partidas[numPartida].Puntos[2*Pareja+1] + Puntos >= 40)
	{
		pthread_mutex_lock(&mutex);
		milistaPartidas.partidas[numPartida].Puntos[2*Pareja+1] = 0;
		milistaPartidas.partidas[numPartida].Puntos[2*Pareja] = milistaPartidas.partidas[numPartida].Puntos[2*Pareja] + 1;
		pthread_mutex_unlock(&mutex);
		if(milistaPartidas.partidas[numPartida].Puntos[2*Pareja]==3)
		{
			if(Pareja==0)
			{
				sprintf(mensaje,"11/%d/12/%d/%d/%d/%d",numPartida,milistaPartidas.partidas[numPartida].Puntos[0],milistaPartidas.partidas[numPartida].Puntos[1],milistaPartidas.partidas[numPartida].Puntos[2],milistaPartidas.partidas[numPartida].Puntos[3]);
				printf("Notificacion: %s\n", mensaje);
				EnviarAPatida("", mensaje , numPartida);
				usleep(50000);
				return -10;
			}
			else
			{
				sprintf(mensaje,"11/%d/12/%d/%d/%d/%d",numPartida,milistaPartidas.partidas[numPartida].Puntos[0],milistaPartidas.partidas[numPartida].Puntos[1],milistaPartidas.partidas[numPartida].Puntos[2],milistaPartidas.partidas[numPartida].Puntos[3]);
				printf("Notificacion: %s\n", mensaje);
				EnviarAPatida("", mensaje , numPartida);
				usleep(50000);
				return -11;
			}
		}
		sprintf(mensaje,"11/%d/12/%d/%d/%d/%d",numPartida,milistaPartidas.partidas[numPartida].Puntos[0],milistaPartidas.partidas[numPartida].Puntos[1],milistaPartidas.partidas[numPartida].Puntos[2],milistaPartidas.partidas[numPartida].Puntos[3]);
		printf("Notificacion: %s\n", mensaje);
		EnviarAPatida("", mensaje , numPartida);
		usleep(50000);
		return -1;
	}
	else
	{
		pthread_mutex_lock(&mutex);
		milistaPartidas.partidas[numPartida].Puntos[2*Pareja+1] = milistaPartidas.partidas[numPartida].Puntos[2*Pareja+1] + Puntos;
		pthread_mutex_unlock(&mutex);
		sprintf(mensaje,"11/%d/12/%d/%d/%d/%d",numPartida,milistaPartidas.partidas[numPartida].Puntos[0],milistaPartidas.partidas[numPartida].Puntos[1],milistaPartidas.partidas[numPartida].Puntos[2],milistaPartidas.partidas[numPartida].Puntos[3]);
		printf("Notificacion: %s\n", mensaje);
		EnviarAPatida("", mensaje , numPartida);
		usleep(50000);
		return 0;
	}
}
//Suma los puntos de la apuesta de la ronda introducida a los ganadores y retorna -10 si gana la pareja 0 y -11 si gana la pareja 1. Si todavia no gana nadie retorna 0
int Puntos(int numPartida, int jugador, int ronda)
{
	int Puntos = milistaPartidas.partidas[numPartida].Apuesta[ronda-1];
	printf("Puntos: %d Ronda: %d Jugador: %d\n", Puntos, ronda, jugador);
	if (Puntos == 0)
	{
		if(ronda==5)
			Puntos = 2;
		if(ronda==4 || ronda==3)
		{
			char mensaje[200];
			sprintf(mensaje,"11/%d/12/%d/%d/%d/%d",numPartida,milistaPartidas.partidas[numPartida].Puntos[0],milistaPartidas.partidas[numPartida].Puntos[1],milistaPartidas.partidas[numPartida].Puntos[2],milistaPartidas.partidas[numPartida].Puntos[3]);
			printf("Notificacion: %s\n", mensaje);
			EnviarAPatida("", mensaje , numPartida);
			usleep(50000);
			return 0;
		}
		else
			Puntos = 1;
	}
	if (Puntos == -1)
	{
		char mensaje[200];
		sprintf(mensaje,"11/%d/12/%d/%d/%d/%d",numPartida,milistaPartidas.partidas[numPartida].Puntos[0],milistaPartidas.partidas[numPartida].Puntos[1],milistaPartidas.partidas[numPartida].Puntos[2],milistaPartidas.partidas[numPartida].Puntos[3]);
		printf("Notificacion: %s\n", mensaje);
		EnviarAPatida("", mensaje , numPartida);
		usleep(50000);
		return 0;
	}
	
	if (jugador==0 || jugador==2)//Puntos para la Pareja 1
	{
		int c = SumarPuntos(numPartida, 1, Puntos);
		return c;
	}
	else
	{
		int c = SumarPuntos(numPartida, 0, Puntos);
		return c;
	}
}
//Reparte los puntos de la Ronda a los ganadores y retorna -10 si gana la pareja 0 y -11 si gana la pareja 1. Si todavia no gana nadie retorna 0
int ContarPuntos(int numPartida)
{
	pthread_mutex_lock(&mutex);
	for(int i=0;i<4;i++)//Asigna el mismo valor a las mismas cartas (8 rey y 3, 7 caballo, 6 sota...)
	{
		for(int j=0;j<4;j++)
		{
			if(milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 3 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 13 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 23 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 33 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 10 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 20 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 30 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 40)
				milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] = 10;
			else if(milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 9 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 19 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 29 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 39)
				milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] = 9;
			else if(milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 8 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 18 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 28 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 38)
				milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] = 8;
			else if(milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 7 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 17 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 27 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 37)
				milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] = 7;
			else if(milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 6 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 16 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 26 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 36)
				milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] = 6;
			else if(milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 5 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 15 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 25 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 35)
				milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] = 5;
			else if(milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 4 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 14 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 24 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 34)
				milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] = 4;
			else if(milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 1 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 11 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 21 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 31 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 2 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 12 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 22 || milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] == 32)
				milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] = 1;
		}
		for(int j=0;j<3;j++)//Ordena las cartas de mayor a menor
		{
			int c = milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j];
			for(int k=j+1;k<4;k++)
			{
				if(c < milistaPartidas.partidas[numPartida].jugadores[i].Cartas[k])
				{
					c = milistaPartidas.partidas[numPartida].jugadores[i].Cartas[k];
					int p = milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j];
					milistaPartidas.partidas[numPartida].jugadores[i].Cartas[j] = c;
					milistaPartidas.partidas[numPartida].jugadores[i].Cartas[k] = p;
				}
				
			}
		}
	}
	pthread_mutex_unlock(&mutex);
	//Repartimos los puntos de Mayor
	int p = milistaPartidas.partidas[numPartida].Mano[0];
	for(int i=1;i<4;i++)
	{
		int c = milistaPartidas.partidas[numPartida].Mano[i];
		if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[0] < milistaPartidas.partidas[numPartida].jugadores[c].Cartas[0])
			p = c;
		else if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[0] == milistaPartidas.partidas[numPartida].jugadores[c].Cartas[0])
		{
			if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[1] < milistaPartidas.partidas[numPartida].jugadores[c].Cartas[1])
				p = c;
			else if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[1] == milistaPartidas.partidas[numPartida].jugadores[c].Cartas[1])
			{
				if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[2] < milistaPartidas.partidas[numPartida].jugadores[c].Cartas[2])
					p = c;
				else if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[2] == milistaPartidas.partidas[numPartida].jugadores[c].Cartas[2])
				{
					if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[3] < milistaPartidas.partidas[numPartida].jugadores[c].Cartas[3])
						p = c;
				}
			}
		}
	}
	if(p==0 || p==2)
	{
		int c = Puntos(numPartida,3,1);
		if(c==-10)
			return -10;
		else if(c==-1)
			return -1;
	}
	else
	{
		int c = Puntos(numPartida,2,1);
		if(c==-11)
			return -11;
		else if(c==-1)
			return -1;
	}
	//Repartimos los puntos de Pequeña
	p = milistaPartidas.partidas[numPartida].Mano[0];
	for(int i=1;i<4;i++)
	{
		int c = milistaPartidas.partidas[numPartida].Mano[i];
		if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[3] > milistaPartidas.partidas[numPartida].jugadores[c].Cartas[3])
			p = c;
		else if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[3] == milistaPartidas.partidas[numPartida].jugadores[c].Cartas[3])
		{
			if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[2] > milistaPartidas.partidas[numPartida].jugadores[c].Cartas[2])
				p = c;
			else if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[2] == milistaPartidas.partidas[numPartida].jugadores[c].Cartas[2])
			{
				if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[1] > milistaPartidas.partidas[numPartida].jugadores[c].Cartas[1])
					p = c;
				else if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[1] == milistaPartidas.partidas[numPartida].jugadores[c].Cartas[1])
				{
					if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[0] < milistaPartidas.partidas[numPartida].jugadores[c].Cartas[0])
						p = c;
				}
			}
		}
	}
	if(p==0 || p==2)
	{
		int c = Puntos(numPartida,3,2);
		if(c==-10)
			return -10;
		else if(c==-1)
			return -1;
	}
	else
	{
		int c = Puntos(numPartida,2,2);
		if(c==-11)
			return -11;
		else if(c==-1)
			return -1;
	}
	//Repartimos los puntos de Pares si es que hay
	if(hayPares(numPartida)==1)
	{
		
	}
	//Repartimos los puntos de Juego si es que hay
	int juego = hayJuego(numPartida);
	printf ("hayJuego: %d\n", juego);
	if(juego==1)
	{
		int p;
		int pp=0;
		int l;
		for(int a=0;a<4;a++)
		{
			p = milistaPartidas.partidas[numPartida].Mano[a];
			if(milistaPartidas.partidas[numPartida].Juego[p]==1)
			{
				for(int i=0;i<4;i++)
				{
					if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[i]== 10 || milistaPartidas.partidas[numPartida].jugadores[p].Cartas[i]== 9 || milistaPartidas.partidas[numPartida].jugadores[p].Cartas[i]== 8)
						pp = pp + 10;
					else
						pp = pp + milistaPartidas.partidas[numPartida].jugadores[p].Cartas[i];
				}
				if (pp==31)
					pp=8;
				else if (pp==32)
					pp=7;
				else if (pp==40)
					pp=6;
				else if (pp==37)
					pp=5;
				else if (pp==36)
					pp=4;
				else if (pp==35)
					pp=3;
				else if (pp==34)
					pp=2;
				else
					pp=1;
				l=a;
				a=4;
			}
		}
		for(int a=l+1;a<4;a++)
		{
			int q = milistaPartidas.partidas[numPartida].Mano[a];
			if(milistaPartidas.partidas[numPartida].Juego[q]==1)
			{
				int qp=0;
				for(int i=0;i<4;i++)
				{
					if(milistaPartidas.partidas[numPartida].jugadores[q].Cartas[i]== 10 || milistaPartidas.partidas[numPartida].jugadores[q].Cartas[i]== 9 || milistaPartidas.partidas[numPartida].jugadores[q].Cartas[i]== 8)
						qp = qp + 10;
					else
						qp = qp + milistaPartidas.partidas[numPartida].jugadores[q].Cartas[i];
				}
				if (pp==31)
					qp=8;
				else if (pp==32)
					qp=7;
				else if (pp==40)
					qp=6;
				else if (pp==37)
					qp=5;
				else if (pp==36)
					qp=4;
				else if (pp==35)
					qp=3;
				else if (pp==34)
					qp=2;
				else
					qp=1;
				
				if(qp>pp)
				{
					pp=qp;
					p=q;
				}
			}
		}
		if(p==0 || p==2)
		{
			int c;
			if(milistaPartidas.partidas[numPartida].Juego[0]==1)
			{
				int jug=0;
				for(int i=0;i<4;i++)
				{
					if(milistaPartidas.partidas[numPartida].jugadores[0].Cartas[i] == 10 || milistaPartidas.partidas[numPartida].jugadores[0].Cartas[i] == 9 || milistaPartidas.partidas[numPartida].jugadores[0].Cartas[i] == 8)
						jug = jug + 10;
					else
						jug = jug + milistaPartidas.partidas[numPartida].jugadores[0].Cartas[i];
				}
				if(jug==31)
				{
					c = SumarPuntos(numPartida,0,3);
					if(c==-10)
						return -10;
					else if(c==-1)
						return -1;
				}
				else
				{
					c = SumarPuntos(numPartida,0,2);
					if(c==-10)
						return -10;
					else if(c==-1)
						return -1;
				}
			}
			if(milistaPartidas.partidas[numPartida].Juego[2]==1)
			{
				int jug=0;
				for(int i=0;i<4;i++)
				{
					if(milistaPartidas.partidas[numPartida].jugadores[2].Cartas[i] == 10 || milistaPartidas.partidas[numPartida].jugadores[2].Cartas[i] == 9 || milistaPartidas.partidas[numPartida].jugadores[2].Cartas[i] == 8)
						jug = jug + 10;
					else
						jug = jug + milistaPartidas.partidas[numPartida].jugadores[2].Cartas[i];
				}
				if(jug==31)
				{
					c = SumarPuntos(numPartida,0,3);
					if(c==-10)
						return -10;
					else if(c==-1)
						return -1;
				}
				else
				{
					c = SumarPuntos(numPartida,0,2);
					if(c==-10)
						return -10;
					else if(c==-1)
						return -1;
				}
			}
			c = Puntos(numPartida,3,4);
			if(c==-10)
				return -10;
			else if(c==-1)
				return -1;
		}
		else
		{
			int c;
			if(milistaPartidas.partidas[numPartida].Juego[1]==1)
			{
				int jug=0;
				for(int i=0;i<4;i++)
				{
					if(milistaPartidas.partidas[numPartida].jugadores[1].Cartas[i]== 10 || milistaPartidas.partidas[numPartida].jugadores[1].Cartas[i]== 9 || milistaPartidas.partidas[numPartida].jugadores[1].Cartas[i]== 8)
						jug = jug + 10;
					else
						jug = jug + milistaPartidas.partidas[numPartida].jugadores[1].Cartas[i];
				}
				if(jug==31)
				{
					c = SumarPuntos(numPartida,1,3);
					if(c==-11)
						return -11;
					else if(c==-1)
						return -1;
				}
				else
				{
					c = SumarPuntos(numPartida,1,2);
					if(c==-11)
						return -11;
					else if(c==-1)
						return -1;
				}
			}
			if(milistaPartidas.partidas[numPartida].Juego[3]==1)
			{
				int jug=0;
				for(int i=0;i<4;i++)
				{
					if(milistaPartidas.partidas[numPartida].jugadores[3].Cartas[i]== 10 || milistaPartidas.partidas[numPartida].jugadores[3].Cartas[i]== 9 || milistaPartidas.partidas[numPartida].jugadores[3].Cartas[i]== 8)
						jug = jug + 10;
					else
						jug = jug + milistaPartidas.partidas[numPartida].jugadores[3].Cartas[i];
				}
				if(jug==31)
				{
					c = SumarPuntos(numPartida,1,3);
					if(c==-11)
						return -11;
					else if(c==-1)
						return -1;
				}
				else
				{
					c = SumarPuntos(numPartida,1,2);
					if(c==-11)
						return -11;
					else if(c==-1)
						return -1;
				}
			}
			c = Puntos(numPartida,2,4);
			if(c==-11)
				return -11;
			else if(c==-1)
				return -1;
		}
	}
	if(juego==2)
	{
		int c;
		if(milistaPartidas.partidas[numPartida].Juego[0]==1)
		{
			int jug=0;
			for(int i=0;i<4;i++)
			{
				if(milistaPartidas.partidas[numPartida].jugadores[0].Cartas[i]== 10 || milistaPartidas.partidas[numPartida].jugadores[0].Cartas[i]== 9 || milistaPartidas.partidas[numPartida].jugadores[0].Cartas[i]== 8)
					jug = jug + 10;
				else
					jug = jug + milistaPartidas.partidas[numPartida].jugadores[0].Cartas[i];
			}
			if(jug==31)
			{
				c = SumarPuntos(numPartida,0,3);
				if(c==-10)
					return -10;
				else if(c==-1)
					return -1;
			}
			else
			{
				c = SumarPuntos(numPartida,0,2);
				if(c==-10)
					return -10;
				else if(c==-1)
					return -1;
			}
		}
		if(milistaPartidas.partidas[numPartida].Juego[2]==1)
		{
			int jug=0;
			for(int i=0;i<4;i++)
			{
				if(milistaPartidas.partidas[numPartida].jugadores[2].Cartas[i]== 10 || milistaPartidas.partidas[numPartida].jugadores[2].Cartas[i]== 9 || milistaPartidas.partidas[numPartida].jugadores[2].Cartas[i]== 8)
					jug = jug + 10;
				else
					jug = jug + milistaPartidas.partidas[numPartida].jugadores[2].Cartas[i];
			}
			if(jug==31)
			{
				c = SumarPuntos(numPartida,0,3);
				if(c==-10)
					return -10;
				else if(c==-1)
					return -1;
			}
			else
			{
				c = SumarPuntos(numPartida,0,2);
				if(c==-10)
					return -10;
				else if(c==-1)
					return -1;
			}
		}
		c = Puntos(numPartida,3,4);
		if(c==-10)
			return -10;
		else if(c==-1)
			return -1;
	}
	if(juego==3)
	{
		int c;
		if(milistaPartidas.partidas[numPartida].Juego[1]==1)
		{
			int jug=0;
			for(int i=0;i<4;i++)
			{
				if(milistaPartidas.partidas[numPartida].jugadores[1].Cartas[i]== 10 || milistaPartidas.partidas[numPartida].jugadores[1].Cartas[i]== 9 || milistaPartidas.partidas[numPartida].jugadores[1].Cartas[i]== 8)
					jug = jug + 10;
				else
					jug = jug + milistaPartidas.partidas[numPartida].jugadores[1].Cartas[i];
			}
			if(jug==31)
			{
				c = SumarPuntos(numPartida,1,3);
				if(c==-11)
					return -11;
				else if(c==-1)
					return -1;
			}
			else
			{
				c = SumarPuntos(numPartida,1,2);
				if(c==-11)
					return -11;
				else if(c==-1)
					return -1;
			}
		}
		if(milistaPartidas.partidas[numPartida].Juego[3]==1)
		{
			int jug=0;
			for(int i=0;i<4;i++)
			{
				if(milistaPartidas.partidas[numPartida].jugadores[3].Cartas[i]== 10 || milistaPartidas.partidas[numPartida].jugadores[3].Cartas[i]== 9 || milistaPartidas.partidas[numPartida].jugadores[3].Cartas[i]== 8)
					jug = jug + 10;
				else
					jug = jug + milistaPartidas.partidas[numPartida].jugadores[3].Cartas[i];
			}
			if(jug==31)
			{
				c = SumarPuntos(numPartida,1,3);
				if(c==-11)
					return -11;
				else if(c==-1)
					return -1;
			}
			else
			{
				c = SumarPuntos(numPartida,1,2);
				if(c==-11)
					return -11;
				else if(c==-1)
					return -1;
			}
		}
		c = Puntos(numPartida,2,4);
		if(c==-11)
			return -11;
		else if(c==-1)
			return -1;
	}
	//Repartimos los puntos de Punto si se ha jugado
	if(juego==0)
	{
		p = milistaPartidas.partidas[numPartida].Mano[0];
		int pun=0;
		for(int i=0;i<4;i++)
		{
			if(milistaPartidas.partidas[numPartida].jugadores[p].Cartas[i]== 10 || milistaPartidas.partidas[numPartida].jugadores[p].Cartas[i]== 9 || milistaPartidas.partidas[numPartida].jugadores[p].Cartas[i]== 8)
				pun = pun + 10;
			else
				pun = pun + milistaPartidas.partidas[numPartida].jugadores[p].Cartas[i];
		}
		for(int k=1;k<4;k++)
		{
			int cun=0;
			int c = milistaPartidas.partidas[numPartida].Mano[k];
			for(int j=0;j<4;j++)
			{
				if(milistaPartidas.partidas[numPartida].jugadores[c].Cartas[j]== 10 || milistaPartidas.partidas[numPartida].jugadores[c].Cartas[j]== 9 || milistaPartidas.partidas[numPartida].jugadores[c].Cartas[j]== 8)
					cun = cun + 10;
				else
					cun = cun + milistaPartidas.partidas[numPartida].jugadores[c].Cartas[j];
			}
			if(cun > pun)
				p = c;
			
		}
		if(p==0 || p==2)
		{
			int c = Puntos(numPartida,3,5);
			if(c==-10)
				return -10;
			else if(c==-1)
				return -1;
		}
		else
		{
			int c = Puntos(numPartida,2,5);
			if(c==-11)
				return -11;
			else if(c==-1)
				return -1;
		}
	}
}
//La lista se pasa por referencia
int PonConectado (ListaConectados *lista, char nombre[20], int *socket){
	//anade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena
	if(lista->num ==100)
		return -1;
	else
	{
		pthread_mutex_lock(&mutex);//No me interrumpas ahora
		strcpy(lista->conectados[lista->num].nombre, nombre);
		printf("\nSocet:%d",*socket);
		lista->conectados[lista->num].socket= *socket;
		lista->num++;
		pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
		return 0;
	}
}

int EliminaConectado (ListaConectados *lista, Conectado *C){
	//Retorna 0 si se ha eliminado y -1 si el usuario no esta en la lista
	//lista ya es un puntero a la lista y por ello la pongo tal cual sin &
	int pos=DamePosicion (lista, C->nombre);
	if(pos==-1)
		return -1;
	else
	{
		int i;
		pthread_mutex_lock(&mutex);//No me interrumpas ahora
		for(i=pos; i< lista->num-1; i++)
		{
			lista->conectados[i]=lista->conectados[i+1];
			//strcpy(lista->conectados[i].nombre, lista->conectados[i+1].nombre);
			//lista->conectados[i].socket=lista->conectados[i+1].socket;
		}
		lista->num--;
		pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
		return 0;
	}
	
}

void DameConectados(ListaConectados *lista, char *conectados[512]){
	//Pone en conectados los nombres de todos los conectados separados
	//por /.
	//Ejemplo: "Pedro/Mayra/Luis"
	pthread_mutex_lock(&mutex);//No me interrumpas ahora
	int i;
	sprintf(conectados,"");
	for(i=0;i<lista->num;i++)
	{
		sprintf(conectados, "%s/%s", conectados, lista->conectados[i].nombre);
		
	}
	pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
}

int DamePosicion(ListaConectados* lista, char nombre[20]){
	//Devuelve el socket o -1 si no lo ha encontrado en la lista
	//esquema de busqueda
	int i=0;
	int encontrado=0;
	while((i<lista->num)&& (!encontrado))
	{
		if(strcmp(lista->conectados[i].nombre,nombre)==0)
			encontrado=1;
		else
			i++;
	}
	if(encontrado)
							return i;
	else
		return -1;
}

void DameUser(ListaConectados *lista, int socket, char nombre[20]){
	//Devuelve el socket o -1 si no lo ha encontrado en la lista
	//esquema de busqueda
	int i=0;
	int encontrado=0;
	while((i<lista->num)&& (!encontrado))
	{
		if(lista->conectados[i].socket==socket)
			encontrado=1;
		else
			i++;
	}
	if(encontrado)
							sprintf(nombre, "%s", lista->conectados[i].nombre);
	else
		printf("No se ha encontrado ningÃÂºn usuario con ese socket");
}
int CrearPartida(ListaPartidas* lista) {
	//anade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena
	if (lista->num == 100)
		return -1;
	else
	{
		pthread_mutex_lock(&mutex);//No me interrumpas ahora
		lista->partidas[lista->num].empezada = 0;
		for(int i=0; i<4;i++){
		sprintf(lista->partidas[lista->num].jugadores[i].nombre,"");
		}
		lista->num++;
		pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
			return lista->num-1;
		
			printf("num: %d\n",lista->num);

	}
}
int EliminarPartida(ListaPartidas* lista, int partida) {
	//Retorna 0 si se ha eliminado y -1 si el usuario no esta en la lista
	//lista ya es un puntero a la lista y por ello la pongo tal cual sin &



		pthread_mutex_lock(&mutex);//No me interrumpas ahora
		for (int i = partida; i < lista->num; i++) {
			lista->partidas[i] = lista->partidas[i + 1];
		}
		lista->num--;
		pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
		return 0;


}
int EntrarPartida(ListaPartidas* lista, char nombre[20], int pareja, int numPartida) {
	//aÃÂ±ade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena

		pthread_mutex_lock(&mutex);//No me interrumpas ahora
	for(int i=0;i<4;i++){
		if (strcmp(lista->partidas[numPartida].jugadores[i].nombre,"")==0)
		{
			sprintf(lista->partidas[numPartida].jugadores[i].nombre, nombre);
			pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
			return 0;
			
		}

		}
	
	
	pthread_mutex_lock(&mutex);//No me interrumpas ahora
		return -1;
	
}

int SalirPartida(ListaPartidas* lista, char nombre[20],int partida) {
	//Retorna 0 si se ha eliminado y -1 si el usuario no esta en la lista
	//lista ya es un puntero a la lista y por ello la pongo tal cual sin &
	int pos = DamePosicion(lista, nombre);
	if (pos == -1)
		return -1;
	else
	{

		pthread_mutex_lock(&mutex);//No me interrumpas ahora

		sprintf(lista->partidas[partida].jugadores[pos].nombre, "");

		pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
		return 0;
	}

}

void JugadoresEnPartida(ListaPartidas* lista, char* conectados[512],int partida) {
	//Pone en conectados los nombres de todos los conectados separados
	//por /.
	//Ejemplo: "Pedro/Mayra/Luis"
	pthread_mutex_lock(&mutex);//No me interrumpas ahora
	sprintf(conectados, "");
for(int i=0;i<4;i++){
	if(strcmp(lista->partidas[partida].jugadores[i].nombre,"")==0)
		sprintf(conectados, "%s/%s", conectados, lista->partidas[partida].jugadores[i].nombre);
	}
	pthread_mutex_unlock(&mutex);//Ya puedes interrumpir

}
int CambiarPareja(ListaPartidas* lista, int jug1, int jug2, int numPartida) {
	char temp[20];
	sprintf(temp, lista->partidas[numPartida].jugadores[jug1].nombre);
	sprintf(lista->partidas[numPartida].jugadores[jug1].nombre, lista->partidas[numPartida].jugadores[jug2].nombre);
	sprintf(lista->partidas[numPartida].jugadores[jug2].nombre, temp);
}
void EnviarAPatida(char nombre[20],char mensaje[200],int numPartida) {
	char respuesta[20];
	int sock_conn;
		for(int i=0; i<4;i++){
	if(strcmp(milistaPartidas.partidas[numPartida].jugadores[i].nombre,nombre)!=0){
		sock_conn=milistaConectados.conectados[DamePosicion(&milistaConectados, milistaPartidas.partidas[numPartida].jugadores[i].nombre)].socket;
		write(sock_conn, mensaje, strlen(mensaje));
	}}
}
void EnviarAMano(char mensaje[200],int numPartida)
{
	int sock_conn;
	int ma = milistaPartidas.partidas[numPartida].Mano[0];
	sock_conn = milistaConectados.conectados[DamePosicion(&milistaConectados, milistaPartidas.partidas[numPartida].jugadores[ma].nombre)].socket;
	write(sock_conn, mensaje, strlen(mensaje));
	
	
}
void EnviarSiguienteJugador(int numPartida,char mensaje[200],int jugador)
//Envia el mensaje al siguiente jugador de la ronda y retorna su posicion o -1 si la ronda a terminado, no hay siguiente
{
	int siguiente;
	for(int i=0;i<3;i++)
	{
		if(jugador == milistaPartidas.partidas[numPartida].Mano[i])
			siguiente=milistaPartidas.partidas[numPartida].Mano[i+1];
	}
	int sock_conn = milistaConectados.conectados[DamePosicion(&milistaConectados, milistaPartidas.partidas[numPartida].jugadores[siguiente].nombre)].socket;
	write(sock_conn, mensaje, strlen(mensaje));
}

void NotificacionConectados()
{
	char respuesta[20];
	char respuesta2[20];
	
	DameConectados(&milistaConectados, &respuesta);
	printf("wert:%s",respuesta);
	if (respuesta==NULL)
		sprintf(respuesta2, "7/None");
	else
	{	
		sprintf(respuesta2,"7%s",respuesta);
		printf("Resultado: %s", respuesta2);
	}
	int sock_conn;
	for (int i=0;i<=milistaConectados.num;i++){
		
		sock_conn =milistaConectados.conectados[i].socket ;
		printf("Socket:%d\n",sock_conn);
		
		write (sock_conn,respuesta2, strlen(respuesta2));

	}
} 

void* AtenderCliente (void* sock)
{
	printf("inicio");
	int ret;
	int sock_conn = *(int *) sock;
	
	char peticion[512];
	char respuesta[512];
	//Mysql
	MYSQL* conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES* resultado;
	MYSQL_RES* resultado2;
	MYSQL_ROW row;
	int nPartidas = 0;
	char Usuario1[20];
	char Usuario2[20];
	char consulta[250];
	int ID;
	char nombre[20];
	// INICIALITZACIONS
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("Error al crear la conexion: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	//inicializar la conexion
	conn = mysql_real_connect(conn, "localhost", "root", "mysql", "mus", 0, NULL, 0);
	if (conn == NULL) {
		printf("Error al inicializar la conexiÃÂ³n: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	int terminar = 0;
	printf("antes del while");
	while (terminar == 0)
	{
		// Ahora recibimos la petici?n
		sprintf(respuesta,"");
		ret=read(sock_conn,peticion, sizeof(peticion));
		printf ("Recibido\n");
		
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret]='\0';
		
		
		printf ("Peticion: %s\n",peticion);
		
		// vamos a ver que quieren
		char *p = strtok( peticion, "/");
		int codigo =  atoi (p);
		
		
		
		if (codigo !=0 && codigo !=6 && codigo !=7 && codigo != 8 && codigo != 9 && codigo != 10)
		{
			p = strtok( NULL, "/");				// Ya tenemos el nombre
			strcpy(nombre,p);
			printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);
		}
		
		if (codigo == 0){ //petici?n de desconexi?n{
			char nombre[20];
			DameUser(&milistaConectados, sock_conn, nombre);
			EliminaConectado(&milistaConectados, &milistaConectados.conectados[DamePosicion(&milistaConectados, nombre)]);
			terminar=1;}
		else if (codigo == 1) {//Iniciar sesion
			char password[20];
			p = strtok(NULL, "/");				// Ya tenemos el nombre
			strcpy(password, p);
			sprintf(consulta, "SELECT * FROM Jugadores WHERE Username='%s' AND Contrase�a='%s'",nombre,password);
			err = mysql_query(conn, consulta);
			if (err != 0) {
				printf("Error al consultar datos de la base %u %s\n",
					   mysql_errno(conn), mysql_error(conn));
				exit(1);
			}
			resultado = mysql_store_result(conn);
			row = mysql_fetch_row(resultado);

			if (row[0]!=NULL)
			{
				sprintf(respuesta, "1/si");
				PonConectado(&milistaConectados, nombre, &sock_conn);
				NotificacionConectados();
				
			}
			else
				sprintf(respuesta, "1/no");
	
			row = mysql_fetch_row(resultado);
			
			
			
		}
		else if (codigo == 2) {//Registarse
			char password[20];
			p = strtok(NULL, "/");				// Ya tenemos el nombre
			strcpy(password, p);
			sprintf(respuesta, "2/si");
			sprintf(consulta, "SELECT Username FROM Jugadores");
			
			err = mysql_query(conn, consulta);
			if (err != 0) {
				printf("Error al consultar datos de la base %u %s\n",
					   mysql_errno(conn), mysql_error(conn));
				exit(1);
			}
			resultado = mysql_store_result(conn);
			row = mysql_fetch_row(resultado);
			
			printf(row[0]);
			printf("\n");
			while (row != NULL) {
				if (strcmp(row[0] , nombre)==0) {
					sprintf(respuesta, "2/no");
				}
				row = mysql_fetch_row(resultado);
				
			}
			if (strcmp(respuesta, "Registrado") == 0) {
				
				int newID = 0;
				sprintf(consulta, "SELECT ID FROM Jugadores;");
				err = mysql_query(conn, consulta);
				if (err != 0) {
					printf("Error al consultar datos de la base %u %s\n",mysql_errno(conn), mysql_error(conn));
					exit(1);
				}
				resultado = mysql_store_result(conn);
				row = mysql_fetch_row(resultado);
				
				while (row != NULL)
				{
					
					if (newID <= atoi(row[0]))
					{
						newID = atoi(row[0]) + 1;
					}
					row = mysql_fetch_row(resultado);
				}
				printf("%d",newID);
				printf("\n");
				sprintf(consulta, "INSERT INTO Jugadores (ID,Username,Contrase�a) VALUES (%d,'%s','%s')",newID,nombre,password);
				err = mysql_query(conn, consulta);
				if (err != 0) {
					printf("Error al consultar datos de la base %u %s\n",mysql_errno(conn), mysql_error(conn));
					exit(1);
				}
				
			}
		}
		
		else if (codigo ==3){ //parejas con las que ha jugado un jugador
			
			//peticion id del jugador
			strcpy(consulta, "SELECT ID FROM Jugadores WHERE Username='");
			strcat(consulta, nombre);
			strcat(consulta, "'; ");
			err = mysql_query(conn, consulta);
			if (err != 0) {
				printf("Error al consultar datos de la base %u %s\n",
					   mysql_errno(conn), mysql_error(conn));
				exit(1);
			}
			resultado = mysql_store_result(conn);
			row = mysql_fetch_row(resultado);
			ID = atoi(row[0]);
			//peticion tabla de las partidas que ha jugado
			strcpy(consulta, "SELECT * FROM Referencia WHERE Referencia.ID_Partida IN ( SELECT Referencia.ID_Partida FROM Referencia, Jugadores WHERE Jugadores.Username = '");
			strcat(consulta, nombre);
			strcat(consulta, "' AND Referencia.ID_Jugador = Jugadores.ID);");
			err = mysql_query(conn, consulta);
			if (err != 0) {
				printf("Error al consultar datos de la base %u %s\n",
					   mysql_errno(conn), mysql_error(conn));
				exit(1);
			}
			resultado = mysql_store_result(conn);
			row = mysql_fetch_row(resultado);
			//Bucle de busqueda en la tabla
			int ID_P = 2;
			int ID_J = -1;
			int jugadores[3][3];
			printf("%s", "Parejas del jugador:\n");
			if (row == NULL)
				printf("No se han obtenido datos en la consulta\n");
			else {
				int i = 0;
				sprintf(respuesta,"3/");
				while (row != NULL) {
					if (ID == atoi(row[1])) {//comprobamos si es el jugador para memorizar su pareja
						ID_P = atoi(row[2]);
					}
					else {//introducimos en un array para memorizar a los 3 otros jugadores
						jugadores[i][0] = atoi(row[0]);
						jugadores[i][1] = atoi(row[1]);
						jugadores[i][2] = atoi(row[2]);
						i = i + 1;
					}
					if (ID_P != 2 && i == 3) {
						i = -1;
						do {//cogemos el jugador con la misma pareja
							
							i++;
							ID_J = jugadores[i][1];
							
							
						} while (ID_P != jugadores[i][2]);
						i = 0;
						char temp[20];
						sprintf(temp, "%d", ID_J);
						strcpy(consulta, "");
						strcpy(consulta, "SELECT Username FROM Jugadores WHERE ID=");
						strcat(consulta, temp);
						strcat(consulta, "; ");
						err = mysql_query(conn, consulta);
						if (err != 0) {
							printf("Error al consultar datos de la base %u %s\n",
								   mysql_errno(conn), mysql_error(conn));
							exit(1);
						}
						
						resultado2 = mysql_store_result(conn);
						row = mysql_fetch_row(resultado2);
						ID_P = 2;
						strcat(respuesta, row[0]);
						strcat(respuesta, "/");
						printf("%s", row[0]);
						printf("\n");
						
					}
					
					row = mysql_fetch_row(resultado);
				}
			}
			//respuesta[strlen(respuesta - 1)] = "/0";
		}
		
		
		else if (codigo == 4) {
			///consulta Cuantas partidas ha ganado un jugador 
			
			int cont;			//Construimos la consulta
			strcpy (consulta,"SELECT Partidas.ID_Parejaganadora FROM mus.Partidas ");
			//strcpy(consulta, "SELECT Partidas.Idganador FROM Partida,Jugador WHERE ID_s ");
			// hacemos la consulta 
			err = mysql_query(conn, consulta);
			if (err != 0)
			{
				printf("Error al consultar datos de la base %u %s\n",
					   mysql_errno(conn), mysql_error(conn));
				exit(1);
				
			}
			
			//recogemos el resultado de la consulta 
			resultado = mysql_store_result(conn);
			row = mysql_fetch_row(resultado);
			if (row == NULL)
				
				printf("No se han obtenido datos en la consulta\n");
			else
			{
				cont = 0;
				while (row != NULL)
				{
					printf("%s \n", row[0]);
					row = mysql_fetch_row(resultado);
					cont++;
					
				}
				sprintf(respuesta,"4/%d", cont);
			}
		}
		else if (codigo == 5)  //Consulta de Andoni
		{
			sprintf(respuesta,"5/");
			nPartidas=0;
			strcpy(Usuario1,nombre);
			p = strtok( NULL, "/");	
			strcpy(Usuario2,p);
			printf("%s, %s\n", Usuario1, Usuario2);
			sprintf (consulta,"SELECT Referencia.ID_Partida FROM (Jugadores, Referencia) WHERE Referencia.ID_Partida IN(SELECT Referencia.ID_Partida FROM(Jugadores, Referencia) WHERE Jugadores.Username = '%s' AND Jugadores.ID = Referencia.ID_Jugador) AND Jugadores.Username = '%s' AND Referencia.ID_Jugador = Jugadores.ID", Usuario1, Usuario2);
			// hacemos la consulta 
			err = mysql_query(conn, consulta);
			if (err != 0) {
				printf("Error al consultar datos de la base %u %s\n",
					   mysql_errno(conn), mysql_error(conn));
				exit(1);
			}
			//recogemos el resultado de la consulta 
			resultado = mysql_store_result(conn);
			row = mysql_fetch_row(resultado);
			if (row == NULL)
				printf("No se han obtenido datos en la consulta\n");
			else{
				while (row !=NULL) {
					int Pa = atoi (row[0]);
					char consulta1 [500];
					char consulta2 [500];
					int errJ1;
					int errJ2;
					MYSQL_RES *resultadoJ1;
					MYSQL_ROW rowJ1;
					MYSQL_RES *resultadoJ2;
					MYSQL_ROW rowJ2;
					
					sprintf (consulta1,"SELECT Referencia.ID_Pareja FROM (Jugadores, Referencia) WHERE Referencia.ID_Partida = %d AND Jugadores.Username = '%s' AND Referencia.ID_Jugador = Jugadores.ID", Pa, Usuario1);
					sprintf (consulta2,"SELECT Referencia.ID_Pareja FROM (Jugadores, Referencia) WHERE Referencia.ID_Partida = %d AND Jugadores.Username = '%s' AND Referencia.ID_Jugador = Jugadores.ID", Pa, Usuario2);
					errJ1=mysql_query (conn, consulta1);
					if (errJ1 != 0){
						printf ("Error al consultar datos de la base %u %s\n",
								mysql_errno(conn), mysql_error(conn));
						exit (1);
					}
					resultadoJ1 = mysql_store_result (conn);
					rowJ1 = mysql_fetch_row (resultadoJ1);
					int Pj1 = atoi (rowJ1[0]);
					
					errJ2=mysql_query (conn, consulta2);
					if (errJ2 != 0){
						printf ("Error al consultar datos de la base %u %s\n",
								mysql_errno(conn), mysql_error(conn));
						exit (1);
					}
					resultadoJ2 = mysql_store_result (conn);
					rowJ2 = mysql_fetch_row (resultadoJ2);
					int Pj2 = atoi (rowJ2[0]);
					
					if (Pj1 == Pj2){
						nPartidas++;
					}
					row = mysql_fetch_row (resultado);
				}
				
			}
			sprintf(respuesta,"5/%d", nPartidas);
		}
		else if (codigo == 6)//Peticiones realizadas por el servidor
		{
			printf("%d", contadorservicios);
			sprintf(respuesta, "6/%d", contadorservicios);
		}
		else if (codigo == 7)//Lista conectados
		{
			DameConectados(&milistaConectados, respuesta);
			if (respuesta==NULL)
				strcpy(respuesta, "7/None");
			else
			{	
				sprintf(respuesta,"7/%s",respuesta);
				printf("Resultado: %s\n", respuesta);
			}
			
		}
		else if (codigo == 8) {
			char miNombre[20];
			char respuestaOtro[20];
			int sock_conn2;
			DameConectados(&milistaConectados, respuesta);
			p = strtok(NULL, "/");				// Conseguimos la peticion secundaria
			int peticion = atoi(p);

			p = strtok(NULL, "/");				//Conseguimos el numero de partida
			int numPartida = atoi(p);
			int pareja;
			int pos;
			int pos2;
			int err;
			p = strtok(NULL, "/");				// Conseguimos el nombre
			strcpy(nombre,p);
			DameUser(&milistaConectados, sock_conn, miNombre);
			switch (peticion)
			{
				case 1:
					pareja=0;
					if (numPartida == -1) {
						numPartida = CrearPartida(&milistaPartidas);
						sprintf(respuesta, "8/1/%d/%s",  numPartida, miNombre);
						err = EntrarPartida(&milistaPartidas, miNombre, pareja, numPartida);
					}
					else
						sprintf(respuesta, "");
					int pos = DamePosicion(&milistaConectados, nombre);
					sock_conn2 = milistaConectados.conectados[pos].socket;
					sprintf(respuestaOtro, "8/1/%d/%s", numPartida, miNombre);
					write(sock_conn2, respuestaOtro, strlen(respuestaOtro));
					break;
				case 2:
					sprintf(respuesta, "");
					pareja = 0;
					err = EntrarPartida(&milistaPartidas, miNombre, pareja, numPartida);
					if (err == 0) {
						sprintf(respuestaOtro, "8/2/%d/%s", numPartida,miNombre);
						int pos = DamePosicion(&milistaConectados, miNombre);
						sock_conn2 = milistaConectados.conectados[pos].socket;
						write(sock_conn2, respuestaOtro, strlen(respuestaOtro));
						sprintf(respuestaOtro, "8/6/%d/%s/%s/%s/%s", numPartida, milistaPartidas.partidas[numPartida].jugadores[0].nombre,milistaPartidas.partidas[numPartida].jugadores[1].nombre,milistaPartidas.partidas[numPartida].jugadores[2].nombre,milistaPartidas.partidas[numPartida].jugadores[3].nombre);
						EnviarAPatida("", respuestaOtro, numPartida);
						printf("\nPetticion:%s\n",respuestaOtro);


					}
					else if (err == -1) {
						int pos = DamePosicion(&milistaConectados, nombre);
						sock_conn2 = milistaConectados.conectados[pos].socket;
						sprintf(respuestaOtro, "8/2/%d/lleno", numPartida);
						write(sock_conn2, respuestaOtro, strlen(respuestaOtro));
					}

					break;
				case 3:
					pos = DamePosicion(&milistaConectados, nombre);
					sock_conn2 = milistaConectados.conectados[pos].socket;
					sprintf(respuestaOtro, "8/3/%d/%s", numPartida, nombre);
					write(sock_conn2, respuestaOtro, strlen(respuestaOtro));
					break;
				case 4:
					SalirPartida(&milistaPartidas, miNombre, numPartida);
					sprintf(respuestaOtro, "8/4/%d/%s", numPartida, miNombre);
					EnviarAPatida(miNombre, respuestaOtro, numPartida);
					break;
				case 5:
					pos=atoi(nombre);
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					pos2 = atoi(p);

					if(milistaPartidas.partidas[numPartida].jugadores[pos2].nombre!=""){
					sprintf(respuestaOtro, "8/7/%d/%d/%d", numPartida, pos,pos2);
					sock_conn2 = milistaConectados.conectados[DamePosicion(&milistaConectados,milistaPartidas.partidas[numPartida].jugadores[pos].nombre)].socket;
					write(sock_conn2, respuestaOtro, strlen(respuestaOtro));
					}
					else{
						pos=atoi(nombre);
						p = strtok(NULL, "/");				//Conseguimos el numero de partida
						pos2 = atoi(p);
						CambiarPareja(&milistaPartidas, pos, pos2, numPartida);
						sprintf(respuestaOtro, "8/6/%d/%s/%s/%s/%s", numPartida, milistaPartidas.partidas[numPartida].jugadores[0].nombre,milistaPartidas.partidas[numPartida].jugadores[1].nombre,milistaPartidas.partidas[numPartida].jugadores[2].nombre,milistaPartidas.partidas[numPartida].jugadores[3].nombre);
						EnviarAPatida("", respuestaOtro, numPartida);
					}

					break;
				case 7:
					pos=atoi(nombre);
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					pos2 = atoi(p);
					CambiarPareja(&milistaPartidas, pos, pos2, numPartida);
					sprintf(respuestaOtro, "8/6/%d/%s/%s/%s/%s", numPartida, milistaPartidas.partidas[numPartida].jugadores[0].nombre,milistaPartidas.partidas[numPartida].jugadores[1].nombre,milistaPartidas.partidas[numPartida].jugadores[2].nombre,milistaPartidas.partidas[numPartida].jugadores[3].nombre);
					EnviarAPatida("", respuestaOtro, numPartida);
					break;
				case 8:
					sprintf(respuestaOtro, "8/8/%d",numPartida);
					EnviarAPatida(nombre, respuestaOtro, numPartida);
					InicioPartida(numPartida,0);
					BarajarBaraja(numPartida);
					ManoInicial(numPartida);
					Repartir(numPartida);
					EnviarCartas(numPartida);
					sprintf(respuesta,"");
					break;
						
			default:
				break;
			}}
		else if (codigo == 9) {//chat
			p = strtok(NULL, "/");				// Ya tenemos la peticion
			int numPartida = atoi(p);
			p = strtok(NULL, "/");				// Ya tenemos la peticion
			char miNombre[20];
			strcpy(miNombre,p);
			p = strtok(NULL, "/");				// Ya tenemos la peticion
			char mensaje[20];
			strcpy(mensaje,p);
			sprintf(peticion,"%d/%d/%s/%s",codigo,numPartida,miNombre,mensaje);
			EnviarAPatida(miNombre, peticion, numPartida);

		}
		
		else if (codigo == 10)
		{
			p = strtok(NULL, "/");
			int numPartida = atoi(p);
			p = strtok(NULL, "/");				//Conseguimos el numero de partida
			int ronda = atoi(p);
			p = strtok(NULL, "/");				// Conseguimos el nombre
			int jugador = atoi(p);
			char Respuesta[200];
			char miNombre[20];
			DameNombre(numPartida,jugador, miNombre);
			char caso[20];
			char peticion[20];
			
			switch (ronda)
			{
			case 0://Ronda de Mus (P=Pregunta, A=Descarte)
				p = strtok(NULL, "/");
				strcpy(peticion,p);
				if (strcmp(peticion, "NO")==0)
				{
					sprintf(Respuesta, "11/%d/0/%d/CORTO", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
					sprintf(Respuesta, "10/%d/2/P", numPartida);
					printf("Respuesta: %s\n", Respuesta);
					usleep(80000);
					EnviarAMano(Respuesta, numPartida);
				}
				else
				{
					sprintf(Respuesta, "11/%d/0/%d/MUS", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
					usleep(80000);
					if (jugador!=DamejugadorPosicion(numPartida,3))
					{
						sprintf(Respuesta, "10/%d/0", numPartida);
						printf("Respuesta: %s\n", Respuesta);
						EnviarSiguienteJugador(numPartida,Respuesta, jugador);
					}
					else
					{
						sprintf(Respuesta, "10/%d/1", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
				}
				break;	
			case 1: //Descarte
				p = strtok(NULL, "/");
				int numCartas = atoi(p);
				for(int c=0;c<numCartas;c++)
				{
					p = strtok(NULL, "/");
					int Carta = atoi(p);
					Mus(numPartida,jugador,Carta);
				}
				sprintf(Respuesta, "11/%d/1/%d/%d", numPartida, jugador, numCartas);
				EnviarAPatida("", Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
				usleep(50000);
				sprintf(Respuesta, "11/%d/10/%d/%d/%d/%d/%d", numPartida, jugador, milistaPartidas.partidas[numPartida].jugadores[jugador].Cartas[0],milistaPartidas.partidas[numPartida].jugadores[jugador].Cartas[1],milistaPartidas.partidas[numPartida].jugadores[jugador].Cartas[2],milistaPartidas.partidas[numPartida].jugadores[jugador].Cartas[3]);
				EnviarAPatida("", Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
				usleep(50000);

				if (jugador!=DamejugadorPosicion(numPartida,3))
				{
					sprintf(Respuesta, "10/%d/1/", numPartida);
					EnviarSiguienteJugador(numPartida,Respuesta, jugador);
				}
				else
				{
					sprintf(Respuesta, "10/%d/0", numPartida);
					EnviarAMano(Respuesta, numPartida);
				}
				break;
			case 2://Mayores
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if (strcmp(caso, "PASO")==0)
				{
					sprintf(Respuesta, "11/%d/2/%d/PASA", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(80000);
					if (jugador!=DamejugadorPosicion(numPartida,3))
					{
						sprintf(Respuesta, "10/%d/2/P", numPartida);
						EnviarSiguienteJugador(numPartida,Respuesta, jugador);
					}
					else
					{
						sprintf(Respuesta, "11/%d/2/%d/SE FUE", numPartida, jugador);
						EnviarAPatida("", Respuesta, numPartida);
						Apostar(numPartida,1,0);
						printf ("Respuesta: %s\n", Respuesta);
						usleep(80000);
						sprintf(Respuesta, "10/%d/3/P", numPartida);
						EnviarAMano(Respuesta, numPartida);
						printf ("Respuesta: %s\n", Respuesta);
					}
				}
				else if(strcmp(caso, "APUESTO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Reapuesta = atoi(p);
					if(Reapuesta==0)
						Apostar(numPartida, 1, 1);
					else
						Apostar(numPartida, 1, Reapuesta);
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/2/%d/%d", numPartida, jugador, Apuesta);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(80000);
					sprintf(Respuesta, "10/%d/2/A/%d", numPartida, Apuesta);
					if (jugador == DamejugadorPosicion(numPartida,0) || jugador == DamejugadorPosicion(numPartida,2))
						EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,0));
					else
						EnviarAMano(Respuesta, numPartida);
				}
				else if(strcmp(caso, "QUIERO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/2/%d/QUIERE", numPartida, jugador);
					Apostar(numPartida, 1, Apuesta);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(80000);
					sprintf(Respuesta, "10/%d/3/P", numPartida);
					EnviarAMano(Respuesta, numPartida);
				}
				else
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/2/%d/NO QUIRE", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(80000);
					if(jugador!=DamejugadorPosicion(numPartida,0) && jugador!=DamejugadorPosicion(numPartida,1))
					{
						int p = Puntos(numPartida,jugador,1);
						Apostar(numPartida, 1, -1);
						if(p==0)
						{
							sprintf(Respuesta, "10/%d/3/P", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
						else if(p==-1)
						{
							InicioPartida(numPartida , 1);
							BarajarBaraja(numPartida);
							PasarMano(numPartida);
							Repartir(numPartida);
							usleep(80000);
							EnviarCartas(numPartida);
							usleep(80000);
							sprintf(Respuesta, "10/%d/0", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
						else if(p==-10)
						{
							sprintf(Respuesta, "11/%d/20", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
						else
						{
							sprintf(Respuesta, "11/%d/21", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
					}
					else
					{
					   sprintf(Respuesta, "10/%d/2/A/%d", numPartida, Apuesta);
							if(jugador==DamejugadorPosicion(numPartida,0))
								EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,1));
						   else
								EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,2));
					}
				}
				break;
			case 3://Pequena
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if (strcmp(caso, "PASO")==0)
				{
					sprintf(Respuesta, "11/%d/3/%d/PASA", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(80000);
					if (jugador!=DamejugadorPosicion(numPartida,3))
					{
						sprintf(Respuesta, "10/%d/3/P", numPartida);
						EnviarSiguienteJugador(numPartida,Respuesta, jugador);
					}
					else
					{
						sprintf(Respuesta, "11/%d/3/%d/SE FUE", numPartida, jugador);
						EnviarAPatida("", Respuesta, numPartida);
						Apostar(numPartida,2,0);
						usleep(80000);
						sprintf(Respuesta, "10/%d/4", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
				}
				else if(strcmp(caso, "APUESTO")==0)
				{
					p = strtok(NULL, "/");
					int Reapuesta = atoi(p);
					if(Reapuesta==0)
						Apostar(numPartida, 2, 1);
					else
						Apostar(numPartida, 2, Reapuesta);//Conseguimos el numero de partida
					p = strtok(NULL, "/");
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/3/%d/%d", numPartida, jugador, Apuesta);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					sprintf(Respuesta, "10/%d/3/A/%d", numPartida, Apuesta);
					if (jugador == DamejugadorPosicion(numPartida,0) || jugador ==DamejugadorPosicion(numPartida,2))
						EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,0));
					else
						EnviarAMano(Respuesta, numPartida);
				}
				else if(strcmp(caso, "QUIERO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/3/%d/QUIERE", numPartida, jugador);
					Apostar(numPartida, 2, Apuesta);
					usleep(50000);
					EnviarAPatida("", Respuesta, numPartida);
					sprintf(Respuesta, "10/%d/4", numPartida);
					EnviarAMano(Respuesta, numPartida);
				}
				else
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/3/%d/NO QUIRE", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					if(jugador!=DamejugadorPosicion(numPartida,0) && jugador!=DamejugadorPosicion(numPartida,1))
					{
						int p = Puntos(numPartida,jugador,2);
						Apostar(numPartida, 2, -1);
						if(p==0)
						{
							sprintf(Respuesta, "10/%d/4", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
						else if(p==-1)
						{
							InicioPartida(numPartida , 1);
							BarajarBaraja(numPartida);
							PasarMano(numPartida);
							Repartir(numPartida);
							usleep(50000);
							EnviarCartas(numPartida);
							usleep(50000);
							sprintf(Respuesta, "10/%d/0", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
						else if(p==-10)
						{
							sprintf(Respuesta, "11/%d/20", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
						else
						{
							sprintf(Respuesta, "11/%d/21", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
					}
					else
					{
						sprintf(Respuesta, "10/%d/3/A/%d", numPartida, Apuesta);
						if(jugador==DamejugadorPosicion(numPartida,0))
							EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,1));
						else
							EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,2));
					}
				}
				break;
			case 4://Pares (Pregunta)
					p = strtok(NULL, "/");
					strcpy(peticion,p);
					if (strcmp(peticion, "NO")==0)
					{
						sprintf(Respuesta, "11/%d/4/%d/PARES NO", numPartida, jugador);
						EnviarAPatida("", Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
						HayPares(numPartida,jugador,0);
						usleep(50000);
						if (jugador==DamejugadorPosicion(numPartida,3))
						{
							int h = hayPares(numPartida);
							printf ("hayPares: %d\n", h);
							
							if (h==1)
							{
								sprintf(Respuesta, "10/%d/5/P", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
							else
							{
								sprintf(Respuesta, "10/%d/6", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
						}
						else
						{
							sprintf(Respuesta, "10/%d/4", numPartida);
							EnviarSiguienteJugador(numPartida, Respuesta, jugador);
						}
					}
					else
					{
						sprintf(Respuesta, "11/%d/4/%d/PARES SI", numPartida, jugador);
						EnviarAPatida("", Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
						HayPares(numPartida,jugador,1);
						usleep(50000);
						if (jugador==DamejugadorPosicion(numPartida,3))
						{
							int h = hayPares(numPartida);
							if (h==1)
							{
								sprintf(Respuesta, "10/%d/5/P", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
							else
							{
								sprintf(Respuesta, "10/%d/6", numPartida);
								EnviarAMano(Respuesta, numPartida);
								Apostar(numPartida,3,-1);
							}
						}
						else
						{						
							sprintf(Respuesta, "10/%d/4", numPartida);
							EnviarSiguienteJugador(numPartida, Respuesta, jugador);
						}
					}
				break;
			case 5: //Pares (Apuesta)
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if (strcmp(caso, "PASO")==0)
				{
					sprintf(Respuesta, "11/%d/5/%d/PASA", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					if (jugador!=DamejugadorPosicion(numPartida,3))
					{
						sprintf(Respuesta, "10/%d/5/P", numPartida);
						EnviarSiguienteJugador(numPartida,Respuesta, jugador);
					}
					else
					{
						sprintf(Respuesta, "11/%d/5/%d/SE FUE", numPartida, jugador);
						EnviarAPatida("", Respuesta, numPartida);
						Apostar(numPartida,3,0);
						usleep(50000);
						sprintf(Respuesta, "10/%d/6", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
				}
				else if(strcmp(caso, "APUESTO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Reapuesta = atoi(p);
					if(Reapuesta==0)
						Apostar(numPartida, 3, 1);
					else
						Apostar(numPartida, 3, Reapuesta);
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/5/%d/%d", numPartida, jugador, Apuesta);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					sprintf(Respuesta, "10/%d/5/A/%d", numPartida, Apuesta);
					if (jugador == DamejugadorPosicion(numPartida,0) || jugador ==DamejugadorPosicion(numPartida,2))
						EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,0));
					else
						EnviarAMano(Respuesta, numPartida);
				}
				else if(strcmp(caso, "QUIERO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/5/%d/QUIERE", numPartida, jugador);
					Apostar(numPartida, 3, Apuesta);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					sprintf(Respuesta, "10/%d/6", numPartida);
					EnviarAMano(Respuesta, numPartida);
				}
				else
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/5/%d/NO QUIRE", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					if(jugador!=DamejugadorPosicion(numPartida,0) && jugador!=DamejugadorPosicion(numPartida,1))
					{
						int p = Puntos(numPartida,jugador,3);
						Apostar(numPartida, 3, -1);
						if(p==0)
						{
							sprintf(Respuesta, "10/%d/6", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
						else if(p==-1)
						{
							InicioPartida(numPartida , 1);
							BarajarBaraja(numPartida);
							PasarMano(numPartida);
							Repartir(numPartida);
							usleep(50000);
							EnviarCartas(numPartida);
							usleep(50000);
							sprintf(Respuesta, "10/%d/0", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
						else if(p==-10)
						{
							sprintf(Respuesta, "11/%d/20", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
						else
						{
							sprintf(Respuesta, "11/%d/21", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
					}
					else
					{
						sprintf(Respuesta, "10/%d/5/A/%d", numPartida, Apuesta);
						if(jugador==DamejugadorPosicion(numPartida,0))
							EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,1));
						else
							EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,2));
					}
				}
				break;
			case 6://Juego (Pregunta)
				p = strtok(NULL, "/");
				strcpy(peticion,p);
				if (strcmp(peticion, "NO")==0)
				{
					sprintf(Respuesta, "11/%d/6/%d/JUEGO NO", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
					HayJuego(numPartida,jugador,0);
					usleep(80000);
					if (jugador==DamejugadorPosicion(numPartida,3))
					{
						int h = hayJuego(numPartida);
						if (h==1)
						{
							sprintf(Respuesta, "10/%d/7/P", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
						else if(h==0)
						{
							sprintf(Respuesta, "10/%d/8/P", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
						else
						{
							int p = ContarPuntos(numPartida);
							if(p==-10)
							{
								sprintf(Respuesta, "11/%d/20", numPartida);
								EnviarAPatida("", Respuesta, numPartida);
							}
							else if(p==-11)
							{
								sprintf(Respuesta, "11/%d/21", numPartida);
								EnviarAPatida("", Respuesta, numPartida);
							}
							else
							{
								InicioPartida(numPartida , 1);
								BarajarBaraja(numPartida);
								PasarMano(numPartida);
								Repartir(numPartida);
								usleep(50000);
								EnviarCartas(numPartida);
								usleep(50000);
								sprintf(Respuesta, "10/%d/0", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
						}
					}
					else
					{
						sprintf(Respuesta, "10/%d/6", numPartida);
						EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,jugador));
					}
				}
				else
				{
					sprintf(Respuesta, "11/%d/6/%d/JUEGO SI", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
					HayJuego(numPartida,jugador,1);
					usleep(80000);
					if (jugador==DamejugadorPosicion(numPartida,3))
					{
						int h = hayJuego(numPartida);
						if (h==1)
						{
							sprintf(Respuesta, "10/%d/7/P", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
						else
						{
							int p = ContarPuntos(numPartida);
							if(p==-10)
							{
								sprintf(Respuesta, "11/%d/20", numPartida);
								EnviarAPatida("", Respuesta, numPartida);
							}
							else if(p==-11)
							{
								sprintf(Respuesta, "11/%d/21", numPartida);
								EnviarAPatida("", Respuesta, numPartida);
							}
							else
							{
								InicioPartida(numPartida , 1);
								BarajarBaraja(numPartida);
								PasarMano(numPartida);
								Repartir(numPartida);
								usleep(50000);
								EnviarCartas(numPartida);
								usleep(50000);
								sprintf(Respuesta, "10/%d/0", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
						}
					}
					else
					{
						sprintf(Respuesta, "10/%d/6", numPartida);
						EnviarSiguienteJugador(numPartida, Respuesta, jugador);
					}
				}
				break;
			case 7:
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if (strcmp(caso, "PASO")==0)
				{
					sprintf(Respuesta, "11/%d/7/%d/PASA", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					if (jugador!=DamejugadorPosicion(numPartida,3))
					{
						sprintf(Respuesta, "10/%d/7/P", numPartida);
						EnviarSiguienteJugador(numPartida,Respuesta, jugador);
					}
					else
					{
						sprintf(Respuesta, "11/%d/7/%d/SE FUE", numPartida, jugador);
						EnviarAPatida("", Respuesta, numPartida);
						Apostar(numPartida,4,0);
						usleep(50000);
						int p = ContarPuntos(numPartida);
						if(p==-10)
						{
							sprintf(Respuesta, "11/%d/20", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
						else if(p==-11)
						{
							sprintf(Respuesta, "11/%d/21", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
						else
						{
							InicioPartida(numPartida , 1);
							BarajarBaraja(numPartida);
							PasarMano(numPartida);
							Repartir(numPartida);
							usleep(50000);
							EnviarCartas(numPartida);
							usleep(50000);
							sprintf(Respuesta, "10/%d/0", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
					}
				}
				else if(strcmp(caso, "APUESTO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Reapuesta = atoi(p);
					if(Reapuesta==0)
						Apostar(numPartida, 4, 1);
					else
						Apostar(numPartida, 4, Reapuesta);
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/7/%d/%d", numPartida, jugador, Apuesta);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					sprintf(Respuesta, "10/%d/7/A/%d", numPartida, Apuesta);
					if (jugador == DamejugadorPosicion(numPartida,0) || jugador ==DamejugadorPosicion(numPartida,2))
						EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,0));
					else
						EnviarAMano(Respuesta, numPartida);
				}
				else if(strcmp(caso, "QUIERO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/7/%d/QUIERE", numPartida, jugador);
					Apostar(numPartida, 4, Apuesta);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					int p = ContarPuntos(numPartida);
					if(p==-10)
					{
						sprintf(Respuesta, "11/%d/20", numPartida);
						EnviarAPatida("", Respuesta, numPartida);
					}
					else if(p==-11)
					{
						sprintf(Respuesta, "11/%d/21", numPartida);
						EnviarAPatida("", Respuesta, numPartida);
					}
					else
					{
						InicioPartida(numPartida , 1);
						BarajarBaraja(numPartida);
						PasarMano(numPartida);
						Repartir(numPartida);
						usleep(50000);
						EnviarCartas(numPartida);
						usleep(50000);
						sprintf(Respuesta, "10/%d/0", numPartida);
						EnviarAMano(Respuesta, numPartida);
						usleep(50000);
						sprintf(Respuesta, "11/%d/13", numPartida);
						EnviarAPatida("",Respuesta, numPartida);
					}
				}
				else
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/7/%d/NO QUIRE", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					if(jugador!=DamejugadorPosicion(numPartida,0) && jugador!=DamejugadorPosicion(numPartida,1))
					{
						int p = Puntos(numPartida,jugador,4);
						Apostar(numPartida, 4, -1);
						if(p==0)
						{
							p = ContarPuntos(numPartida);
							if(p==-10)
							{
								sprintf(Respuesta, "11/%d/20", numPartida);
								EnviarAPatida("", Respuesta, numPartida);
							}
							else if(p==-11)
							{
								sprintf(Respuesta, "11/%d/21", numPartida);
								EnviarAPatida("", Respuesta, numPartida);
							}
							else
							{
								InicioPartida(numPartida , 1);
								BarajarBaraja(numPartida);
								PasarMano(numPartida);
								Repartir(numPartida);
								usleep(50000);
								EnviarCartas(numPartida);
								usleep(50000);
								sprintf(Respuesta, "10/%d/0", numPartida);
								EnviarAMano(Respuesta, numPartida);
								usleep(50000);
								sprintf(Respuesta, "11/%d/13", numPartida);
								EnviarAPatida("",Respuesta, numPartida);
								
							}
						}
						else if(p==-10)
						{
							sprintf(Respuesta, "11/%d/20", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
						else
						{
							sprintf(Respuesta, "11/%d/21", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
					}
					else
					{
						sprintf(Respuesta, "10/%d/7/A/%d", numPartida, Apuesta);
						if(jugador==DamejugadorPosicion(numPartida,0))
							EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,1));
						else
							EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,2));
					}
				}
				break;
			case 8://Punto
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if (strcmp(caso, "PASO")==0)
				{
					sprintf(Respuesta, "11/%d/8/%d/PASA", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					if (jugador!=DamejugadorPosicion(numPartida,3))
					{
						sprintf(Respuesta, "10/%d/8/P", numPartida);
						EnviarSiguienteJugador(numPartida,Respuesta, jugador);
					}
					else
					{
						sprintf(Respuesta, "11/%d/8/%d/SE FUE", numPartida, jugador);
						EnviarAPatida("", Respuesta, numPartida);
						usleep(50000);
						Apostar(numPartida,5,0);
						int p = ContarPuntos(numPartida);
						if(p==-10)
						{
							sprintf(Respuesta, "11/%d/20", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
						else if(p==-11)
						{
							sprintf(Respuesta, "11/%d/21", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
						else
						{
							InicioPartida(numPartida , 1);
							BarajarBaraja(numPartida);
							PasarMano(numPartida);
							Repartir(numPartida);
							usleep(50000);
							EnviarCartas(numPartida);
							usleep(50000);
							sprintf(Respuesta, "10/%d/0", numPartida);
							EnviarAMano(Respuesta, numPartida);
							usleep(50000);
							sprintf(Respuesta, "11/%d/13", numPartida);
							EnviarAPatida("",Respuesta, numPartida);
							
						}
					}
				}
				else if(strcmp(caso, "APUESTO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Reapuesta = atoi(p);
					if(Reapuesta==0)
						Apostar(numPartida, 5, 1);
					else
						Apostar(numPartida, 5, Reapuesta);
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/8/%d/%d", numPartida, jugador, Apuesta);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					sprintf(Respuesta, "10/%d/8/A/%d", numPartida, Apuesta);
					if (jugador == DamejugadorPosicion(numPartida,0) || jugador ==DamejugadorPosicion(numPartida,2))
						EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,0));
					else
						EnviarAMano(Respuesta, numPartida);
				}
				else if(strcmp(caso, "QUIERO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/8/%d/QUIERE", numPartida, jugador);
					Apostar(numPartida, 5, Apuesta);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					int p = ContarPuntos(numPartida);
					if(p==-10)
					{
						sprintf(Respuesta, "11/%d/20", numPartida);
						EnviarAPatida("", Respuesta, numPartida);
					}
					else if(p==-11)
					{
						sprintf(Respuesta, "11/%d/21", numPartida);
						EnviarAPatida("", Respuesta, numPartida);
					}
					else
					{
						InicioPartida(numPartida, 1);
						BarajarBaraja(numPartida);
						PasarMano(numPartida);
						Repartir(numPartida);
						usleep(50000);
						EnviarCartas(numPartida);
						usleep(50000);
						sprintf(Respuesta, "10/%d/0", numPartida);
						EnviarAMano(Respuesta, numPartida);
						usleep(50000);
						sprintf(Respuesta, "11/%d/13", numPartida);
						EnviarAPatida("",Respuesta, numPartida);
						
					}
				}
				else
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/8/%d/NO QUIRE", numPartida, jugador);
					EnviarAPatida("", Respuesta, numPartida);
					usleep(50000);
					if(jugador!=DamejugadorPosicion(numPartida,0) && jugador!=DamejugadorPosicion(numPartida,1))
					{
						int p = Puntos(numPartida,jugador,5);
						Apostar(numPartida, 5, -1);
						if(p==0)
						{
							p = ContarPuntos(numPartida);
							if(p==-10)
							{
								sprintf(Respuesta, "11/%d/20", numPartida);
								EnviarAPatida("", Respuesta, numPartida);
							}
							else if(p==-11)
							{
								sprintf(Respuesta, "11/%d/21", numPartida);
								EnviarAPatida("", Respuesta, numPartida);
							}
							else
							{
								InicioPartida(numPartida , 1);
								BarajarBaraja(numPartida);
								PasarMano(numPartida);
								Repartir(numPartida);
								usleep(50000);
								EnviarCartas(numPartida);
								usleep(50000);
								sprintf(Respuesta, "10/%d/0", numPartida);
								EnviarAMano(Respuesta, numPartida);
								usleep(50000);
								sprintf(Respuesta, "11/%d/13", numPartida);
								EnviarAPatida("",Respuesta, numPartida);
								
							}
						}
						else if(p==-10)
						{
							sprintf(Respuesta, "11/%d/20", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
						else
						{
							sprintf(Respuesta, "11/%d/21", numPartida);
							EnviarAPatida("", Respuesta, numPartida);
						}
					}
					else
					{
						sprintf(Respuesta, "10/%d/8/A/%d", numPartida, Apuesta);
						if(jugador==DamejugadorPosicion(numPartida,0))
							EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,1));
						else
							EnviarSiguienteJugador(numPartida, Respuesta, DamejugadorPosicion(numPartida,2));
					}
				}
				break;
			default:
				break;
			}
		}

		
		
		if (codigo !=0 && codigo!=9 && codigo!=10)
		{	
			printf("Soket:%d\n",sock_conn);
			
			// Enviamos respuesta
			if(codigo !=-5){
				printf ("Respuesta: %s\n", respuesta);
				
			write (sock_conn,respuesta, strlen(respuesta));}
			if (codigo != 1 && codigo != 2)
			{
				pthread_mutex_lock(&mutex);//No me interrumpas
				contadorservicios++;
				pthread_mutex_unlock(&mutex);//Ahora puedes interrumpirme
			}
		}
	}
	// Se acabo el servicio para este cliente
	mysql_close(conn);
	close(sock_conn); 
	return NULL;
}

int main(int argc, char *argv[]) 
{
	
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;
	
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// establecemos el puerto de escucha
	serv_adr.sin_port = htons(9020);
	//setsockopt(*sock_listen, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	int i;
	int err;
	pthread_t thread[25];
	int sock[25];
	contadorservicios = 0;
	milistaConectados.num=0;
	// Bucle infinito
	for (i=0;i<25;i++){
		printf ("Escuchando\n");
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		//sock_conn es el socket que usaremos para este cliente
		sock[i] = sock_conn;
		
		//Creamos el thread y decirle lo que tiene que hacer
		err=pthread_create(&thread[i],NULL,AtenderCliente,&sock[i]);
		printf("%d",err);
		
	}
}
