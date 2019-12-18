#pragma once
#include "GameState.h"

class MenuButton;
//class Texture;

class EndState : public GameState
{
public:
	EndState(GameStateMachine* _gsm, SDLApplication* _app);
	~EndState() {};
	//El cambio de nivel lo debe desencadenar el metodo update
};

