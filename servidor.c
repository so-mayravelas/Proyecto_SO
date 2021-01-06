#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <pthread.h>

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
	int PuntosP0[2];
	int PuntosP1[2];
	int Parejas;
	int Juego;
	int Baraja[40];
} Partida;

typedef struct {
	Partida partidas[100];
	int num;
} ListaPartidas;
ListaPartidas milistaPartidas;

void BarajarBaraja(int numPartida)
{
	pthread_mutex_lock(&mutex);
	for (int i=0;i<40;i++)//Creo los valores de las cartas, del 1 al 40
		milistaPartidas.partidas[numPartida].Baraja[i] = i+1;
	
	srand(time(NULL));//Estructura para generar numeros aleatorios
	int n = 40;
	for(int i=0;i<40;i++)
	{
		int v = rand()%n;// nos genera un numero aleatorio entre 0 y n-1
		int p = milistaPartidas.partidas[numPartida].Baraja[v];
		milistaPartidas.partidas[numPartida].Baraja [v] = milistaPartidas.partidas[numPartida].Baraja[n-1];
		milistaPartidas.partidas[numPartida].Baraja[n-1] = p;
		n--;
	}
	pthread_mutex_unlock(&mutex);
};

void Repartir(numPartida)
{
	int ma = milistaPartidas.partidas[numPartida].Mano[0];

		pthread_mutex_lock(&mutex);
		for(int j=0;j<4;j++){
			int cartas1[4] = {milistaPartidas.partidas[numPartida].Baraja[j*4],milistaPartidas.partidas[numPartida].Baraja[4*(j+1)],milistaPartidas.partidas[numPartida].Baraja[4*(j+2)],milistaPartidas.partidas[numPartida].Baraja[4*(j+3)]};
			for(int i=0;i<4;i++){
				if(j+ma<5){
				milistaPartidas.partidas[numPartida].jugadores[j+ma-1].Cartas[i] = cartas1[i];
				}
				else{
					milistaPartidas.partidas[numPartida].jugadores[j+ma-5].Cartas[i] = cartas1[i];
				}
			}
		}
		pthread_mutex_unlock(&mutex);
	
	for(int i=0; i<16;i++)
	{
		pthread_mutex_lock(&mutex);
		milistaPartidas.partidas[numPartida].Baraja[i]=0;
		pthread_mutex_unlock(&mutex);
	}
};

void PasarMano(int numPartida)
{
	int ma = milistaPartidas.partidas[numPartida].Mano[0];
	if(ma == 1)
	{
		pthread_mutex_lock(&mutex);
		int mano[4] = {2,3,4,1};
		for(int i=0;i<4;i++)
			milistaPartidas.partidas[numPartida].Mano[i] = mano[i];
		pthread_mutex_unlock(&mutex);
	}
	else if(ma == 2)
	{
		pthread_mutex_lock(&mutex);
		int mano[4] = {3,4,1,2};
		for(int i=0;i<4;i++)
			milistaPartidas.partidas[numPartida].Mano[i] = mano[i];
		pthread_mutex_unlock(&mutex);
	}
	else if(ma == 3)
	{
		pthread_mutex_lock(&mutex);
		int mano[4] = {4,1,2,3};
		for(int i=0;i<4;i++)
			milistaPartidas.partidas[numPartida].Mano[i] = mano[i];
		pthread_mutex_unlock(&mutex);
	}
	else if(ma == 4)
	{
		pthread_mutex_lock(&mutex);
		int mano[4] = {1,2,3,4};
		for(int i=0;i<4;i++)
			milistaPartidas.partidas[numPartida].Mano[i] = mano[i];
		pthread_mutex_unlock(&mutex);
	}
};

void HayPares(int numPartida)
{
	pthread_mutex_lock(&mutex);
	milistaPartidas.partidas[numPartida].Parejas = 1;
	pthread_mutex_unlock(&mutex);
};

