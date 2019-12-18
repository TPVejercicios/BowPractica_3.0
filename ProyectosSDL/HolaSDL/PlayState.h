#pragma once
#include "GameState.h"

class MenuButton;

/*PlayState: Implementa el estado del juego del Arrows propiamente dicho. Incluye por tanto gran parte de
los atributos y funcionalidad que antes tenamos en la clase Game. La antigua lista de objetos del juego ahora
sera el escenario (list<GameObject*>) heredado de GameState. El cambio de nivel lo debe desencadenar el
metodo update.*/

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
};