#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>



int main(int argc, char *argv[])
{
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
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
	serv_adr.sin_port = htons(9000);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	int i;
	// Bucle infinito
	for (;;){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		//sock_conn es el socket que usaremos para este cliente
		
		int terminar =0;
		// Entramos en un bucle para atender todas las peticiones de este cliente
		//hasta que se desconecte
		while (terminar ==0)
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


			
			if (codigo !=0)
			{
				p = strtok( NULL, "/");				// Ya tenemos el nombre
				strcpy(nombre,p);
				printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);
			}
			
			if (codigo ==0) //petici?n de desconexi?n
				terminar=1;
			else if (codigo == 1) {//Iniciar sesion
				char password[20];
				p = strtok(NULL, "/");				// Ya tenemos el nombre
				strcpy(password, p);
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
					if (strcmp(nombre, row[0]) == 0 && strcmp(password, row[1]) == 0)
						sprintf(respuesta, "Has iniciado sesion");
				}

			
			}
			else if (codigo == 2) {//Registarse
				char password[20];
				p = strtok(NULL, "/");				// Ya tenemos el nombre
				strcpy(password, p);
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
				while (row != NULL) {
					if (strcmp(row[0] , nombre)==0) {
						sprintf(respuesta, "Error:Username ya registrado");
					}
					row = mysql_fetch_row(resultado);
				}
				if (strcmp(respuesta, "Registrado") == 0) {
					int newID = 0;
					sprintf(consulta, "SELECT ID FROM Jugadores");
					if (err != 0) {
						printf("Error al consultar datos de la base %u %s\n",mysql_errno(conn), mysql_error(conn));
						exit(1);
					}
					resultado = mysql_store_result(conn);
					row = mysql_fetch_row(resultado);
					while (row != NULL)
					{
						if (newID < atoi(row[0]))
						{
							newID = atoi(row[0]) + 1;
						}
					}
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
				///consulta

				int cont;
				//Construimos la consulta
				strcpy(consulta, "SELECT Partidas.Idganador FROM Partidas ");
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
			}
			else //quiere saber si es alto
			{
						nPartidas=0;
						p = strtok( NULL, "/");	
						strcpy(Usuario2,p);
						sprintf(consulta, "SELECT Referencia.ID_Partida FROM (Jugadores,Referencia) WHERE Referencia.ID_Partida IN(SELECT Referencia.ID_Partida FROM(Jugadores, Referencia) WHERE Jugadores.Username = '%s' AND Jugadores.ID = Referencia.ID_Jugador AND Referencia.Pareja =IN( SELECT Referencia.Pareja FROM(Jugadores, Referencia) WHERE Jugadores.Username = '%s' AND Jugadores.ID = Referencia.ID_Jugador) AND Referencia.ID_Partida =IN( SELECT Referencia.ID_Partida FROM(Jugadores, Referencia) WHERE Jugadores.Username = '%s' AND Jugadores.ID = Referencia.ID_Jugador)) AND Jugadores.Username = '%s' AND Referencia.ID_Jugador = Jugadores.ID", Usuario1, Usuario1, Usuario1, Usuario2);
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
						else {
							while (row != NULL) {
								printf("%d\n", row);
								nPartidas++;
								row = mysql_fetch_row(resultado);
							}

						}
						sprintf(respuesta,"%d",nPartidas);
			}
				
			if (codigo !=0)
			{
				
				printf ("Respuesta: %s\n", respuesta);
				// Enviamos respuesta
				write (sock_conn,respuesta, strlen(respuesta));
			}
		}
		// Se acabo el servicio para este cliente
		mysql_close(conn);
		exit(0);
		close(sock_conn); 
	}
}
