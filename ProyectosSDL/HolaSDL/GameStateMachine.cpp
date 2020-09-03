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
#include <stack>
#include "checkML.h"



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

//Elimina el estado top de la pila
void GameStateMachine::popStack() {
	auto aux = states.top();
	delete aux;
	states.pop();
}

//Carga el menuState en función del estado que le ha llamado
void GameStateMachine::loadMenuState(){
	//si estamos en playState eliminamos un estado, el playState
	if (typeid(*(states.top())).name() == typeid(PlayState).name()) {
		statesToErase++;
	}
	//Si estamos en pause o end eliminados dos estados
	else if (typeid(*(states.top())).name() == typeid(PauseState).name() ||
		typeid(*(states.top())).name() == typeid(EndState).name()) {
		statesToErase += 2;
	}
	else {
		throw domain_error("No se ha podido cargar el estado MenuState");
	}
}

//Carga el playState en función del estado que le ha llamado
void GameStateMachine::loadPlayState() {
	if (typeid(*(states.top())).name() == typeid(MainMenuState).name()) {
		states.push(new PlayState(this, app));
	}
	else if (typeid(*(states.top())).name() == typeid(PauseState).name()
		|| typeid(*(states.top())).name() == typeid(EndState).name()) {
		statesToErase++;
	}
	else {
		throw domain_error("No se ha podido cargar el estado PlayState");
	}
}

//Carga el estado PauseState si el estado que le llama es el PlayState
void GameStateMachine::loadPauseState(bool status) {
	if (typeid(*(states.top())).name() == typeid(PlayState).name()) {
		aux = states.top();
		states.push(new PauseState(this, app, status));
		states.top()->activeFreeze();
	}
	else {
		throw domain_error("No se ha podido cargar el estado PauseState");
	}
}

//Carga el estado EndState si el estado actual es PlayState
void GameStateMachine::loadEndState(int status) {
	if (typeid(*(states.top())).name() == typeid(PlayState).name()) {
		states.push(new EndState(this, app, status));
	}
	else {
		throw domain_error("No se ha podido cargar el estado EndState");
	}
}

void GameStateMachine::saveGame()
{
	if (typeid(*(states.top())).name() == typeid(PauseState).name()) {
		//Destruimos el estado pausa
		popStack();
		//Enviamos a guardar todos los objetos "guardables" de gameState
		states.top()->saveGameObjects();
		//Devolvemos el estado top de los estados a la pausa
		loadPauseState(true);
	}
	else {
		throw domain_error("No se ha podido cargar el estado EndState");
	}
}

void GameStateMachine::loadGame()
{
	if (typeid(*(states.top())).name() == typeid(MainMenuState).name() /*|| typeid(*(states.top())).name() == typeid(EndState).name()*/) {
		ifstream read("saveGame.txt");
		if (read.is_open()) {
			auto playState = new PlayState(this, app, true);
			int cadena;
			while (!read.eof()) {
				read >> cadena;
				switch (cadena)
				{
				case 99:
					int nivel, puntos, flechas, butterflies;
					read >> nivel >> puntos >> flechas >> butterflies;
					playState->setLevel(nivel, puntos, flechas, butterflies);
					break;
				case (int)Resources::TextureId::Ballons:
					//posX , posY y velocidad
					int x, y, speed;
					read >> x >> y >> speed;
					playState->createBallon(x, y, speed);
					break;
				case (int)Resources::TextureId::Butterflies:
					double dirX, dirY;
					read >> x >> y >> dirX >> dirY;
					playState->createButterfly({ (double)x,(double)y }, { (double)dirX,(double)dirY });
					break;
				case (int)Resources::TextureId::LoadedBow: //17
					int status;
					read >> y >> status;
					playState->setBow(y, status);
					break;
				case (int)Resources::TextureId::ArrowRight:
					//id , posición y stacks
					int stacks;
					read >> x >> y >> stacks;
					playState->createArrow(x, y, stacks);
					break;
				case (int)Resources::TextureId::Rewards:
					//id, kind, state, posx, posy
					int kind, state;
					double xr, yr;
					read >> kind >> state >> xr >> yr;
					playState->createKnowReward({ xr, yr }, kind, state);
					break;
				default:
					read.ignore();
					break;
				}
			}
			read.close();
			states.push(playState);
			playState = nullptr;
			loadPauseState(true);
		}
	}
	else 
	{
		throw domain_error("No se ha podido leer el fichero de guardado");
	}
}

void GameStateMachine::deleteStates()
{
	if (statesToErase > 0) {
		for (int i = 0; i < statesToErase; i++) {
			popStack();
		}
		statesToErase = 0;
	}
	if (nextState != STATES::Clean) {
		switch (nextState)
		{
		case::STATES::EndState:
			loadEndState(2);
			break;
		case::STATES::PlayState:
			loadPlayState();
			break;
		case::STATES::PauseState:
			loadPauseState(false);
			break;
		case::STATES::MenuState:
			loadMenuState();
			break;
		case::STATES::SaveState:
			saveGame();
			break;
		case::STATES::LoadState:
			loadGame();
			break;
		default:
			throw exception("No existe el estado");
			break;
		}
		nextState = STATES::Clean;
	}
}

