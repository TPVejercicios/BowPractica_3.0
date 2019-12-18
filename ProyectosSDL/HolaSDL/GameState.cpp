#include "GameState.h"
#include "Background.h"
#include "EventHandler.h"
#include "SDLApplication.h"
#include "GameObject.h"
#include "GameStateMachine.h"

GameState::GameState(GameStateMachine* _gsm, Texture* _bg) {
	gsm = _gsm;
	background = _bg;

}

GameState::~GameState() {

}


void GameState::update() {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->update();
	}
}

void GameState::render() {
	background->render({0,0,background->getW(),background->getH()}, SDL_FLIP_NONE);
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->render();
	}
}


