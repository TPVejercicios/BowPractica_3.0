#include "GameStateMachine.h"
#include "SDLApplication.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "PlayState.h"
#include "EndState.h"
#include "Texture.h"
#include <typeinfo>
#include <iostream>
#include <stdexcept>

/*GameStateMachine se encarga de la gestión de los estados*/

//Constructora de GameStateMachine inicializando en mainMenuState
GameStateMachine::GameStateMachine(SDLApplication* _app) {
	app = _app;
	states.push(new MainMenuState(this, app));
}

GameStateMachine::~GameStateMachine() {
	int size = states.size();
	for (int i = 0; i < size; i++ ) {
		auto aux = states.top();
		delete aux;
		states.pop();
	}
	app = nullptr;
}

void GameStateMachine::cleanStack() {
	auto aux = states.top();
	delete aux;
	states.pop();
}

void GameStateMachine::loadMenuState(){
	
	if (typeid(states.top()) == typeid(PlayState)) {
		cleanStack();
	}
	else if (typeid(states.top()) == typeid(PauseState)) {
		cleanStack();
		cleanStack();
	}
	else if (typeid(states.top()) == typeid(EndState)) {
		cleanStack();
		cleanStack();
		cleanStack();
	}
	else {
		throw domain_error("No se ha podido cargar el estado MenuState");
	}
}

//Estas funciones las acabo de ver antes de desconectar y nose si valen para algo o no porque ya estan los CallBacks en SDLApplication
void GameStateMachine::loadGameState() {

	if (typeid(states.top()) == typeid(MainMenuState)) {
		states.push(new PlayState(this, app));
	}
	else if (typeid(states.top()) == typeid(PauseState)) {
		states.pop();
	}
	else {
		throw domain_error("No se ha podido cargar el estado PlayState");
	}
}

//Carga en función del actual estado al estado de pausa
void GameStateMachine::loadPauseState() {
	
	if (typeid(states.top()) == typeid(PlayState)) {
		states.push(new PauseState(this, app));
	}
	else if (typeid(states.top()) == typeid(EndState)) {
		states.push(new EndState(this, app));
	}
	else {
		throw domain_error("No se ha podido cargar el estado PauseState");
	}
}

//Carga el estado EndState si el estado actual es PlayState
void GameStateMachine::loadEndState() {

	if (typeid(states.top()) == typeid(PlayState)) {
		states.push(new EndState(this,app));
	}
	else {
		throw domain_error("No se ha podido cargar el estado EndState");
	}
}



