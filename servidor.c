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
	int socket;
} Conectado;

typedef struct{
	Conectado conectados[100];
	int num;
} ListaConectados;
ListaConectados milistaConectados;
typedef struct {
	char nombre1[20];
	int pareja1;
	char nombre2[20];
	int pareja2;
	char nombre3[20];
	int pareja3;
	char nombre4[20];
	int pareja4;
	int empezada;
} Partida;
typedef struct {
	Partida partidas[100];
	int num;
} ListaPartidas;
ListaPartidas milistaPartidas;

//Declaracion lista para guardar los conectados

//La lista se pasa por referencia
int PonConectado (ListaConectados *lista, char nombre[20], int *socket){
	//añade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena
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

int DamePosicion(ListaConectados *lista, char nombre[20]){
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
		printf("No se ha encontrado ningún usuario con ese socket");
}
int CrearPartida(ListaPartidas* lista) {
	//añade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena
	if (lista->num == 100)
		return -1;
	else
	{
		pthread_mutex_lock(&mutex);//No me interrumpas ahora
		lista->partidas[lista->num]->empezada = 0;
		lista->partidas[lista->num]->pareja1 = -1;
		lista->partidas[lista->num]->pareja2 = -1;
		lista->partidas[lista->num]->pareja3 = -1;
		lista->partidas[lista->num]->pareja4 = -1;
		lista->num++;
		pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
			return num-1;
		


	}
}
int EliminarPartida(ListaPartidas* lista, int partida) {
	//Retorna 0 si se ha eliminado y -1 si el usuario no esta en la lista
	//lista ya es un puntero a la lista y por ello la pongo tal cual sin &



		pthread_mutex_lock(&mutex);//No me interrumpas ahora
		for (int i = partida; i < num; i++;) {
			lista->partidas[i] = lista->partidas[i + 1];
		}
		lista->num--;
		pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
		return 0;


}
int EntrarPartida(ListaPartidas* lista, char nombre[20], int pareja, int numPartida) {
	//añade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena

		pthread_mutex_lock(&mutex);//No me interrumpas ahora
		if (lista->partidas[numPartida]->pareja1==-1)
		{
			strcpy(lista->partidas[numPartida].nombre, nombre);

			lista->partidas[numPartida].pareja1 = pareja;
			pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
			return 0;
			
		}
		else if (lista->partidas[numPartida]->pareja2 == -1)
		{
			strcpy(lista->partidas[numPartida].nombre, nombre);

			lista->partidas[numPartida].pareja2 = pareja;
			pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
			return 0;

		}
		else if (lista->partidas[numPartida]->pareja3 == -1)
		{
			strcpy(lista->partidas[numPartida].nombre, nombre);

			lista->partidas[numPartida].pareja3= pareja;
			pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
			return 0;

		}
		else if (lista->partidas[numPartida]->pareja4 == -1)
		{
			strcpy(lista->partidas[numPartida].nombre, nombre);

			lista->partidas[numPartida].pareja4 = pareja;
			pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
			return 0;

		}
		else
		{
			pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
			return -1;
		}


	
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
		switch (pos)
		{
			1:
			lista->partidas[partida].pareja1 = -1;
			break;
			2:
			lista->partidas[partida].pareja1 = -1;
			break;
			3:
			lista->partidas[partida].pareja1 = -1;
			break;
			4:
			lista->partidas[partida].pareja1 = -1;
			break;
		}

		pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
		return 0;
	}

}

