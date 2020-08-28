#pragma once
#include "GameState.h"

/*
	Clase inicializa los botones del menú principal
*/

class MainMenuState : public GameState
{
public:
	MainMenuState(GameStateMachine* _gsm, SDLApplication* _app);
private:
	const int BUTTON_H = 100;
	const int BUTTON_W = 100;
	void createPlayButton();
	void createLoadButton();
	void createExitButton();
};

