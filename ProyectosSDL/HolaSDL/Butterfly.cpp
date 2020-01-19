#include "Butterfly.h"

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
			//game->killObject(this);
		}
	}
	//Comprobar colisiones con los límites de la pantalla
	if (pos.getX() > MAX_X || pos.getX() < MIN_X) {
		dir.setX(-dir.getX());
		dir.setY(dir.getY());
		flip = SDL_FLIP_VERTICAL;
	}
	else if (pos.getY() > MAX_Y || pos.getY() < 0) {
		dir.setX(dir.getX());
		dir.setY(-dir.getY());
		flip = SDL_FLIP_HORIZONTAL;
	}
}