void JugadoresEnPartida(ListaPartidas* lista, char* conectados[512],int partida) {
	//Pone en conectados los nombres de todos los conectados separados
	//por /.
	//Ejemplo: "Pedro/Mayra/Luis"
	pthread_mutex_lock(&mutex);//No me interrumpas ahora
	int i;
	sprintf(conectados, "");
	if(lista->partidas[partida].pareja1!=-1){
		sprintf(conectados, "%s/%s", conectados, lista->partidas[partida].nombre1);
		
	}
	if (lista->partidas[partida].pareja2 != -1) {
		sprintf(conectados, "%s/%s", conectados, lista->partidas[partida].nombre2);

	}
	if (lista->partidas[partida].pareja3 != -1) {
		sprintf(conectados, "%s/%s", conectados, lista->partidas[partida].nombre3);

	}
	if (lista->partidas[partida].pareja4 != -1) {
		sprintf(conectados, "%s/%s", conectados, lista->partidas[partida].nombre4);

	}
	pthread_mutex_unlock(&mutex);//Ya puedes interrumpir

}
int CambiarPareja(ListaPartidas* lista, char nombre[20], int pareja, int numPartida) {
	if (strcmp(nombre, lista->partidas[numPartida]->nombre1) {
		lista->partidas[numPartida]->pareja1=pareja;
	}
	else if (strcmp(nombre, lista->partidas[numPartida]->nombre1) {
		lista->partidas[numPartida]->pareja2 = pareja;
	}
	else if (strcmp(nombre, lista->partidas[numPartida]->nombre1) {
		lista->partidas[numPartida]->pareja3 = pareja;
	}
	else if (strcmp(nombre, lista->partidas[numPartida]->nombre1) {
		lista->partidas[numPartida]->pareja4 = pareja;
	}
}
void EnviarAPatida(char nombre[20],char mensaje[200],int numPartida) {
	char respuesta[20];
	int sock_conn;
	if(milistaPartidas.partidas[numPartida].nombre1!=nombre){
		sock_conn=milistaConectados.conectados[DamePosicion(milistaConectados, milistaPartidas.partidas[numPartida].nombre1)].socket;
		write(sock_conn, mensaje, strlen(mensaje));
	}
	if (milistaPartidas.partidas[numPartida].nombre2 != nombre) {
		sock_conn = milistaConectados.conectados[DamePosicion(milistaConectados, milistaPartidas.partidas[numPartida].nombre2)].socket;
		write(sock_conn, mensaje, strlen(mensaje));
	}
	if (milistaPartidas.partidas[numPartida].nombre3 != nombre) {
		sock_conn = milistaConectados.conectados[DamePosicion(milistaConectados, milistaPartidas.partidas[numPartida].nombre3)].socket;
		write(sock_conn, mensaje, strlen(mensaje));
	}
	if (milistaPartidas.partidas[numPartida].nombre4 != nombre) {
		sock_conn = milistaConectados.conectados[DamePosicion(milistaConectados, milistaPartidas.partidas[numPartida].nombre4)].socket;
		write(sock_conn, mensaje, strlen(mensaje));
	}
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
		printf("Error al inicializar la conexión: %u %s\n",
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
		
		if (codigo == 0) //petici?n de desconexi?n
			char nombre[20];
			DameUser(milista, sock_conn, nombre);
			EliminaConectado(milista, milista.conectados[DamePosicion(milista, nombre)]);
			terminar=1;
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
				PonConectado(&milista, nombre, &sock_conn);
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
				sprintf(consulta, "INSERT INTO Jugadores (ID,Username,Contraseña) VALUES (%d,'%s','%s')",newID,nombre,password);
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
			DameConectados(&milista, respuesta);
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
			DameConectados(&milista, respuesta);
			p = strtok(NULL, "/");				// Conseguimos la peticion secundaria
			int peticion = atoi(p);

			p = strtok(NULL, "/");				//Conseguimos el numero de partida
			int numPartida = atoi(p);

			p = strtok(NULL, "/");				// Conseguimos el nombre
			strcpy(nombre,p);
			DameUser(&milistaConectados, sock_conn, miNombre);
			switch (peticion)
			{
				1:
					if (numPartida == -1) {
						numPartida = CrearPartida(&milistaPartidas);
						sprintf(respuesta, "8/1/%d/%s",  numPartida, miNombre);
					}
					int pos = DamePosicion(&milistaConectados, nombre);
					sock_conn2 = milistaConectados.conectados[pos].socket;
					sprintf(respuestaOtro, "8/1/%d/%s", numPartida, miNombre);
					write(sock_conn2, respuestaOtro, strlen(respuestaOtro));
					break;
				2:
					int pareja = 0;
					int err = EntrarPartida(&milistaConectados, miNombre, pareja, numPartida);
					if (err == 0) {
						sprintf(respuestaOtro, "8/2/%d/%s", numPartida, miNombre);
						EnviarAPatida(miNombre, respuestaOtro, numPartida);
					}
					else if (err == -1) {
						int pos = DamePosicion(&milistaConectados, nombre);
						sock_conn2 = milistaConectados.conectados[pos].socket;
						sprintf(respuestaOtro, "8/3/%d/%s", numPartida, nombre);
						sprintf(respuesta, "8/6/%d/%s", numPartida, miNombre);
						write(sock_conn2, respuestaOtro, strlen(respuestaOtro));
					}

					break;
				3:
					int pos = DamePosicion(&milistaConectados, nombre);
					sock_conn2 = milistaConectados.conectados[pos].socket;
					sprintf(respuestaOtro, "8/3/%d/%s", numPartida, nombre);
					write(sock_conn2, respuestaOtro, strlen(respuestaOtro));
					break;
				4:
					SalirPartida(milistaPartidas, miNombre, numPartida);
					sprintf(respuestaOtro, "8/4/%d/%s", numPartida, miNombre);
					EnviarAPatida(miNombre, respuestaOtro, numPartida);
					break;
				5:
					int pareja=atoi(nombre)
					CambiarPareja(milistaPartidas, miNombre, pareja, numPartida);
					sprintf(respuestaOtro, "8/5/%d/%s", numPartida, miNombre);
					EnviarAPatida(miNombre, respuestaOtro, numPartida);
					break;
					

						
			default:
				break;
			}
		else if (codigo == 9) {//chat
			p = strtok(NULL, "/");				// Ya tenemos la peticion
			int numPartida = atoi(p);
			p = strtok(NULL, "/");				// Ya tenemos la peticion
			strcpy(miNombre,p);
			EnviarAPatida(miNombre, peticion, numPartida);

}

		}
		
		if (codigo !=0)
		{	
			printf("Soket:%d",sock_conn);
			
			printf ("Respuesta: %s\n", respuesta);
			// Enviamos respuesta

			write (sock_conn,respuesta, strlen(respuesta));
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
	milista.num=0;
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
