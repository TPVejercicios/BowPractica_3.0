#include "SDLGameObject.h"
#include "Texture.h"
#include "GameState.h"
#include "SDLApplication.h"

SDLGameObject::SDLGameObject(Vector2D _pos, Point2D _dir, int _height, int _width, Texture* _texture, GameState* _owner, int _id, int _speed){
	texture = _texture;
	pos = _pos;
	dir = _dir;
	height = _height;
	width = _width;
	ownerState = _owner;
	id = _id;
	speed = _speed;
}

SDLGameObject::~SDLGameObject() {
	texture = nullptr;
	ownerState = nullptr;
}

//Render generico
void SDLGameObject::render() {
	texture->render({ pos.getX(),pos.getY(),width,height }, SDL_FLIP_NONE);
}

//Update generico
void SDLGameObject::update() {
	this->pos.setX(pos.getX() + dir.getX() * speed);
	this->pos.setY(pos.getY() + dir.getY() * speed);
}

//Cambia la textura de un objecto
void SDLGameObject::changeTexture(int index) {
	SDLApplication* app = ownerState->getApp();
	this->texture = app->getTexture(index);
	app = nullptr;
}

