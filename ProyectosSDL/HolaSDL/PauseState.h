#pragma once
#include "GameState.h"

class MenuButton;
class GameStateMachine;

class PauseState : public GameState
{
public:
	PauseState(GameStateMachine* _gsm, SDLApplication* _app) : GameState(_gsm, _app) {};
	~PauseState() {};
	//El cambio de nivel lo debe desencadenar el metodo update
	virtual void update() {};
	virtual void render() {};
	virtual void handleEvent() {};
};

