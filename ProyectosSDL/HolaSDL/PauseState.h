#pragma once
#include "GameState.h"

class MenuButton;
class GameStateMachine;

class PauseState : public GameState
{
public:
	PauseState(GameStateMachine* _gsm, Texture* _texture) : GameState(_gsm, _texture) {};
	~PauseState() {};
	//El cambio de nivel lo debe desencadenar el metodo update
	virtual void update() {};
	virtual void render() {};
	virtual void handleEvent() {};
};

