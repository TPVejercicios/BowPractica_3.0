#pragma once
#include "GameState.h"

class MenuButton;

using uint = unsigned int;

//Constantes para los diferentes objectos de la escena
#pragma region CONST
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

//Constantes para la creación de globos
const uint MIN_X_BALLON = 200;
const uint MAX_X_BALLON = 600;
const uint MIN_Y_BALLON = 700;
const uint BALLON_MAX_SPEED = 18;
const uint BALLON_MIN_SPEED = 5;
const uint BALLON_H = 100;
const uint BALLON_W = 100;

//Constantes para la creación de una mariposa
const uint BUTTERFLY_H = 96;
const uint BUTTERFLY_W = 93;
const uint BUTT_MIN_X = 150;
const uint BUTT_MAX_X = 750;
const uint BUTT_MAX_Y = 550;
const uint BUT_SPEED = 2;

#pragma endregion

enum indexObjets {
	OBJECT_BOW = 0, OBJECT_ARROW = 1, OBJECT_BALLON = 2, OBJECT_BUTTERFLY = 3, OBJECT_REWARD = 4
};

class PlayState : public GameState
{
private:
	int remaingShoots = START_SHOOTS;
	void createBow();
	void createBallon();
	void createButterfly();
public:
	//El cambio de nivel lo debe desencadenar el metodo update
	PlayState(GameStateMachine* _gsm, SDLApplication* _app);
	~PlayState() {};
	void createArrow(int x, int y);
	bool canShoot() { return remaingShoots > 0 ? true : false; };
	void giveArrows() { remaingShoots += 100; };
};