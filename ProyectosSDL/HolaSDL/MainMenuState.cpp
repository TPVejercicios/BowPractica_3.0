#include "MainMenuState.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(GameStateMachine* _gsm, SDLApplication* _app):
	GameState(_gsm, _app)
{
	background = app->getTexture(22);	//Arreglar el index de las texturas
	//Boton Play
	MenuButton* butonPlay = new MenuButton({ 150,400 }, { BUTTON_PLAY_X,BUTTON_PLAY_Y }, BUTTON_W, BUTTON_H, app->getTexture(15), this, 0, app, CallBackPlay);
	this->addGameObject(butonPlay);
	this->addEventObject(butonPlay);
	butonPlay = nullptr;
	//Boton Load
	MenuButton* butonLoad = new MenuButton({ 300,400 }, { BUTTON_PLAY_X,BUTTON_PLAY_Y }, BUTTON_W, BUTTON_H, app->getTexture(16), this, 0, app, CallBackLoad);
	this->addGameObject(butonLoad);
	this->addEventObject(butonLoad);
	butonPlay = nullptr;
	//Boton Exit
	MenuButton* butonExit = new MenuButton({ 450,400 }, { BUTTON_PLAY_X,BUTTON_PLAY_Y }, BUTTON_W, BUTTON_H, app->getTexture(19), this, 0, app, CallBackExit);
	this->addGameObject(butonExit);
	this->addEventObject(butonExit);
	butonPlay = nullptr;
}