#pragma once
#include "GameState.h"

class EndState : public GameState
{
public:
	EndState(GameStateMachine* _gsm, SDLApplication* _app, int _status);
	~EndState() {};
};

