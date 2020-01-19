#include "Ballon.h"

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
			//game->killObject(this);
		}
	}
}