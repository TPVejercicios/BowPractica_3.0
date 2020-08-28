#pragma once
#include <stack>

class GameState;
class Texture;
class SDLApplication;
class PlayState;

//void CallBackToPush(GameState* newState, stack<GameState*>* states);
//using CallBackOnClick = void(GameState * newState, stack<GameState*> & states);

/*
	GameStateMachine gestiona la pila de estados
	metiendo o sacando estados de la pila
*/
using namespace std;

enum class STATES
{
	MenuState, PlayState, PauseState, EndState, SaveState, LoadState,
	Clean
};

class GameStateMachine
{
private:
	//Pila de estados
	stack<GameState*> states;
	//Estado auxiliar
	GameState* aux = nullptr;
	//El siguiente en la cola 
	STATES nextState = STATES::Clean;
	int statesToErase = 0;
	//Puntero a la app
	SDLApplication* app = nullptr;
	//Quita el estado superior de la pila
	void popStack();
public:
	//Construye mainMenu y lo mete a la pila
	GameStateMachine(SDLApplication* _app);
	//Recorre la pila limpiando todos los estados
	~GameStateMachine();
	//Devuelve el estado top de la pila
	GameState* currentState() { return states.top(); };
	//Añade un estado al top de la pila
	inline void pushState(GameState* _currState) { states.push(_currState); };
	//Hace un pop de la pila y luego mete un estado
	void changeState(GameState* _currState) { states.pop(); states.push(_currState); };
	//Quita el último estado de la pila
	void popState() { popStack(); }
	//Carga el estado de menu en función del estado actual
	void loadMenuState();
	//Carga el estado de game en función del estado actual
	void loadPlayState();
	//Carga el estado de pausa en función del estado actual
	void loadPauseState(bool status);
	//Carga el estado de endGame en función del estado actual
	void loadEndState(int status);
	//Carga el estado SaveState en función de quien lo ha llamado
	void saveGame();
	//Carga el estado LoadState en función de quien lo ha llamado
	void loadGame();
	//Elimina los estados pendientes a eliminar
	void deleteStates();
	//Suma a los estados pendientes a elimnar
	void killStates(int num) { statesToErase += num; }
	//Devuelve el estado auxiliar
	GameState* getAux() { return aux; };
	//
	inline void nextStateToPush(STATES state) { nextState = state; }
	SDLApplication* getApp() { return app; };
	virtual void render() {};
	virtual void update() {};
};

