#include "SDLGameObject.h"
#include "Texture.h"
#include "GameState.h"
#include "SDLApplication.h"

#include <iostream>
#include <fstream>


SDLGameObject::SDLGameObject(Vector2D _pos, Point2D _dir, int _height, int _width, Texture* _texture, GameState* _owner, int _id, int _speed){
	texture = _texture;
	pos = _pos;
	dir = _dir;
	height = _height;
	width = _width;
	ownerState = _owner;
	id = _id;
	speed = _speed;
	id != -1 ? storable = true : storable = false;
}

SDLGameObject::~SDLGameObject() {
	texture = nullptr;
	ownerState = nullptr;
}

//Render generico
void SDLGameObject::render() {
	texture->render(SDL_Rect({ (int)pos.getX(),(int)pos.getY(),(int)width,(int)height }), SDL_FLIP_NONE);
}

//Guardado genérico
void SDLGameObject::saveObject(ofstream& write)
{
	//if (storable) {
	//	write << id << " " << pos.getX() << pos.getY() << typeid(*(this)).name();
	//}
}

//Update generico
void SDLGameObject::update() {
	this->pos.setX(pos.getX() + dir.getX() * speed);
	this->pos.setY(pos.getY() + dir.getY() * speed);
}

//Cambia la textura de un objecto
void SDLGameObject::changeTexture(int index) {
	this->texture = ownerState->getApp()->getTexture(index);
}

