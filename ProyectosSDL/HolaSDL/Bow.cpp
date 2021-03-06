#include "Bow.h"
#include "PlayState.h"
#include "GameState.h"

Bow::Bow(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed) :
	SDLGameObject(_pos, _dir, _h, _w, _texture, _owner,_id,_speed) {
	collisionable = false;
}

void Bow::update() {
	pos.setY(pos.getY() + dir.getY() * speed);
	if (pos.getY() < 0) pos.setY(0);
	if (pos.getY() > WIN_HEIGHT - height) pos.setY(WIN_HEIGHT - height);
	if (!charged && !static_cast<PlayState*>(ownerState)->canShoot()) {
		static_cast<PlayState*>(ownerState)->noArrows();
	}
}

//Se encarga de la gesti�n de los eventos del Bow
void Bow::handleEvent(const SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		//Tecla abajo
		if (event.key.keysym.sym == SDLK_DOWN) dir.setY(1);
		//Tecla ariba
		else if (event.key.keysym.sym == SDLK_UP) dir.setY(-1);
		//Tecla disparo
		else if (event.key.keysym.sym == SDLK_RIGHT && charged) {
			charged = false;
			this->texture = ownerState->getApp()->getTexture(Resources::TextureId::DischargedBow);
			//Para ajustar el tama�o y posici�n al cambio de textura
			width = BOW_2_W;
			pos.setX(GAP);
			static_cast<PlayState*>(ownerState)->createArrow({ pos.getX(), pos.getY() + height / 2 });
		}
		//Tecla recarga
		else if (event.key.keysym.sym == SDLK_LEFT && !charged && static_cast<PlayState*>(ownerState)->canShoot()) {
			charged = true;
			this->texture = ownerState->getApp()->getTexture(Resources::TextureId::LoadedBow);
			//Para ajustar el tama�o y posici�n al cambio de textura
			width = BOW_1_W;
			pos.setX(0);
		}
		else if (event.key.keysym.sym == SDLK_p) {
			static_cast<PlayState*>(ownerState)->giveArrows();
		}
	}
	else {
		dir.setY(0);
	}
}

void Bow::saveObject(ofstream& write)
{
	//Guardamos el id, la posici�n en Y y si el arco est� cargado
	write << id << " " << pos.getY() << " " << charged; //cargado 1 descargado 0
}

void Bow::changeBowStatus(int status)
{
	status == 0 ? charged = false : charged = true;
	if (!charged) {
		texture = ownerState->getApp()->getTexture(Resources::TextureId::DischargedBow);
		//Para ajustar el tama�o y posici�n al cambio de textura
		width = BOW_2_W;
		pos.setX(GAP);
	}
}

