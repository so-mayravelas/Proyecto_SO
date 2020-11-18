DROP DATABASE IF EXISTS DBGame;
CREATE DATABASE DBGame;

USE DBGame;

CREATE TABLE Partidas(
	ID INT NOT NULL,
	ParejaGanadora INT,
	Duracion FLOAT,
	Resultado INT,
	Fecha VARCHAR(8),
	PRIMARY KEY (ID)
)ENGINE=InnoDB;

CREATE TABLE Jugadores(
	ID INT NOT NULL,
	Usuario VARCHAR(20) NOT NULL,
	Contraseña VARCHAR(20) NOT NULL,
	PRIMARY KEY (ID)	
)ENGINE=InnoDB;

CREATE TABLE Referencia(
	ID_P INT NOT NULL,
	ID_J INT NOT NULL,
	Pareja INT NOT NULL,
	FOREIGN KEY (ID_P) REFERENCES Partidas(ID),
	FOREIGN KEY (ID_J) REFERENCES Jugadores(ID)
)ENGINE=InnoDB;


INSERT INTO Partidas VALUES (1,0,1.12,31,'18102020');
INSERT INTO Partidas VALUES (2,0,0.98,30,'12092020');
INSERT INTO Partidas VALUES (3,1,2.42,32,'27122019');

INSERT INTO Jugadores VALUES (1,'David','Saiz');
INSERT INTO Jugadores VALUES (2,'Andoni','Coronel');
INSERT INTO Jugadores VALUES (3,'Galder','Arcellares');
INSERT INTO Jugadores VALUES (4,'Tania','Guillot');
INSERT INTO Jugadores VALUES (5,'Unai','Coronel');
INSERT INTO Jugadores VALUES (6,'Ibon','Erro');
INSERT INTO Jugadores VALUES (7,'Ander','Lopez');

INSERT INTO Referencia VALUES (1,1,1);
INSERT INTO Referencia VALUES (1,2,1);
INSERT INTO Referencia VALUES (1,3,0);
INSERT INTO Referencia VALUES (1,4,0);
INSERT INTO Referencia VALUES (2,2,2);
INSERT INTO Referencia VALUES (2,5,2);
INSERT INTO Referencia VALUES (2,6,3);
INSERT INTO Referencia VALUES (2,7,3);
INSERT INTO Referencia VALUES (3,2,1);
INSERT INTO Referencia VALUES (3,1,1);
INSERT INTO Referencia VALUES (3,3,0);
INSERT INTO Referencia VALUES (3,4,0);

/*SELECT Referencia.ID_P FROM (Jugadores,Referencia) 
WHERE Referencia.ID_P IN(
	SELECT Referencia.ID_P FROM(Jugadores, Referencia)
	WHERE Jugadores.Usuario = 'Andoni' 
	AND Jugadores.ID = Referencia.ID_J
	)
AND Referencia.Pareja IN(
	SELECT Referencia.Pareja FROM(Jugadores, Referencia) 
	WHERE Jugadores.Usuario = 'Andoni' 
	AND Jugadores.ID = Referencia.ID_J
	)
AND Jugadores.Usuario = 'Ibon'
AND Referencia.ID_J = Jugadores.ID;*/
