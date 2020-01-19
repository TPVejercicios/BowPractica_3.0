#include "MainMenuState.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(GameStateMachine* _gsm, SDLApplication* _app):
	GameState(_gsm, _app)
{
	background = app->getTexture(22);
	createPlayButton();
	createLoadButton();
	createExitButton();
}


void MainMenuState::createPlayButton() {
	MenuButton* butonPlay = new MenuButton({ BUTTON_PLAY_X,BUTTON_PLAY_Y }, { BUTTON_PLAY_X,BUTTON_PLAY_Y }, BUTTON_W, BUTTON_H, app->getTexture(15), this, 0, app, CallBackPlay);
	this->addGameObject(butonPlay);
	this->addEventObject(butonPlay);
	butonPlay = nullptr;
}
void MainMenuState::createLoadButton() {
	MenuButton* butonLoad = new MenuButton({ BUTTON_LOAD_X,BUTTON_LOAD_Y }, { BUTTON_LOAD_X,BUTTON_LOAD_Y }, BUTTON_W, BUTTON_H, app->getTexture(16), this, 0, app, CallBackLoad);
	this->addGameObject(butonLoad);
	this->addEventObject(butonLoad);
	butonLoad = nullptr;
}
void MainMenuState::createExitButton() {
	MenuButton* butonExit = new MenuButton({ BUTTON_EXIT_Y,BUTTON_EXIT_X }, { BUTTON_EXIT_Y,BUTTON_EXIT_X }, BUTTON_W, BUTTON_H, app->getTexture(19), this, 0, app, CallBackExit);
	this->addGameObject(butonExit);
	this->addEventObject(butonExit);
	butonExit = nullptr;
}