#pragma once
#include <stack>

class GameState;
class Texture;
class SDLApplication;

using namespace std;

class GameStateMachine
{
private:
	stack<GameState*> states;
	SDLApplication* app = nullptr;
public:
	//Estado inicial: MainMenuState
	GameStateMachine(SDLApplication* _app);
	~GameStateMachine();

	//Devuelve el estado de arriba de la pila
	GameState* currentState() { return states.top(); };

	//A�ade un estado arriba de la pila
	void pushState(GameState* _currState) { states.push(_currState); };

	//LLama a pop() y luego a push()
	void changeState(GameState* _currState) { states.pop(); states.push(_currState); };

	//Quita el �ltimo estado de la pila
	void popState() { states.pop(); };

	void loadMenuState();

	void loadGameState();

	void loadPauseState();

	void loadEndState();

};

