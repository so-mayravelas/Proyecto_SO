//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int nPartidas = 0;
	char Usuario1 [20];
	char Usuario2 [20];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexiï¿ïŸ³n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "DBGame",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexiï¿ïŸ³n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	err=mysql_query (conn, "SELECT * FROM Jugadores");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta. El resultado de la
	//consulta se devuelve en una variable del tipo puntero a
	//MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia
	//de la tabla real en disco.
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial en memoria
	// en la que cada fila contiene los datos de una persona.
	
	// Ahora obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	row = mysql_fetch_row (resultado);
	// En una fila hay tantas columnas como datos tiene una
	// persona. En nuestro caso hay tres columnas: dni(row[0]),
	// nombre(row[1]) y edad (row[2]).
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL) {
			int ID = atoi (row[0]);
			printf ("ID: %d, Usuario: %s, Contraseña: %s\n", row[0], row[1], row[2]);
			row = mysql_fetch_row (resultado);
	}
		// Realizar la busqueda Ejercicio 3.3
		printf ("Dame los Usuarios que quieres buscar separados por un espacio\n"); 
		scanf ("%s %s", Usuario1, Usuario2);
		// construimos la consulta SQL
		char consulta [500];
		sprintf (consulta,"SELECT Referencia.ID_P FROM (Jugadores,Referencia) WHERE Referencia.ID_P IN(SELECT Referencia.ID_P FROM(Jugadores, Referencia) WHERE Jugadores.Usuario = '%s' AND Jugadores.ID = Referencia.ID_J) AND Referencia.Pareja IN(SELECT Referencia.Pareja FROM(Jugadores, Referencia) WHERE Jugadores.Usuario = '%s' AND Jugadores.ID = Referencia.ID_J) AND Jugadores.Usuario = '%s' AND Referencia.ID_J = Jugadores.ID", Usuario1, Usuario1, Usuario2);
		// hacemos la consulta 
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		row = mysql_fetch_row (resultado);
		if (row == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else{
			while (row !=NULL) {
				printf ("%d\n", row);
				nPartidas++;
				row = mysql_fetch_row (resultado);
			}

		}
		
		printf ("Numero de partidas que la pareja de %s y %s ha jugado: %d\n", Usuario1, Usuario2, nPartidas);
		
		// cerrar la conexion con el servidor MYSQL 
		mysql_close (conn);
		exit(0);
}