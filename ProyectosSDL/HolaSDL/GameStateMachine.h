#pragma once
#include <stack>
class GameState;

class GameStateMachine
{
private:
	//stack <GameState*> states;

public:
	//Estado inicial: MainMenuState
	GameStateMachine() {};

	//Devuelve el estado de arriba de la pila
	const GameState* currentState() {};

	//Añade un estado arriba de la pila
	void pushState(GameState* _currState) {};

	//LLama a pop() y luego a push()
	void changeState(GameState* _currState) {};

	//Quita el último estado de la pila
	void popState() {};

};

