#pragma once
#include "GameState.h"

class MenuButton;
class GameStateMachine;
class Texture;

class MainMenuState : public GameState
{
public:
	MainMenuState(GameStateMachine* _gsm);
	//El cambio de nivel lo debe desencadenar el metodo update
	virtual void update() {};
	virtual void render() {};
	virtual void handleEvent() {};
};

