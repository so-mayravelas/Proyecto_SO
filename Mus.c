//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	MYSQL* conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES* resultado;
	MYSQL_RES* resultado2;
	MYSQL_ROW row;
	char nombre[20];
	char consulta[250];
	int ID;
	
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
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	printf("Usuario que de quien quieres saber la pareja: ");
	scanf("%s",nombre);
	strcpy(consulta, "SELECT * FROM Referencia WHERE Referencia.ID_Partida IN ( SELECT Referencia.ID_Partida FROM Referencia, Jugadores WHERE Jugadores.Username = '");
	strcat(consulta, nombre);
	strcat(consulta, "' AND Referencia.ID_Jugador = Jugadores.ID);");
	err = mysql_query(conn, consulta);
	if (err != 0) {
		printf("Error al consultar datos de la base %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	//recogemos el resultado de la consulta. El resultado de la
	//consulta se devuelve en una variable del tipo puntero a
	//MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia
	//de la tabla real en disco.
	resultado = mysql_store_result(conn);
	// El resultado es una estructura matricial en memoria
	// en la que cada fila contiene los datos de una persona.
	strcpy(consulta, "");
	strcpy(consulta, "SELECT ID FROM Jugadores WHERE Username='");
	strcat(consulta, nombre);
	strcat(consulta, "'; ");
	err = mysql_query(conn, consulta);
	if (err != 0) {
		printf("Error al consultar datos de la base %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	resultado2 = mysql_store_result(conn);
	row= mysql_fetch_row(resultado2);
	ID = atoi(row[0]);
	// Ahora obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	row = mysql_fetch_row(resultado);
	// En una fila hay tantas columnas como datos tiene una
	// persona. En nuestro caso hay tres columnas: dni(row[0]),
	// nombre(row[1]) y edad (row[2]).
	int ID_P=2;
	int ID_J=-1;
	int jugadores[3][3];
	printf("%s","Parejas del jugador:\n");
	if (row == NULL)
		printf("No se han obtenido datos en la consulta\n");
	else{
		int i=0;
		while (row != NULL) {
			if(ID==atoi(row[1])){
				ID_P=atoi(row[2]);
			}
			else{
				jugadores[i][0]=atoi(row[0]);
				jugadores[i][1]=atoi(row[1]);
				jugadores[i][2]=atoi(row[2]);
				i=i+1;
			}
			if(ID_P!=2&&i==3){
				i=-1;
				do{
				
						i++;
						ID_J=jugadores[i][1];
						

				}while(ID_P!=jugadores[i][2]);
				i=0;
				char temp[20];
				sprintf(temp,"%d",ID_J);
				strcpy(consulta, "");
				strcpy(consulta, "SELECT Username FROM Jugadores WHERE ID=");
				strcat(consulta, temp );
				strcat(consulta, "; ");				
				err = mysql_query(conn, consulta);
				if (err != 0) {
					printf("Error al consultar datos de la base %u %s\n",
						   mysql_errno(conn), mysql_error(conn));
					exit(1);
				}
				
				resultado2 = mysql_store_result(conn);
				row= mysql_fetch_row(resultado2);
				ID_P=2;
				printf("%s",row[0]);
				printf("\n");
				
			}
			row = mysql_fetch_row(resultado);
		}}
		
	mysql_close(conn);
	exit(0);
}

