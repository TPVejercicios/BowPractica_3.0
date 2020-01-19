#include "Bow.h"
#include "PlayState.h"

Bow::Bow(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed) :
	SDLGameObject(_pos, _dir, _h, _w, _texture, _owner,_id,_speed) {
	collisionable = false;
}

void Bow::update() {
	pos.setY(pos.getY() + dir.getY() * speed);
	if (pos.getY() < 0) pos.setY(0);
	if (pos.getY() > WIN_HEIGHT - height) pos.setY(WIN_HEIGHT - height);
}

//Se encarga de la gestión de los eventos del Bow
void Bow::handleEvent(const SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		//Tecla abajo
		if (event.key.keysym.sym == SDLK_DOWN) dir.setY(1);
		//Tecla ariba
		else if (event.key.keysym.sym == SDLK_UP) dir.setY(-1);
		//Tecla disparo
		else if (event.key.keysym.sym == SDLK_RIGHT && charged) {
			charged = false;
			this->changeTexture(static_cast<PlayState*>(ownerState)->getApp()->BOW_2);
			static_cast<PlayState*>(ownerState)->createArrow(pos.getX(), pos.getY() + height / 2);
		}
		//Tecla recarga
		else if (event.key.keysym.sym == SDLK_LEFT && !charged && static_cast<PlayState*>(ownerState)->canShoot()) {
			charged = true;
			this->changeTexture(static_cast<PlayState*>(ownerState)->getApp()->BOW_1);
		}
		else if (event.key.keysym.sym == SDLK_p) {
			static_cast<PlayState*>(ownerState)->giveArrows();
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