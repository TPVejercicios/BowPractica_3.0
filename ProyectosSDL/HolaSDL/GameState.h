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
	list<GameObject*> gameObjects;			//Lista de todos los objetos
	list<EventHandler*> eventObjects;		//Lista de objetos con eventos
	list<GameObject*> objectsToErase;
	GameStateMachine* gsm = nullptr;		//Puntero al gameStateMachine
	Texture* background = nullptr;			//Puntero al background
	SDLApplication* app = nullptr;		

	void addGameObject(GameObject* _gm) { gameObjects.push_back(_gm); };
	void addEventObject(EventHandler* _eH) { eventObjects.push_back(_eH); };
	void killObject(GameObject* _gm) { gameObjects.push_back(_gm); };

	enum buttonIDs {
		MENU = 0, PLAY = 1, LOAD = 2, SAVE = 3, EXIT = 4, PAUSE = 5
	};
public:
	GameState(GameStateMachine* _gsm, SDLApplication* _app);
	~GameState();
	virtual void update();
	virtual void render();
	virtual void handleEvents();
	SDLApplication* getApp() { return app; };

};
