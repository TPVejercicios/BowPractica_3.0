#pragma once
#include "SDLGameObject.h"
#include "Texture.h"

#pragma region CONSTANTES
const uint MIN_X = 150;
const uint MAX_X = 800;
const uint MAX_Y = 600;
const int MAX_SPEED_BUT = 2;
const int DEAD_DIR = 1;
const int DEAD_SPEED = 10;
#pragma endregion


typedef enum
{
	ALIVE = 0, DEAD = 1
}state_butterfly;

class Butterfly:public SDLGameObject
{
private:
	state_butterfly currState = ALIVE;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int col = 0;
	int row = 0;
public:
	explicit Butterfly(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed)
		:SDLGameObject(_pos, _dir, _h, _w, _texture, _owner, _id, _speed) {};
	~Butterfly() {};
	void render() override { texture->renderFrame(getRect(), row, col, flip); };
	void update()override;
	void startDestruction()override;
	void saveObject(ofstream& write) override;
};

