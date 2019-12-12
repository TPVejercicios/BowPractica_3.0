#include "SDLGameObject.h"
#include "Texture.h"



SDLGameObject::SDLGameObject(Texture* _texture, Vector2D _pos, Point2D _dir, int _height, int _width, GameState* _owner) 
	:GameObject() {
	texture = _texture;
	pos = _pos;
	dir = _dir;
	height = _height;
	width = _width;
	ownerState = _owner;
}

void SDLGameObject::render() {
	texture->render({ pos.getX(),pos.getY(),width,height }, SDL_FLIP_NONE);
}

void SDLGameObject::update() {

}
