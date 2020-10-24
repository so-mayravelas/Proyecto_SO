#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int id;
	char nombre[20];
	char consulta [80];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion, indicamos claves de acceso
	conn = mysql_real_connect (conn, "localhost", "root", "mysql", "JBD",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//indicamos la base de datos con la que queremos trabajar 
	err=mysql_query(conn, "use JBD;");
	if (err!=0)
	{
		printf ("Error al crear la base de datos %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
///consulta
	
	int cont;
	//Construimos la consulta
	strcpy (consulta,"SELECT partida.Idganador FROM JBD.partida ");
	// hacemos la consulta 
	err=mysql_query (conn, consulta); 
	if (err!=0) 
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
		
	}
	
	//recogemos el resultado de la consulta
	
	//recogemos el resultado de la consulta 
	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);
	if (row == NULL)
	
		printf ("No se han obtenido datos en la consulta\n");
	else
	{
		cont=0;
		while(row!=NULL)
		{
			printf("%s \n", row[0]);
			row=mysql_fetch_row(resultado);
			cont++;
		}
	}
	
	// cerrar la conexion con el servidor MYSQL 
	mysql_close (conn);
	exit(0);
	
}
