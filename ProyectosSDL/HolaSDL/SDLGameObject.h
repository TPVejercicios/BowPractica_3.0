#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>

class GameState;
class Vector2D;
class Texture;

using Point2D = Vector2D;
using uint = unsigned int;


class SDLGameObject : public GameObject
{
protected:
	Point2D pos;
	Vector2D dir;
	int height, width, id;
	int speed;
	Texture* texture = nullptr;
	GameState* ownerState = nullptr;
	bool collisionable = true;
	bool deleting = false;

	//Métodos privados
	void changeTexture(int index);

public:
	SDLGameObject(Point2D _pos, Vector2D _dir, int _height, int _width, Texture* _texture, GameState* _owner, int _id, int speed);
	SDLGameObject() {};
	~SDLGameObject();

	virtual void update();
	virtual void render();
	SDL_Rect getRect() const { return { pos.getX(),pos.getY(),width,height }; };
	bool isCollisionable() { return collisionable; };
	bool isDeleting() { return deleting; };
	int getId() { return id; }
	virtual void startDestruction() {};
};

