#include "Butterfly.h"
#include "GameState.h"
#include "PlayState.h"
#include <iostream>

void Butterfly::update() {
	//Si está viva actualizamos su posición y el frame de la textura
	if (currState == ALIVE) {
		pos.setY(pos.getY() + dir.getY() * MAX_SPEED_BUT);
		pos.setX(pos.getX() + dir.getX() * MAX_SPEED_BUT);
		if (col >= 5) col = 0;
		else col++;
	}
	//Si no, es que está muerta y por tanto sale por debajo de la pantalla
	else {
		pos.setY(pos.getY() + DEAD_DIR * DEAD_SPEED);
		//Al salir de la pantalla se elimina
		if (pos.getY() - height > MAX_Y && !deleting) {
			deleting = true;
			dynamic_cast<GameState*>(ownerState)->killObject(this);
		}
	}

	//Comprobar colisiones con los límites de la pantalla
	//EJE X
	if (pos.getX() + width > MAX_X || pos.getX() < MIN_X) {
		dir.setX(-dir.getX());
	}
	//EJE Y
	if (pos.getY() + height > MAX_Y || pos.getY() < 25) {
		dir.setY(-dir.getY());
	}
	//cout << "BUTTERFLY POS: {" << pos.getX() << ", " << pos.getY() << "} DIR: {" << dir.getX() << ", " << dir.getY() << "}" << endl;
}

void Butterfly::startDestruction() {
	static_cast<PlayState*>(ownerState)->removeButterfly();
	collisionable = false;
	currState = DEAD;
	storable = false;
}

void Butterfly::saveObject(ofstream& write)
{
	//Guardamos el id, la posición y el estado actual de la mariposa
	write << id << " " << pos.getX() << " " << pos.getY() << " " << dir.getX() << " " << dir.getY();
}