DROP DATABASE IF EXISTS JBD;
CREATE DATABASE JBD;


USE JBD;

CREATE TABLE jugador(
	id INT(20),
	nombre VARCHAR(20),
	password VARCHAR(20),
	Victorias INT(10),
	PRIMARY KEY (id)
)ENGINE=InnoDB;

CREATE TABLE partida(
	IdPart INT(20),
	Idganador VARCHAR(20),
	duracion FLOAT,
	fechahora VARCHAR(20),
	PRIMARY KEY (id)
)ENGINE=InnoDB;

CREATE TABLE Resultado(
	idJugador INT(20),
	idPartida INT(20), 
	puntos INT,
	FOREIGN KEY (idJugador) REFERENCES jugador(id),
	FOREIGN KEY (idPartida) REFERENCES partida(id)
)ENGINE=InnoDB;

INSERT INTO jugador VALUES (1, 'Galder', '123456', 5);
INSERT INTO jugador VALUES (2, 'Mayra', '654321', 3);
INSERT INTO jugador VALUES (3, 'Andoni', '123456',4);

INSERT INTO partida VALUES (1,2,12, '13/10/2020 10:30');
INSERT INTO partida VALUES (2,3,8,'02/10/2020 10:30');
INSERT INTO partida VALUES (3,6,13,'13/10/2020 10:30');


INSERT INTO Resultado VALUES (4,1);
INSERT INTO Resultado VALUES (4,3);
INSERT INTO Resultado VALUES (5,1);






