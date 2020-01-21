#include "Arrow.h"
#include "GameState.h"


void Arrow::update() {
	this->pos.setX(pos.getX() + dir.getX() * speed);
	this->pos.setY(pos.getY() + dir.getY() * speed);
	if (pos.getX() > arrowLimit) {
		dynamic_cast<GameState*>(ownerState)->killObject(this);
	}
}

