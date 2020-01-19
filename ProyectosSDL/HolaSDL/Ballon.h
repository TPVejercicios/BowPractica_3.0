#pragma once
#include "SDLGameObject.h"
#include "Texture.h"

const int MAX_ROW = 6;
int const TOP_LIMIT = -200; 
enum status
{
	SWOLLEN, PUNCTURED
};

class Ballon :public SDLGameObject
{
private:
	status currStatus = SWOLLEN;
	int row = 0;
	int col = 0;
public:
	Ballon(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed) 
		:SDLGameObject(_pos, _dir, _h, _w, _texture, _owner, _id, _speed) {
		row = rand() % MAX_ROW;
	};
	virtual void render() { texture->renderFrame(getRect(), row, col, SDL_FLIP_NONE); };
	virtual void update();
};

