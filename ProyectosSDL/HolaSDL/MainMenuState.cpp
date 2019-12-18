#include "MainMenuState.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(GameStateMachine* _gsm, SDLApplication* _app):
	GameState(_gsm, _app)
{
	background = app->getTexture(22);//No sale el index no sé por que
	MenuButton* butonPlay = new MenuButton({ 300,400 }, { BUTTON_PLAY_X,BUTTON_PLAY_Y }, BUTTON_W, BUTTON_H, app->getTexture(15), this, 0);
	this->addGameObject(butonPlay);
	this->addEventObject(butonPlay);
	butonPlay = nullptr;
}