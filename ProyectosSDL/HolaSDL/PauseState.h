#pragma once
#include "GameState.h"

class MenuButton;
class GameStateMachine;

class PauseState : public GameState
{
public:
	PauseState(GameStateMachine* _gsm, SDLApplication* _app);
	//El cambio de nivel lo debe desencadenar el metodo update
};

