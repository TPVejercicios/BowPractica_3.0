#include "Butterfly.h"
#include "GameState.h"
#include "PlayState.h"

void Butterfly::update() {

	if (currState == ALIVE) {
		pos.setY(pos.getY() + dir.getY() * MAX_SPEED_BUT);
		pos.setX(pos.getX() + dir.getX() * MAX_SPEED_BUT);
		if (col >= 5) col = 0;
		else col++;
	}
	else {
		pos.setY(pos.getY() + DEAD_DIR * DEAD_SPEED);
		if (pos.getY() > MAX_Y && !deleting) {
			deleting = true;
			dynamic_cast<GameState*>(ownerState)->killObject(this);
		}
	}
	//Comprobar colisiones con los límites de la pantalla
	if (pos.getX() > MAX_X || pos.getX() < MIN_X) {
		dir.setX(-dir.getX());
		dir.setY(dir.getY());
		//flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
	}
	else if (pos.getY() > MAX_Y || pos.getY() < 25) {
		dir.setX(dir.getX());
		dir.setY(-dir.getY());
		//flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
	}
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