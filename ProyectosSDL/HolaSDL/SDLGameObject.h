#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>
#include <fstream>


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
	double height, width, speed;
	double id;
	Texture* texture = nullptr;
	GameState* ownerState = nullptr;
	bool collisionable = true;
	bool deleting = false;
	//variable que determina si el objeto se puede guardar
	bool storable = false;

	//Métodos privados
	void changeTexture(int index);

public:
	SDLGameObject(Point2D _pos, Vector2D _dir , int _height, int _width, Texture* _texture, GameState* _owner, int _id, int speed);
	SDLGameObject() {};	//Para el scb
	~SDLGameObject();

	virtual void update();
	virtual void render();
	virtual void saveObject(ofstream& write);

	SDL_Rect getRect() const { return SDL_Rect({ (int)pos.getX(),(int)pos.getY(), (int)width, (int)height }); }
	bool isCollisionable() { return collisionable; };
	bool isDeleting() { return deleting; };
	int getId() { return (int)id; }
	virtual void startDestruction() {};
	void setTexture(Texture* tex) { texture = tex; }
};

