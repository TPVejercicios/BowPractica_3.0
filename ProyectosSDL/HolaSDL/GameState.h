#pragma once
#include <list>

/*Es la clase raz de la jerarqua de estados del juego y tiene al menos tres atributos: el escenario
del estado del juego (list<GameObject*>), los manejadores de eventos (list<EventHandler*>) y el puntero
al juego. Implementa ademas los metodos update, render y handleEvent.*/
class Game;

class GameState
{
protected: 
	//list<GameObject*>
	//list<EventHandler*>
	Game* game = nullptr;
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvent() = 0;
};

