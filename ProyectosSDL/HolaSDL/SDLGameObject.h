#pragma once
#include "GameObject.h"
#include "Vector2D.h"

class GameState;
class Vector2D;
class Texture;

using Point2D = Vector2D;

class SDLGameObject : public GameObject
{
protected:
	Point2D pos;
	Vector2D dir;
	int height, width;
	Texture* texture = nullptr;
	GameState* ownerState = nullptr;
public:
	SDLGameObject(Texture* _texture, Point2D _pos, Vector2D _dir, int _height, int _width, GameState* _owner);
	~SDLGameObject() {};

	virtual void update();
	virtual void render();
	virtual void handleEvent() = 0;
};

