#pragma once
#include "GameState.h"

class MenuButton;

/*PlayState: Implementa el estado del juego del Arrows propiamente dicho. Incluye por tanto gran parte de
los atributos y funcionalidad que antes tenamos en la clase Game. La antigua lista de objetos del juego ahora
sera el escenario (list<GameObject*>) heredado de GameState. El cambio de nivel lo debe desencadenar el
metodo update.*/

class PlayState : public GameState
{
public:
	//El cambio de nivel lo debe desencadenar el metodo update
	virtual void update() {};
	virtual void render() {};
	virtual void handleEvent() {};
};

