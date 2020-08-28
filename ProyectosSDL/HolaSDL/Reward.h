#pragma once
#include "EventHandler.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "Texture.h"

using Point2D = Vector2D;

#pragma region CONSTANTES
const int MAX_COLS = 8;
const int MAX_FILS = 10;
const int MAX_Y_POS = 700;
const int MAX_SPEED_REW = 5;
const int ARROWS_TO_ADD = 5;
const int ARROWS_TO_REMOVE = -2;
const int BUTTERFLIES_TO_ADD = 2;
const int BALLON_BIG_SCALE = 2;
const int BUBBLE_X_SIZE = 90;
const int BUBBLE_Y_SIZE = 90;
const int REWARD_GAP_X = 20;
const int REWARD_GAP_Y = 20;
#pragma endregion

enum state_reward
{
	INSIDE = 0, OUTSIDE = 1, PICKED = 2
};
class Reward : public SDLGameObject, public EventHandler
{
private:
	state_reward currState = INSIDE;
	Texture* bubleTex = nullptr;
	Texture* rewardsTex = nullptr;
protected:
	int currRow = 0;
	int currCol = 0;

public:
	Reward(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed, Texture* reward_tex);
	~Reward();
	virtual void render() ;
	virtual void update();
	//virtual void saveToFile(string& data);
	virtual void handleEvent(const SDL_Event event);
	virtual void action() = 0;
	void setState(int state);
};

class AddArrows : public Reward
{
public:
	AddArrows(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed, Texture* reward_tex)
		: Reward(_pos, _dir, _h, _w, _texture, _owner, _id, _speed, reward_tex) {
		currRow = 0;
	};
	virtual void action();
};

class RemoveArrows : public Reward
{
public:
	RemoveArrows(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed, Texture* reward_tex)
		: Reward(_pos, _dir, _h, _w, _texture, _owner, _id, _speed, reward_tex) {
		currRow = 1;
	};
	virtual void action();
};

class ReviveButterflies : public Reward
{
public:
	ReviveButterflies(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed, Texture* reward_tex)
		: Reward(_pos, _dir, _h, _w, _texture, _owner, _id, _speed, reward_tex) {
		currRow = 2;
	};
	virtual void action();
};

class BigBallons : public Reward
{
public:
	BigBallons(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed, Texture* reward_tex)
		: Reward(_pos, _dir, _h, _w, _texture, _owner, _id, _speed, reward_tex) {
		currRow = 3;
	};
	virtual void action();
};


