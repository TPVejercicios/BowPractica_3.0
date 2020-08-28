#pragma once
#include "GameState.h"

class MenuButton;
class GameStateMachine;

class PauseState : public GameState
{
private:
	const int W_BUTTON = 100;
	const int H_BUTTON = 100;
public:
	PauseState(GameStateMachine* _gsm, SDLApplication* _app, bool _status);
	void changeTexSaveGame();
};

