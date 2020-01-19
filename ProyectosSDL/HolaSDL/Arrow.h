#pragma once
#include "SDLGameObject.h"


class Arrow: public SDLGameObject
{
private:
public:
	Arrow(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed) 
		:SDLGameObject(_pos, _dir, _h, _w, _texture, _owner, _id,_speed) {};

};

