#pragma once
#include "GameState.h"

class MenuButton;
class Texture;				

const int BUTTON_PLAY_X = 400;
const int BUTTON_PLAY_Y = 400;
const int BUTTON_H = 100;
const int BUTTON_W = 100;

		

class MainMenuState : public GameState
{

public:
	MainMenuState(GameStateMachine* _gsm, Texture* _bg, Texture* _buttonPlay);
	//El cambio de nivel lo debe desencadenar el metodo update

};

