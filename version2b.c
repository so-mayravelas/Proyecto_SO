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

ListaConectados milista;

//Declaracion lista para guardar los conectados

//La lista se pasa por referencia
int PonConectado (ListaConectados *lista, char nombre[20], int *socket){
	//aÃ±ade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena
	if(lista->num ==100)
		return -1;
	else
	{
		pthread_mutex_lock(&mutex);//No me interrumpas ahora
		strcpy(lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket= socket;
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

void DameConectados(ListaConectados *lista, char conectados[512]){
	//Pone en conectados los nombres de todos los conectados separados
	//por /.
	//Ejemplo: "Pedro/Mayra/Luis"
	pthread_mutex_lock(&mutex);//No me interrumpas ahora
	int i;
	for(i=0;i<lista->num;i++)
	{
		sprintf(conectados, "%s/%s", conectados, lista->conectados[i].nombre);
		pthread_mutex_unlock(&mutex);//Ya puedes interrumpir
	}
	
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
		printf("No se ha encontrado ningÃºn usuario con ese socket");
}

int AtenderPeticion (int identificador, char datos [200], char respuesta [512], int socket)
{
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
	if (identificador !=0)
	{
		char datos1 [200];
		strcpy(datos1,datos);
		char *p = strtok( datos1, "/");				// Ya tenemos el nombre
		strcpy(nombre,p);
		printf ("Codigo: %d, Nombre: %s\n", identificador, nombre);
	}
	
	if (identificador ==0) //petici?n de desconexi?n
		return 1;
	
	else if (identificador == 1) {//Iniciar sesion
		char password[20];
		char *c = strtok(datos, "/");				// Ya tenemos el nombre
		strcpy(password, c);
		sprintf(respuesta, "Error:Nombre de usuario o contrasena no conciden");
		sprintf(consulta, "SELECT * FROM Jugadores WHERE Username='%s' AND Contraseña='%s'",nombre,password);
		err = mysql_query(conn, consulta);
		if (err != 0) {
			printf("Error al consultar datos de la base %u %s\n",
				   mysql_errno(conn), mysql_error(conn));
			exit(1);
		}
		resultado = mysql_store_result(conn);
		row = mysql_fetch_row(resultado);
		printf(row[0]);
		while (row != NULL)
		{
			if (strcmp(nombre, row[1]) == 0 && strcmp(password, row[2]) == 0)
			{
				sprintf(respuesta, "Has iniciado sesion");
				PonConectado(&milista, nombre, &socket); 
			}
			row = mysql_fetch_row(resultado);
		}
		return 0;
		
		
	}
	else if (identificador == 2) {//Registarse
		char password[20];
		char *c = strtok(NULL, "/");				// Ya tenemos el nombre
		strcpy(password, c);
		sprintf(respuesta, "Registrado");
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
				sprintf(respuesta, "Error:Username ya registrado");
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
		return 0;
	}
	
	else if (identificador ==3){ //parejas con las que ha jugado un jugador
		
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
		return 0;
	}
	
	
	else if (identificador == 4) {
		///consulta Cuantas partidas ha ganado un jugador 
		
		int cont;
		//Construimos la consulta
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
		}
		return 0;
	}
	
	else if (identificador == 5)  //Consulta de Andoni
	{
		nPartidas=0;
		strcpy(Usuario1,nombre);
		char *c = strtok( datos, "/");	
		strcpy(Usuario2,c);
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
			printf("No va mal\n");
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
		sprintf(respuesta,"%d", nPartidas);
		return 0;
	}

	else if (identificador==6)//Peticiones realizadas por el servidor
	{
		sprintf(respuesta, "%d", contadorservicios);
	}
	else if (identificador==7)//Lista conectados
	{
		DameConectados(&milista, respuesta);
		if (respuesta==NULL)
			strcpy(respuesta, "No hay conectados");
		else
		{
			printf("Resultado: %s\n", respuesta);
		}
		
	}
	//Cerramos la conexion con la base de datos
	mysql_close(conn);
}
//Programa principal 
//para llamar a todas las funciones


void *AtenderCliente (void *socket)
{
	int ret;
	int sock_conn;
	int *s;
	s = (int *) socket;
	sock_conn = *s;
	
	char peticion[512];
	char respuesta[512];
	char datos [200];
	sprintf(datos,"");
	
	int terminar = 0;
	
	while (terminar == 0)
	{
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
		p = strtok( NULL, "/");
		
		while (p != NULL)
		{
			sprintf(datos,"%s%s/", datos, p);
			p = strtok( NULL, "/");
			
		}
		
		terminar = AtenderPeticion(codigo, datos, respuesta, socket);
		
		if (codigo !=0)
		{
			printf("Respuesta: %s\n", respuesta);
			//Enviamos respuesta
			write(sock_conn, respuesta, strlen(respuesta));
			pthread_mutex_lock(&mutex);//No me interrumpas
			contadorservicios++;
			pthread_mutex_unlock(&mutex);
		}
	}
	
	close(sock_conn); 
}

int main(int argc, char *argv[])
{
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;
	
	//INICIALIZAMOS
	//abrimos socket
	if((sock_listen =socket(AF_INET, SOCK_STREAM, 0)) <0)
		printf("Error creando el socket");
	//Hacemos el bind al puerto
	
	memset(&serv_adr,0,sizeof(serv_adr)); //inicializamos a cero serv_addr
	serv_adr.sin_family = AF_INET;
	
	//asocia el socket a cualquiera de las ip de la maquina
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	//establecemos el puerto de escucha
	serv_adr.sin_port=htons(9040);
	if(bind(sock_listen,(struct sockaddr *) &serv_adr, sizeof(serv_adr))<0)
		printf("Error en el bind");
	if(listen(sock_listen,3) <0)
		printf("Error en el listen");
	
	//int i;
	int sockets[25];
	pthread_t thread [25];
	contadorservicios = 0;
	milista.num=0;
	//i=0;
	//Bucle para atender a clientes
	for(int i=0;i<25;i++)
	{
		printf ("Escuchando\n");
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		
		// Crear thead y decirle lo que tiene que hacer
		pthread_create (&thread[25], NULL, AtenderCliente, &sockets[i]);			
	}
}


