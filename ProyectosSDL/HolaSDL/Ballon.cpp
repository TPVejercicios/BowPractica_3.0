#include "Ballon.h"
#include "GameState.h"
#include "PlayState.h"

void Ballon::update() {

	if (currStatus == SWOLLEN) {
		pos.setY(pos.getY() + (dir.getY() * speed));
		if (pos.getY() < TOP_LIMIT) {
			currStatus = PUNCTURED;
		}
	}
	else
	{
		col++;
		if (col > texture->getNumCols() && !deleting) {
			deleting = true;
			static_cast<GameState*>(ownerState)->killObject(this);
		}
	}
}

void Ballon::startDestruction() {
	collisionable = false;
	dir.setY(0);
	currStatus = PUNCTURED;
	int rnd = rand() % 10;
	if (rnd < 3) {
		static_cast<PlayState*>(ownerState)->createReward(pos);
	}
}