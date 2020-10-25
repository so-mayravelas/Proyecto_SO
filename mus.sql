DROP DATABASE IF EXISTS mus;
CREATE DATABASE mus;
USE mus;
CREATE TABLE Partidas(
	ID_Partida INTEGER NOT NULL,
	ID_ParejaGanadora INTEGER,
	Duracion INTEGER,
	Resultado INTEGER,
	Fecha TEXT,
	PRIMARY KEY(ID_Partida)
)ENGINE = InnoDB;
CREATE TABLE Jugadores(
	ID INTEGER NOT NULL,
	Username TEXT,
	Contraseña TEXT,
	PRIMARY KEY (ID)
)ENGINE = InnoDB;
CREATE TABLE Referencia(
	ID_Partida INTEGER,
	ID_Jugador INTEGER,
	ID_Pareja INTEGER,
	FOREIGN KEY(ID_Partida) REFERENCES Partidas(ID_Partida),
	FOREIGN KEY(ID_Jugador) REFERENCES Jugadores(ID)
)ENGINE=InnoDB;

INSERT INTO Jugadores Values (1,"Galder","1234");
INSERT INTO Jugadores Values (2,"Ga","1234");
INSERT INTO Jugadores Values (3,"Mayra","1234");
INSERT INTO Jugadores Values (4,"May","1234");
INSERT INTO Jugadores Values (5,"Andoni","1234");
INSERT INTO Jugadores Values (6,"And","1234");
INSERT INTO Partidas Values (1,1,40,2,"2020-08-10");
INSERT INTO Partidas Values (2,0,40,2,"2020-08-10");
INSERT INTO Partidas Values (3,0,23,0,"2020-08-10");
INSERT INTO Partidas Values (4,1,35,2,"2020-08-10");
INSERT INTO Partidas Values (5,0,25,1,"2020-08-10");
INSERT INTO Partidas Values (6,1,20,0,"2020-08-10");
INSERT INTO Referencia Values (1,1,0);
INSERT INTO Referencia Values (1,2,0);
INSERT INTO Referencia Values (1,3,1);
INSERT INTO Referencia Values (1,4,1);
INSERT INTO Referencia Values (2,2,0);
INSERT INTO Referencia Values (2,3,0);
INSERT INTO Referencia Values (2,6,1);
INSERT INTO Referencia Values (2,5,1);
INSERT INTO Referencia Values (3,2,0);
INSERT INTO Referencia Values (3,3,0);
INSERT INTO Referencia Values (3,1,1);
INSERT INTO Referencia Values (3,6,1);
INSERT INTO Referencia Values (4,3,0);
INSERT INTO Referencia Values (4,5,0);
INSERT INTO Referencia Values (4,2,1);
INSERT INTO Referencia Values (4,4,1);
INSERT INTO Referencia Values (5,1,0);
INSERT INTO Referencia Values (5,3,0);
INSERT INTO Referencia Values (5,2,1);
INSERT INTO Referencia Values (5,6,1);
INSERT INTO Referencia Values (6,1,0);
INSERT INTO Referencia Values (6,5,0);
INSERT INTO Referencia Values (6,4,1);
INSERT INTO Referencia Values (6,2,1);