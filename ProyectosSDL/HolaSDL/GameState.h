#pragma once
#include <list>

using namespace std;

/*Es la clase raz de la jerarqua de estados del juego y tiene al menos tres atributos: el escenario
del estado del juego (list<GameObject*>), los manejadores de eventos (list<EventHandler*>) y el puntero
al juego. Implementa ademas los metodos update, render y handleEvent.*/
class SDLApplication;
class GameObject;
class EventHandler;
class GameStateMachine;
class Background;

//Indice de texturas
enum indexTexturas
{
	ARROW_1 = 0, ARROW_2 = 1, BG_1 = 2, BG_2 = 3, BG_3 = 4, BG_4 = 5, BG_5 = 6, BG_6 = 7, BALLONS = 8,
	BOW_1 = 9, BOW_2 = 10, BUBBLE = 11, BUTTERFLY = 12, DIGITS = 13, REWARDS = 14, BOTON_PLAY = 15, BOTON_GUARDAR = 16,
	BOTON_MENU = 17, BOTON_REINICIAR = 18, BOTON_PAUSA = 19, BOTON_REANUDAR = 20, BG_END = 21, BG_MENU = 22
};

class GameState
{
protected:
	list<GameObject*> gameObjects;
	list<EventHandler*> eventObjects;
	GameStateMachine* gsm = nullptr;		//Puntero al gameStateMachine
	Background* background = nullptr;		//Puntero al background

public:
	GameState(GameStateMachine* _gsm, Texture* _bg);
	~GameState();

	virtual void update() {};
	virtual void render() {};
	virtual void handleEvents() {};
};

