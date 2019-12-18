#include "GameState.h"
#include "Background.h"
#include "EventHandler.h"
#include "SDLApplication.h"
#include "GameObject.h"
#include "GameStateMachine.h"

GameState::GameState(GameStateMachine* _gsm, SDLApplication* _app) {
	gsm = _gsm;
	app = _app;
}

GameState::~GameState() {

}


void GameState::update() {
	cout << "updating" << endl;
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->update();
	}
}

void GameState::render() {
	cout << "Renderizando cosas" << endl;
	background->render({0,0,background->getW(),background->getH()}, SDL_FLIP_NONE);
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->render();
	}
}

void GameState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		cout << "comprobando eventos" << endl;
		if (event.type != SDL_QUIT) {
			for (auto eventIT = eventObjects.begin(); eventIT != eventObjects.end(); ++eventIT) {
				auto* aux = dynamic_cast<EventHandler*>(*eventIT);
				(aux)->handleEvent(event);
			}
		}
	}
}

void CallBackPlay(SDLApplication* app) { 
	app->Play(); 
}

