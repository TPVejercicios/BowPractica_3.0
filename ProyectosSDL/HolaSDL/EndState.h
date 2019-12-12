#pragma once
#include "GameState.h"

class MenuButton;

class EndState : public GameState
{
public:
	EndState(GameStateMachine* _gsm) : GameState(_gsm) {};
	~EndState() {};
	//El cambio de nivel lo debe desencadenar el metodo update
	virtual void update() {};
	virtual void render() {};
	virtual void handleEvent() {};
};