void HayJuego(int numPartida)
{
	pthread_mutex_lock(&mutex);
	milistaPartidas.partidas[numPartida].Juego = 1;
	pthread_mutex_unlock(&mutex);
};

int hayPares(int numPartida)
{
	int i = milistaPartidas.partidas[numPartida].Parejas;
	return i;
};

int hayJuego(int numPartida)
{
	int i = milistaPartidas.partidas[numPartida].Juego;
	return i;
};

int damePareja(int numPartida, char nombre[20])
{
	for(int i=0; i<4;i++){
	if(strcmp(milistaPartidas.partidas[numPartida].jugadores[i].nombre,nombre)==0)
	{
		return i%2;
	}}

}
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
	
	
};
void Apostar(int numPartida, int ronda, int Apuesta)
{
	pthread_mutex_lock(&mutex);
	milistaPartidas.partidas[numPartida].Apuesta[ronda-1]= Apuesta;
	pthread_mutex_unlock(&mutex);
}
int Puntos(int numPartida, int Pareja, int ronda)
{
	int Puntos = milistaPartidas.partidas[numPartida].Apuesta[ronda-1];
	
	if (Puntos == 0)
		Puntos = 1;
	
	if (Puntos == -1)
		return 0;
	
	if (Pareja==0)
	{
		if(milistaPartidas.partidas[numPartida].PuntosP0[1] + Puntos >= 40)
		{
			pthread_mutex_lock(&mutex);
			milistaPartidas.partidas[numPartida].PuntosP0[1] = 40 - milistaPartidas.partidas[numPartida].PuntosP0[1] + Puntos;
			milistaPartidas.partidas[numPartida].PuntosP0[0] = milistaPartidas.partidas[numPartida].PuntosP0[0] + 1;
			pthread_mutex_unlock(&mutex);
			if(milistaPartidas.partidas[numPartida].PuntosP0[0]==3)
			{
				return -10;
			}
			return 0;
		}
		else
		{
			pthread_mutex_lock(&mutex);
			milistaPartidas.partidas[numPartida].PuntosP0[1] = milistaPartidas.partidas[numPartida].PuntosP0[1] + Puntos;
			pthread_mutex_unlock(&mutex);
			return 0;
		}
	}
	if (Pareja==1)
	{
		if(milistaPartidas.partidas[numPartida].PuntosP1[1] + Puntos >= 40)
		{
			pthread_mutex_lock(&mutex);
			milistaPartidas.partidas[numPartida].PuntosP1[1] = 40 - milistaPartidas.partidas[numPartida].PuntosP1[1] + Puntos;
			milistaPartidas.partidas[numPartida].PuntosP1[0] = milistaPartidas.partidas[numPartida].PuntosP1[0] + 1;
			pthread_mutex_unlock(&mutex);
			if(milistaPartidas.partidas[numPartida].PuntosP1[0]==3)
			{
				return -11;
			}
			return 0;
		}
		else
		{
			pthread_mutex_lock(&mutex);
			milistaPartidas.partidas[numPartida].PuntosP1[1] = milistaPartidas.partidas[numPartida].PuntosP1[1] + Puntos;
			pthread_mutex_unlock(&mutex);
			return 0;
		}
	}
}
//La lista se pasa por referencia
int PonConectado (ListaConectados *lista, char nombre[20], int *socket){
	//aÃ±ade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena
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
		printf("No se ha encontrado ningÃºn usuario con ese socket");
}
int CrearPartida(ListaPartidas* lista) {
	//aÃ±ade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena
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
	//aÃ±ade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena

		pthread_mutex_lock(&mutex);//No me interrumpas ahora
	for(int i=0;i<4;i++){
		if (strcmp(lista->partidas[numPartida].jugadores[i].nombre,"")==0)
		{
			sprintf(lista->partidas[numPartida].jugadores[i].nombre, nombre);
			pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
			return 0;
			
		}

		}
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
	if(strcmp(lista->partidas[partida].jugadores[i].nombre,"")==0){
		sprintf(conectados, "%s/%s", conectados, lista->partidas[partida].jugadores[i].nombre);
	}}
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
	sock_conn = milistaConectados.conectados[DamePosicion(&milistaConectados, milistaPartidas.partidas[numPartida].jugadores[ma-1].nombre)].socket;
	write(sock_conn, mensaje, strlen(mensaje));
	
	
}
int EnviarSiguiente(int jugador,char mensaje[200],int numPartida)
//Envia el mensaje al siguiente jugador de la ronda y retorna su posicion o -1 si la ronda a terminado, no hay siguiente
{
	int numJugador;
	char siguiente[20];
	numJugador=1;
	strcpy(siguiente,milistaPartidas.partidas[numPartida].jugadores[jugador].nombre);	
	for(int i=0;i<4;i++)
	{
		if(numJugador == milistaPartidas.partidas[numPartida].Mano[i] && i!=3)
		{
			int sock_conn = milistaConectados.conectados[DamePosicion(&milistaConectados, siguiente)].socket;
			write(sock_conn, mensaje, strlen(mensaje));
			return i;
		}
	}
	return -1;
}
void EnviarRival(int jugador,char mensaje[200],int numPartida)
{
	int sock_conn;
	char rival[20];
	

	strcpy(rival,milistaPartidas.partidas[numPartida].jugadores[jugador].nombre);

	sock_conn = milistaConectados.conectados[DamePosicion(&milistaConectados, rival)].socket;
	write(sock_conn, mensaje, strlen(mensaje));
}
int EnviarCompanero(int jugador,char mensaje[200],int numPartida)
{
	int sock_conn;
	char companero[20];
	

	strcpy(companero,milistaPartidas.partidas[numPartida].jugadores[jugador%2+2].nombre);
	sock_conn = milistaConectados.conectados[DamePosicion(&milistaConectados, companero)].socket;
	write(sock_conn, mensaje, strlen(mensaje));
	return 0;

};
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
		printf("Error al inicializar la conexiÃ³n: %u %s\n",
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
		
		
		
		if (codigo !=0 && codigo !=6 && codigo !=7 && codigo != 8 && codigo != 9)
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
			char miNombre;
			p = strtok(NULL, "/");
			int numPartida = atoi(p);
			p = strtok(NULL, "/");				//Conseguimos el numero de partida
			int ronda = atoi(p);
			p = strtok(NULL, "/");				// Conseguimos el nombre
			strcpy(nombre,p);
			char Respuesta[200];
			char caso[20];
			
			switch (ronda)
			{
			case 0://Ronda de Mus (P=Pregunta, A=Descarte)
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if(strcmp(caso, "P")==0)
				{
					char peticion[20];
					p = strtok(NULL, "/");
					strcpy(peticion,p);
					if (strcmp(peticion, "NO")==0)
					{
						sprintf(Respuesta, "11/%d/0/P/%s/CORTO", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
						sprintf(Respuesta, "10/%d/1", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
					else
					{
						sprintf(Respuesta, "11/%d/0/P/%s/MUS", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
						sprintf(Respuesta, "10/%d/0/P", numPartida);
						int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
						if (ma==-1)
						{
							sprintf(Respuesta, "10/%d/0/A", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
					}
				}
				else
				{
					p = strtok(NULL, "/");
					int numCartas = atoi(p);
					for(int c=0;c<numCartas;c++)
					{
						p = strtok(NULL, "/");
						int Carta = atoi(p);
						Mus(numPartida,miNombre,Carta);
					}
					sprintf(Respuesta, "10/%d/0/A", numPartida);
					int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
					if (ma==-1)
					{
						sprintf(Respuesta, "10/%d/1", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
				}
				break;
				
			case 1://Mayores
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if (strcmp(caso, "PASO")==0)
				{
					sprintf(Respuesta, "11/%d/1/%s/PASA", numPartida, miNombre);
					EnviarAPatida(miNombre, Respuesta, numPartida);
					sprintf(Respuesta, "10/%d/1/A", numPartida);
					int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
					if (ma==-1)
					{
						sprintf(Respuesta, "11/%d/1/%s/SE FUE", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						Apostar(numPartida,1,0);
						sprintf(Respuesta, "10/%d/2", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
				}
				else if(strcmp(caso, "APUESTO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/1/%s/%d", numPartida, miNombre, Apuesta);
					EnviarAPatida(miNombre, Respuesta, numPartida);
					sprintf(Respuesta, "10/%d/1/%d", numPartida, Apuesta);
					EnviarRival(miNombre,Respuesta,numPartida);
				}
				else if(strcmp(caso, "QUIERO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/1/%s/QUIERE", numPartida, miNombre);
					Apostar(numPartida, 1, Apuesta);
					EnviarAPatida(miNombre, Respuesta, numPartida);
					sprintf(Respuesta, "10/%d/2", numPartida);
					EnviarAMano(Respuesta, numPartida);
				}
				else
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/1/%s/NO QUIRE", numPartida, miNombre);
					int com= EnviarCompanero(miNombre,Respuesta,numPartida);
					if(com==-1)
					{
						int p = damePareja(numPartida, miNombre);
						if (p==0)
							Puntos(numPartida,1,1);
						else
							Puntos(numPartida,0,1);
						Apostar(numPartida, 1, -1);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						sprintf(Respuesta, "10/%d/2", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
				}
				break;
			case 2://Pequeña
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if (strcmp(caso, "PASO")==0)
				{
					sprintf(Respuesta, "11/%d/2/%s/PASA", numPartida, miNombre);
					EnviarAPatida(miNombre, Respuesta, numPartida);
					sprintf(Respuesta, "10/%d/2", numPartida);
					int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
					if (ma==-1)
					{
						sprintf(Respuesta, "11/%d/1/%s/SE FUE", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						Apostar(numPartida,2,0);
						sprintf(Respuesta, "10/%d/3/P", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
				}
				else if(strcmp(caso, "APUESTO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/2/%s/%d", numPartida, miNombre, Apuesta);
					EnviarAPatida(miNombre, Respuesta, numPartida);
					sprintf(Respuesta, "10/%d/2/%d", numPartida, Apuesta);
					EnviarRival(miNombre,Respuesta,numPartida);
				}
				else if(strcmp(caso, "QUIERO")==0)
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/2/%s/QUIERE", numPartida, miNombre);
					Apostar(numPartida, 2, Apuesta);
					EnviarAPatida(miNombre, Respuesta, numPartida);
					sprintf(Respuesta, "10/%d/3/P", numPartida);
					EnviarAMano(Respuesta, numPartida);
				}
				else
				{
					p = strtok(NULL, "/");				//Conseguimos el numero de partida
					int Apuesta = atoi(p);
					sprintf(Respuesta, "11/%d/2/%s/NO QUIRE", numPartida, miNombre);
					int com= EnviarCompanero(miNombre,Respuesta,numPartida);
					if(com==-1)
					{
						int p = damePareja(numPartida, miNombre);
						if (p==0)
							Puntos(numPartida,1,2);
						else
							Puntos(numPartida,0,2);
						Apostar(numPartida, 2, -1);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						sprintf(Respuesta, "10/%d/3/P", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
				}
				break;
			case 3://Pares (P=Pregunta, A=Apuesta)
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if(strcmp(caso, "P")==0)
				{
					char peticion[20];
					p = strtok(NULL, "/");
					strcpy(peticion,p);
					if (strcmp(peticion, "NO")==0)
					{
						sprintf(Respuesta, "11/%d/3/P/%s/PARES NO", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
						sprintf(Respuesta, "10/%d/3/P", numPartida);
						int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
						if (ma==-1)
						{
							int h = hayPares(numPartida);
							if (h==1)
							{
								sprintf(Respuesta, "10/%d/3/A", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
							else
							{
								sprintf(Respuesta, "10/%d/4/P", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
						}
					}
					else
					{
						sprintf(Respuesta, "11/%d/3/P/%s/PARES SI", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
						sprintf(Respuesta, "10/%d/3/P", numPartida);
						int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
						if (ma==-1)
						{
							int h = hayPares(numPartida);
							if (h==1)
							{
								sprintf(Respuesta, "10/%d/3/A", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
							else
							{
								sprintf(Respuesta, "10/%d/4/P", numPartida);
								EnviarAMano(Respuesta, numPartida);
								Apostar(numPartida,3,0);
								HayPares(numPartida);
							}
						}
						else
							HayPares(numPartida);
					}
				}
				else
				{
					p = strtok(NULL, "/");
					strcpy(caso,p);
					if (strcmp(caso, "PASO")==0)
					{
						sprintf(Respuesta, "11/%d/3/%s/PASA", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						sprintf(Respuesta, "10/%d/3/A", numPartida);
						int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
						if (ma==-1)
						{
							sprintf(Respuesta, "11/%d/2/%s/SE FUE", numPartida, miNombre);
							EnviarAPatida(miNombre, Respuesta, numPartida);
							Apostar(numPartida,3,0);
							sprintf(Respuesta, "10/%d/4/P", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
					}
					else if(strcmp(caso, "APUESTO")==0)
					{
						p = strtok(NULL, "/");				//Conseguimos el numero de partida
						int Apuesta = atoi(p);
						sprintf(Respuesta, "11/%d/3/%s/%d", numPartida, miNombre, Apuesta);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						sprintf(Respuesta, "10/%d/3/A/%d", numPartida, Apuesta);
						EnviarRival(miNombre,Respuesta,numPartida);
					}
					else if(strcmp(caso, "QUIERO")==0)
					{
						p = strtok(NULL, "/");				//Conseguimos el numero de partida
						int Apuesta = atoi(p);
						sprintf(Respuesta, "11/%d/3/%s/QUIERE", numPartida, miNombre);
						Apostar(numPartida, 3, Apuesta);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						sprintf(Respuesta, "10/%d/4/P", numPartida);
						EnviarAMano(Respuesta, numPartida);
					}
					else
					{
						p = strtok(NULL, "/");				//Conseguimos el numero de partida
						int Apuesta = atoi(p);
						sprintf(Respuesta, "11/%d/3/%s/NO QUIRE", numPartida, miNombre);
						int com= EnviarCompanero(miNombre,Respuesta,numPartida);
						if(com==-1)
						{
							int p = damePareja(numPartida, miNombre);
							if (p==0)
								Puntos(numPartida,1,3);
							else
								Puntos(numPartida,0,3);
							Apostar(numPartida, 3, -1);
							EnviarAPatida(miNombre, Respuesta, numPartida);
							sprintf(Respuesta, "10/%d/4/P", numPartida);
							EnviarAMano(Respuesta, numPartida);
						}
					}
				}
				
				break;
			case 4://Juego (P=Pregunta, A=Apuesta)
				p = strtok(NULL, "/");
				strcpy(caso,p);
				if(strcmp(caso, "P")==0)
				{
					char peticion[20];
					p = strtok(NULL, "/");
					strcpy(peticion,p);
					if (strcmp(peticion, "NO")==0)
					{
						sprintf(Respuesta, "11/%d/4/P/%s/JUEGO NO", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
						sprintf(Respuesta, "10/%d/4/P", numPartida);
						int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
						if (ma==-1)
						{
							int h = hayJuego(numPartida);
							if(h==1)
							{
								sprintf(Respuesta, "10/%d/4/A", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
							else
							{
								sprintf(Respuesta, "10/%d/5", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
						}
					}
					else
					{
						sprintf(Respuesta, "11/%d/4/P/%s/JUEGO SI", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
						sprintf(Respuesta, "10/%d/4/P", numPartida);
						int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
						if (ma==-1)
						{
							int h = hayJuego(numPartida);
							if(h==1)
							{
								sprintf(Respuesta, "10/%d/4/A", numPartida);
								EnviarAMano(Respuesta, numPartida);
							}
							else
							{
								HayJuego(numPartida);
								sprintf(Respuesta, "11/%d/FIN DE RONDA", numPartida, miNombre);
								//Repartir puntuacion
								BarajarBaraja(numPartida);
								PasarMano(numPartida);
								Repartir(numPartida);
								sprintf(Respuesta, "10/%d/1/A", numPartida);
								EnviarAMano(Respuesta,numPartida);
								EnviarAPatida(miNombre, Respuesta, numPartida);//Notificamos a los jugadores lo que ha decidido
							}
						}
						else
							HayJuego(numPartida);
					}
				}
				else
				{
					char caso[20];
					p = strtok(NULL, "/");
					strcpy(caso,p);
					if (strcmp(caso, "PASO")==0)
					{
						sprintf(Respuesta, "11/%d/4/%s/PASA", numPartida, miNombre);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						sprintf(Respuesta, "10/%d/4/A", numPartida);
						int ma= EnviarSiguiente(miNombre,Respuesta,numPartida);
						if (ma==-1)
						{
							sprintf(Respuesta, "11/%d/2/%s/SE FUE", numPartida, miNombre);
							EnviarAPatida(miNombre, Respuesta, numPartida);
							Apostar(numPartida,3,0);
							//Reparti Puntos
							BarajarBaraja(numPartida);
							PasarMano(numPartida);
							Repartir(numPartida);
							sprintf(Respuesta, "10/%d/1/A", numPartida);
							EnviarAMano(Respuesta,numPartida);
						}
					}
					else if(strcmp(caso, "APUESTO")==0)
					{
						p = strtok(NULL, "/");				//Conseguimos el numero de partida
						int Apuesta = atoi(p);
						sprintf(Respuesta, "11/%d/4/%s/%d", numPartida, miNombre, Apuesta);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						sprintf(Respuesta, "10/%d/4/A/%d", numPartida, Apuesta);
						EnviarRival(miNombre,Respuesta,numPartida);
					}
					else if(strcmp(caso, "QUIERO")==0)
					{
						p = strtok(NULL, "/");				//Conseguimos el numero de partida
						int Apuesta = atoi(p);
						sprintf(Respuesta, "11/%d/4/%s/QUIERE", numPartida, miNombre);
						Apostar(numPartida, 4, Apuesta);
						EnviarAPatida(miNombre, Respuesta, numPartida);
						//Repartir Puntos
						BarajarBaraja(numPartida);
						PasarMano(numPartida);
						Repartir(numPartida);
						sprintf(Respuesta, "10/%d/1/A", numPartida);
						EnviarAMano(Respuesta,numPartida);
					}
					else
					{
						p = strtok(NULL, "/");				//Conseguimos el numero de partida
						int Apuesta = atoi(p);
						sprintf(Respuesta, "11/%d/4/%s/NO QUIRE", numPartida, miNombre);
						int com= EnviarCompanero(miNombre,Respuesta,numPartida);
						if(com==-1)
						{
							int p = damePareja(numPartida, miNombre);
							if (p==0)
								Puntos(numPartida,1,4);
							else
								Puntos(numPartida,0,4);
							Apostar(numPartida, 4, -1);
							EnviarAPatida(miNombre, Respuesta, numPartida);
							//Repartir Puntos
							BarajarBaraja(numPartida);
							PasarMano(numPartida);
							Repartir(numPartida);
							sprintf(Respuesta, "10/%d/1/A", numPartida);
							EnviarAMano(Respuesta,numPartida);
						}
					}
				}
				break;
			case 5://Punto
				
				break;
			default:
				break;
			}
		}

		
		
		if (codigo !=0)
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
