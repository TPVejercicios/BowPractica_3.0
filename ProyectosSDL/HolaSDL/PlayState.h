#pragma once
#include "GameState.h"

class MenuButton;

//Constantes para la creación de bow
using uint = unsigned int;
const uint START_BOW_POS_X = 0;
const uint BOW_POS_Y = 0;
const uint BOW_H = 100;
const uint BOW_W = 100;
const uint BOW_SCALE = 1;

enum indexObjets {
	OBJECT_BOW = 0, OBJECT_ARROW = 1, OBJECT_BALLON = 2, OBJECT_BUTTERFLY = 3, OBJECT_REWARD = 4
};

class PlayState : public GameState
{
private:
	void CreateBow();
public:
	//El cambio de nivel lo debe desencadenar el metodo update
	PlayState(GameStateMachine* _gsm, SDLApplication* _app);
	~PlayState() {};
	changeTexture(enum textureName);
};