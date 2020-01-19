#pragma once
#include "GameState.h"

class MenuButton;


using uint = unsigned int;


//Constantes para la creación de bow
const uint START_BOW_POS_X = 0;
const uint BOW_POS_Y = 0;
const uint BOW_H = 100;
const uint BOW_W = 100;
const uint BOW_SCALE = 1;
const int BOW_SPEED = 20;

//Constantes para generar el boton de pause
const uint BUTTON_POS_X = 400;
const uint BUTTON_POS_Y = 400;

//Constantes para la creación de una flecha
const uint ARROW_H = 20;
const uint ARROW_W = 100;
const uint ARROW_SPEED = 50;
const int START_SHOOTS = 10;


enum indexObjets {
	OBJECT_BOW = 0, OBJECT_ARROW = 1, OBJECT_BALLON = 2, OBJECT_BUTTERFLY = 3, OBJECT_REWARD = 4
};

class PlayState : public GameState
{
private:
	int remaingShoots = START_SHOOTS;
	void createBow();
public:
	//El cambio de nivel lo debe desencadenar el metodo update
	PlayState(GameStateMachine* _gsm, SDLApplication* _app);
	~PlayState() {};
	void createArrow(int x, int y);
	bool canShoot() { return remaingShoots > 0 ? true : false; };
};