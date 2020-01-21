#pragma once
#include "SDLGameObject.h"
#include "PlayState.h"

#pragma region CONSTANTES
const int H_FOR_COLLISION = 5;
const int W_FOR_COLLISION = 50;
const int GAP_COll = 55;
#pragma endregion


class Arrow: public SDLGameObject
{
private:
	int arrowLimit = 700;
	int stack = 0;
public:
	Arrow(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed) 
		:SDLGameObject(_pos, _dir, _h, _w, _texture, _owner, _id,_speed) {};
	virtual void update();
	void addStack() { stack++; };
	void bonusStack() { static_cast<PlayState*>(ownerState)->stackArrows(stack); };
	SDL_Rect getRectForCollision() const { return{ pos.getX() + GAP_COll,pos.getY(),W_FOR_COLLISION,H_FOR_COLLISION }; }

};

