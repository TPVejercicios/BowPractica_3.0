#pragma once
#include "GameState.h"

class MenuButton;
class Texture;				

//Constantes para determinar boton play
const int BUTTON_PLAY_X = 150;
const int BUTTON_PLAY_Y = 400;

//Constantes para determinar boton load
const int BUTTON_LOAD_X = 300;
const int BUTTON_LOAD_Y = 400;

//Constantes para determinar boton exit
const int BUTTON_EXIT_X = 450;
const int BUTTON_EXIT_Y = 400;

//Constantes para determinar las dimensiones de los botones
const int BUTTON_H = 100;
const int BUTTON_W = 100;

class MainMenuState : public GameState
{
private:
	void createPlayButton();
	void createLoadButton();
	void createExitButton();

public:
	MainMenuState(GameStateMachine* _gsm, SDLApplication* _app);
	//El cambio de nivel lo debe desencadenar el metodo update
};

