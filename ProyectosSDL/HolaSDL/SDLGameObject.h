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
	int height, width, id;
	Texture* texture = nullptr;
	GameState* ownerState = nullptr;
	bool collisionable = false;

public:
	SDLGameObject(Point2D _pos, Vector2D _dir, int _height, int _width, Texture* _texture, GameState* _owner, int _id);
	~SDLGameObject() {};

	virtual void update();
	virtual void render();
};

