#include "MainMenuState.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"

MainMenuState::MainMenuState(GameStateMachine* _gsm,Texture* _bg, Texture* _buttonPlay):
	GameState(_gsm, _bg)
{
	MenuButton* butonPlay = new MenuButton(_buttonPlay, { 300,400 }, { BUTTON_PLAY_X,BUTTON_PLAY_Y }, BUTTON_W, BUTTON_H, this,PLAY, CallBackPlay);
	this->addGameObject(butonPlay);
	this->addEventObject(butonPlay);
	butonPlay = nullptr;
}