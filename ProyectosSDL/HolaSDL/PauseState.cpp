#include "PauseState.h"
#include "SDLApplication.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"

PauseState::PauseState(GameStateMachine* _gsm, SDLApplication* _app) : GameState(_gsm, _app) {
	background = app->getTexture(19);
	//Boton Menu
	MenuButton* buton = new MenuButton({ 350,420 }, { 100, 100 }, 100, 100, app->getTexture(20), this, 0, app, CallBackCont);
	this->addGameObject(buton);
	this->addEventObject(buton);
	buton = nullptr;

	//Boton Menu
	MenuButton* butonMenu = new MenuButton({ 600,420 }, { 100, 100 }, 100, 100, app->getTexture(17), this, 0, app, CallBackMenu);
	this->addGameObject(butonMenu);
	this->addEventObject(butonMenu);
	butonMenu = nullptr;
}
