#pragma once
#include "GameState.h"

class MenuButton;
//class Texture;

class EndState : public GameState
{
public:
	EndState(GameStateMachine* _gsm, Texture* _texture);
	~EndState() {};
	//El cambio de nivel lo debe desencadenar el metodo update
	virtual void update() {};
	virtual void render() {};
	virtual void handleEvent() {};
};

