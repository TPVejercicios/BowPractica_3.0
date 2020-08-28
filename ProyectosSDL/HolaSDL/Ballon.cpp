#include "Ballon.h"
#include "GameState.h"
#include "PlayState.h"

void Ballon::update() {
	//Si el globo está inflado 
	if (currStatus == status::SWOLLEN) {
		//Mueve el globo
		pos.setY(pos.getY() + (dir.getY() * speed));
		//Si el globo llega al límite se cambia el estado a pinchado
		if (pos.getY() < topLimit) {
			currStatus = status::PUNCTURED;
		}
	}
	else//El globo está pinchado
	{	
		//Se suma la columna para su renderizaje
		col++;
		//Cuando se llega al final de las columnas, se procede a destruir el globo
		if (col > texture->getNumCols() && !deleting) {
			deleting = true;
			static_cast<GameState*>(ownerState)->killObject(this);
		}
	}
}

void Ballon::startDestruction() {
	collisionable = false;
	dir.setY(0);
	currStatus = status::PUNCTURED;
	int rnd = rand() % 10;
	if (rnd < 3) {
		static_cast<PlayState*>(ownerState)->createReward(pos);
	}
}

void Ballon::saveObject(ofstream& write)
{
	//Guardamos el id, la posición , velocidad
	write << id << " " << pos.getX() << " " << pos.getY() << " " << speed;
} 
