#pragma once
#include "SDLGameObject.h"

class Game;
using CallBackOnClick = void(Game* game);

class MenuButton : public SDLGameObject
{
private:
	//Texture* texture;
public:
	virtual void update() {};
	virtual void render() {};
	virtual void handleEvent() {};
	
	CallBackOnClick* action {};
};

