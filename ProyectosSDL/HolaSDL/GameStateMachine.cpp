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


//Constructora de GameStateMachine inicializando en mainMenuState
GameStateMachine::GameStateMachine(SDLApplication* _app) {
	app = _app;
	states.push(new MainMenuState(this, app));		//Para probar Menu
	//states.push(new PlayState(this, app));		//Para probar Play
	//states.push(new EndState(this, app));			//Para probar End
	//states.push(new PauseState(this, app));		//Para probar Pause
}

GameStateMachine::~GameStateMachine() {
	
}


void GameStateMachine::loadMenuState(){
	
	/*if (typeid(states.top()) == typeid(PlayState)) {
		states.pop();
	}
	else if (typeid(states.top()) == typeid(PauseState)) {
		states.pop();
		states.pop();
	}
	else if (typeid(states.top()) == typeid(EndState)) {
		states.pop();
		states.pop();
		states.pop();
	}
	else {
		cout << "Error al cargar estado" << endl;
	}*/
}

//Estas funciones las acabo de ver antes de desconectar y nose si valen para algo o no porque ya estan los CallBacks en SDLApplication
void GameStateMachine::loadGameState() {

	if (typeid(states.top()) == typeid(MainMenuState)) {
		cout << "CAMBIO ESCENA A PLAYSTATE" << endl;
		//states.push(new PlayState(this));
	}
	else if (typeid(states.top()) == typeid(PauseState)) {
		states.pop();
	}
	else {
		cout << "Error al cargar estado " << "PlayState" <<endl;
	}
}

void GameStateMachine::loadPauseState() {
	
	if (typeid(states.top()) == typeid(PlayState)) {
		states.push(new PauseState(this, app));
	}
	else if (typeid(states.top()) == typeid(EndState)) {
		states.push(new EndState(this,app));
	}
	else {
		cout << "Error al cargar estado" << "PauseState" << endl;
	}
}

void GameStateMachine::loadEndState() {

	if (typeid(states.top()) == typeid(PlayState)) {
		states.push(new EndState(this,app));
	}
	else {
		cout << "Error al cargar estado" << "EndState" << endl;
	}
}



