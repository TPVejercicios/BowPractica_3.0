#include "GameState.h"
#include "Background.h"
#include "EventHandler.h"
#include "SDLApplication.h"
#include "GameObject.h"
#include "GameStateMachine.h"

GameState::GameState(GameStateMachine* _gsm) {
	gsm = _gsm;
	background = new Background(600, 800, gsm->getApp()->getTexture(BG_MENU));
}

GameState::~GameState() {

}

/*
GameState::void update() {

}

GameState::void render() {
	SDL_RenderClear(renderer);
	background->render();
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->render();
	}
	SDL_RenderPresent(renderer);
}

GameState::void handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type != SDL_QUIT) {
			for (auto eventIT = eventObjects.begin(); eventIT != eventObjects.end(); ++eventIT) {
				auto* aux = dynamic_cast<EventHandler*>(*eventIT);
				(aux)->handleEvent(event);
			}
		}
		else exit = true;
	}
}*/