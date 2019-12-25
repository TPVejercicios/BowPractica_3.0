#include "Bow.h"

Bow::Bow(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id) :
	SDLGameObject(_pos, _dir, _h, _w, _texture, _owner,_id) {
	collisionable = false;
}

void Bow::update() {
	pos.setY(pos.getY() + dir.getY() * BOW_SPEED);
	if (pos.getY() < 0) pos.setY(0);
	if (pos.getY() > WIN_HEIGHT - height) pos.setY(WIN_HEIGHT - height);
}

void Bow::handleEvent(const SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		//Tecla abajo
		if (event.key.keysym.sym == SDLK_DOWN) dir.setY(1);
		//Tecla ariba
		else if (event.key.keysym.sym == SDLK_UP) dir.setY(-1);
		//Tecla disparo
		else if (event.key.keysym.sym == SDLK_RIGHT && charged) {
			charged = false;
			//changeTexture();
			//ownerState->createArrow({ pos.getX(),pos.getY() + h / 2 });
		}
		//Tecla recarga
		/*else if (event.key.keysym.sym == SDLK_LEFT && !charged && game->getRemainingShots() > 0) {
			charged = true;
			//changeTexture();
		}*/
		else if (event.key.keysym.sym == SDLK_p) {
			//game->gime100Arrows();
		}
	}
	else {
		dir.setY(0);
	}
}


/*
void Bow::changeTexture() {
	texture = game->getTextureBow(charged);
	w = texture->getW() / PROPOR;
	if (!charged) {
		pos.setX(GAP);
	}
	else pos.setX(0);
}

void Bow::saveToFile(string &data) {
	ArrowGameObject::saveToFile(data);
	data += " charged " + to_string(charged);
}

void Bow::notCharged() {
	charged = false;
	changeTexture();
}

*/