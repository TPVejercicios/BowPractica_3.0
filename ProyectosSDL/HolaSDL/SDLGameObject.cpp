#include "SDLGameObject.h"
#include "Texture.h"



SDLGameObject::SDLGameObject(Vector2D _pos, Point2D _dir, int _height, int _width, Texture* _texture, GameState* _owner, int _id)
{
	texture = _texture;
	pos = _pos;
	dir = _dir;
	height = _height;
	width = _width;
	ownerState = _owner;
	id = _id;
}

void SDLGameObject::render() {
	texture->render({ pos.getX(),pos.getY(),width,height }, SDL_FLIP_NONE);
}

void SDLGameObject::update() {

}
