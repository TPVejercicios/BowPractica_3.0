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
	void CallBackPlay(SDLApplication* app);

	/*void CallBackLoad(SDLApplication* app) {
		//app->Load();
	}
	void CallBackExit(SDLApplication* app) {
		//app->Exit();
	}
	void CallBackSave(SDLApplication* app) {
		//app->Save();
	}
	void CallBackMenu(SDLApplication* app) {
		//app->Menu();
	}*/

public:
	GameState(GameStateMachine* _gsm, Texture* _bg);
	~GameState();

	virtual void update();
	virtual void render();
	virtual void handleEvents() {};
	SDLApplication* getApp() { return app; };

	void addGameObject(GameObject* _gm) { gameObjects.push_back(_gm); };
	void addEventObject(EventHandler* _eH) { eventObjects.push_back(_eH); };

	enum buttonIDs {
		MENU = 0, PLAY = 1, LOAD = 2, SAVE = 3 , EXIT = 4
	};
};

