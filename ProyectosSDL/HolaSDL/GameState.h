#pragma once
#include <list>

using namespace std;
using uint = unsigned int;

class SDLApplication;
class GameObject;
class EventHandler;
class GameStateMachine;
class Background;
class Texture;
class Arrow;

class GameState
{
protected:
	const int MAX_LEVELS = 6;
	list<GameObject*> gameObjects;			//Lista de todos los objetos
	list<EventHandler*> eventObjects;		//Lista de objetos con eventos
	list<GameObject*> objectsToErase;		//Listas de objetos a borrar
	list<Arrow*> arrows;					//Lista con las flechas
	GameStateMachine* gsm = nullptr;		//Puntero al gameStateMachine
	Texture* background = nullptr;			//Puntero al background
	SDLApplication* app = nullptr;		

	void addGameObject(GameObject* _gm) { gameObjects.push_back(_gm); };
	void addEventObject(EventHandler* _eH) { eventObjects.push_back(_eH); };


public:
	//Enumerados para la asignación de texturas
#pragma region ENUMERADOS
	enum indexTexturas
	{
		ARROW_1 = 0, ARROW_2 = 1, BG_1 = 2, BG_2 = 3, BG_3 = 4, BG_4 = 5, BG_5 = 6, BG_6 = 7, BALLONS = 8,
		BOW_1 = 9, BOW_2 = 10, BUBBLE = 11, BUTTERFLY = 12, DIGITS = 13, REWARDS = 14, BOTON_PLAY = 15, BOTON_GUARDAR = 16,
		BOTON_MENU = 17, BOTON_REINICIAR = 18, BOTON_PAUSA = 19, BOTON_REANUDAR = 20, BG_END = 21, BG_MENU = 22
	};

	//Estructura para definir cada nivel
	typedef struct {
		indexTexturas currTex;
		int butterflyNum;
		int arrows;
		int pointsToReach;
		uint frame_ballon;
	}level;

	//Array constante para determinar los valores de cada nivel
	level LEVELS[6] = {
		{BG_1,5,10,50,500},		//nivel 1
		{BG_2,10,12,250,450},	//nivel 2
		{BG_3,12,15,550,400},	//nivel 3
		{BG_4,15,18,800,350},	//nivel 4
		{BG_5,16,20,1000,250},	//nivel 5
		{BG_6,20,25,1250,175}	//nivel 6
	};

	const enum buttonIDs {
		MENU = 0, PLAY = 1, LOAD = 2, SAVE = 3, EXIT = 4, PAUSE = 5
	};
	const enum rewardIDs {
		ADD_ARROW = 0, QUIT_ARROW = 1, ADD_BUTTER = 2, SCALE_BUTTER = 3
	};

	const enum indexObjets {
		OBJECT_BOW = 0, OBJECT_ARROW = 1, OBJECT_BALLON = 2, OBJECT_BUTTERFLY = 3, OBJECT_REWARD = 4
	};
#pragma endregion

	GameState(GameStateMachine* _gsm, SDLApplication* _app);
	~GameState();
	//Métodos virtuales
	virtual void update();
	virtual void render();
	virtual void handleEvents();

	void killObject(GameObject* _gm) { objectsToErase.push_back(_gm); };
	SDLApplication* getApp() { return app; };
	void deleteObjects();
};
