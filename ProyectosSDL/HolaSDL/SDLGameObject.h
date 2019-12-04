#pragma once
#include "GameObject.h"

class GameState;

class SDLGameObject : public GameObject
{
protected:
	//Point2D pos;
	int height, width;
	//Texture* texture = nullptr;
	GameState* ownerState = nullptr;
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvent() = 0;
};

