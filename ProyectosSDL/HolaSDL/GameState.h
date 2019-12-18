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
class Texture;

class GameState
{
protected:
	list<GameObject*> gameObjects;
	list<EventHandler*> eventObjects;
	GameStateMachine* gsm = nullptr;		//Puntero al gameStateMachine
	Texture* background = nullptr;		//Puntero al background
	SDLApplication* app = nullptr;

public:
	GameState(GameStateMachine* _gsm, Texture* _bg);
	~GameState();

	virtual void update();
	virtual void render();
	virtual void handleEvents() {};

	void addGameObject(GameObject* _gm) { gameObjects.push_back(_gm); };
	void addEventObject(EventHandler* _eH) { eventObjects.push_back(_eH); };
};

