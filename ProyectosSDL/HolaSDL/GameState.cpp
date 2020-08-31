#include "GameState.h"
#include "EventHandler.h"
#include "SDLApplication.h"
#include "GameObject.h"
#include "GameStateMachine.h"
#include "Arrow.h"

#include <fstream>

GameState::GameState(GameStateMachine* _gsm, SDLApplication* _app) :gsm(_gsm), app(_app) {}

//Elimina todos los objetos
GameState::~GameState() {
	for (auto it = gameObjects.begin(); it != gameObjects.end();) {
		auto aux = it;
		it++;
		delete* aux;
	};
	gameObjects.clear();
	objectsToErase.clear();
	arrows.clear();
	eventObjects.clear();
	gsm = nullptr;				
	app = nullptr;
}

void GameState::update() {
	//Primero borra los objetos que están en la lista de ser eliminados
	deleteObjects();

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->update();
	}
}

void GameState::render() {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->render();
	}
}

void GameState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type != SDL_QUIT) {
			for (auto eventIT = eventObjects.begin(); eventIT != eventObjects.end(); ++eventIT) {
				auto* aux = dynamic_cast<EventHandler*>(*eventIT);
				(aux)->handleEvent(event);
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)app->Exit();
		}
	}
}

//Elimina todos los objetos que están en lista a ser borrados
void GameState::deleteObjects() {

	for (auto it = objectsToErase.begin(); it != objectsToErase.end();) {
		auto  aux = it;

		//Es un objeto de evento?
		auto  eH = dynamic_cast<EventHandler*>(*aux);
		if (eH != nullptr) {
			eventObjects.remove(eH);
		}

		//Es una flecha?
		auto  arrow = dynamic_cast<Arrow*>(*aux);
		if (arrow != nullptr) {
			arrows.remove(arrow);
		}

		it++;
		delete* aux;
		gameObjects.remove(*aux);
		objectsToErase.remove(*aux);
	}
}

void GameState::saveGameObjects()
{
	ofstream write("saveGame.txt");
	if (write.is_open()) {
		for (auto gm = gameObjects.begin(); gm != gameObjects.end(); ++gm) {
			static_cast<SDLGameObject*>(*(gm))->saveObject(write);
			write << endl;
		}
	}
	else
	{
		throw exception("No se ha podido abrir el archivo de texto para guardar.");
	}

	write.close();
}

GameObject* GameState::getObjById(int id_)
{
	auto ob = gameObjects.begin();
	bool finded = false;
	while (ob != gameObjects.end() && !finded)
	{
		auto obj = dynamic_cast<SDLGameObject*>(*ob);
		if (obj != nullptr && obj->getId() == id_) {
			finded = false;
			return (*ob);
		}
		ob++;
		if (ob == gameObjects.end()) {
			return nullptr;
		}
	}
}
