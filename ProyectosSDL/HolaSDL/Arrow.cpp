#include "Arrow.h"
#include "GameState.h"


void Arrow::update() {
	this->pos.setX(pos.getX() + dir.getX() * speed);
	this->pos.setY(pos.getY() + dir.getY() * speed);
	if (pos.getX() > arrowLimit) {
		static_cast<GameState*>(ownerState)->killObject(this);
	}
}

void Arrow::saveObject(ofstream& write)
{
	//Guardamos el id, la posición y cuantos stacks tiene
	write << id << " " << pos.getX() << " " << pos.getY() << " " << stack << endl;
}

