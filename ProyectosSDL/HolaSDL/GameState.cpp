#include "GameState.h"
#include "Background.h"
#include "EventHandler.h"
#include "SDLApplication.h"
#include "GameObject.h"
#include "GameStateMachine.h"
#include "Arrow.h"

GameState::GameState(GameStateMachine* _gsm, SDLApplication* _app) :gsm(_gsm), app(_app) {}

//Elimina todos los objetos
GameState::~GameState() {
	for (auto it = gameObjects.begin(); it != gameObjects.end();) {
		auto aux = it;
		it++;
		delete* aux;
	};
	/*for (auto it = eventObjects.begin(); it != eventObjects.end();) {
		auto aux = it;
		it++;
		delete* aux;
	};
	for (auto it = objectsToErase.begin(); it != objectsToErase.end();) {
		auto aux = it;
		it++;
		delete* aux;
	};
	for (auto it = arrows.begin(); it != arrows.end();) {
		auto aux = it;
		it++;
		delete* aux;
	};*/
	gsm = nullptr;		
	background = nullptr;			
	app = nullptr;
}

void GameState::update() {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->update();
	}
}

void GameState::render() {
	background->render({ 0,0,background->getW(),background->getH() }, SDL_FLIP_NONE);
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
		}
	}
}

//Elimina todos los objetos que están en lista a ser borrados
void GameState::deleteObjects() {
	if (!objectsToErase.empty()) {
		auto OTEIT = objectsToErase.begin();
		while (OTEIT != objectsToErase.end()) {
			auto GOIT = gameObjects.begin();
			bool found = false;
			while (!found && GOIT != gameObjects.end()) {
				if ((*OTEIT) == (*GOIT)) {//Coincidencia entre objectToErase y gameObject
					
					if (dynamic_cast<EventHandler*>(*OTEIT)) {
						bool eventFounded = false;
						auto EHIT = eventObjects.begin();
						while (!eventFounded && EHIT != eventObjects.end())
						{
							auto aux = dynamic_cast<GameObject*>(*EHIT);
							if (*OTEIT == aux) {
								
								eventObjects.erase(EHIT);
								eventFounded = true;
								found = true;
							}
							else EHIT++;
						}
					}
					else if (dynamic_cast<Arrow*>(*OTEIT)) {
						auto ARWIT = arrows.begin();
						bool arrowFounded = false;
						while (!arrowFounded && ARWIT != arrows.end())
						{
							if ((*OTEIT) == (*ARWIT)) {
								static_cast<Arrow*>(*ARWIT)->bonusStack();
								arrows.erase(ARWIT);
								arrowFounded = true;
								found = true;
							}
							else ARWIT++;
						}
					}
					auto auxIT = GOIT;
					auto auxEIT = OTEIT;
					GameObject* gm = *GOIT;
					OTEIT++;
					GOIT++;
					objectsToErase.erase(auxEIT);
					gameObjects.erase(auxIT);
					delete (gm);
					found = true;
				}
				else GOIT++;
			}
		}
	}
}
