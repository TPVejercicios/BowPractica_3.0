#pragma once
#include <list>
#include "Resources.h"
#include "checkML.h"

using namespace std;
using uint = unsigned int;

class SDLApplication;
class GameObject;
class EventHandler;
class GameStateMachine;
class Background;
class Texture;
class Arrow;

/*
	GameState manda los updates y renders los diferentes game objects.
	También elimina los objetos.
*/

class GameState
{
protected:
	bool freeze = false;
	int currLevel = 0;
	const int MAX_LEVELS = 6;
	//Lista de todos los objetos
	list<GameObject*> gameObjects;		
	//Lista de objetos con eventos
	list<EventHandler*> eventObjects;	
	//Listas de objetos a borrar
	list<GameObject*> objectsToErase;	
	//Lista con las flechas
	list<Arrow*> arrows;	
	//Puntero al gameStateMachine
	GameStateMachine* gsm = nullptr;		
	//Texture* background = nullptr;			//Puntero al background
	SDLApplication* app = nullptr;		
	//Agrega un gameObject a la lista de gameObjects
	inline void addGameObject(GameObject* _gm) { gameObjects.push_back(_gm); };
	//Agrega un eventObject a la lista de evetObjects
	inline void addEventObject(EventHandler* _eH) { eventObjects.push_back(_eH); };
public:
	//Enumerados para la asignación de texturas
#pragma region ENUMERADOS

	//Estructura para definir cada nivel
	typedef struct {
		int butterflyNum;
		int arrows;
		int pointsToReach;
		double frame_ballon;
	}level;

	//Array constante para determinar los valores de cada nivel
	level LEVELS[6] = {
		//num de mariposas  //flechas	//Puntos a conseguir	//Frame rate de los globos
		{5,					10,			50,						800},						//nivel 1
		{10,				12,			250,					700},						//nivel 2
		{12,				15,			550,					600},						//nivel 3
		{15,				18,			800,					500},						//nivel 4
		{16,				20,			1000,					400},						//nivel 5
		{20,				25,			1250,					300}						//nivel 6
	};
#pragma endregion
	GameState(GameStateMachine* _gsm, SDLApplication* _app);
	~GameState();
	//Métodos virtuales
	virtual void update();
	virtual void render();
	virtual void handleEvents();
	//Agrega un gameObject a la lista de objetos a borrar
	void killObject(GameObject* _gm) { objectsToErase.push_back(_gm); };
	//Devuelve la app
	SDLApplication* getApp() { return app; };
	//Elimina los objetos de la lista a borrar
	void deleteObjects();
	//Manda a guardar a todos los elementos "guardables" del juego
	void saveGameObjects();
	//devuelve el actual nivel
	int getCurrLevel() { return currLevel; }
	//Devuelve el primer objeto en función del id
	GameObject* getObjById(int id_);
	//Activa la pausa
	inline void activeFreeze() { freeze = true; };
	inline void deactiveFreeze() { freeze = false; };
};
