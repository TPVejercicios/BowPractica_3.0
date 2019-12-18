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
	states.push(new MainMenuState(this,app->getTexture(app->BG_MENU), app->getTexture(app->BOTON_PLAY)));
}

GameStateMachine::~GameStateMachine() {
	
}


void GameStateMachine::loadMenuState(){
	
	if (typeid(states.top()) == typeid(PlayState)) {
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
	}
}

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
		states.push(new PauseState(this,app->getTexture(1)));
	}
	else if (typeid(states.top()) == typeid(EndState)) {
		states.push(new EndState(this,app->getTexture(1)));
	}
	else {
		cout << "Error al cargar estado" << "PauseState" << endl;
	}
}

void GameStateMachine::loadEndState() {

	if (typeid(states.top()) == typeid(PlayState)) {
		states.push(new EndState(this, app->getTexture(1)));
	}
	else {
		cout << "Error al cargar estado" << "EndState" << endl;
	}
}



