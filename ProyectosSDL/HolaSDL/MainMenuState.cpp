#include "MainMenuState.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>

MainMenuState::MainMenuState(GameStateMachine* _gsm, Texture* _botonPlay):
	GameState(_gsm)
{
	_botonPlay->render({400,300,_botonPlay->getW() / 4,_botonPlay->getH() / 4}, SDL_FLIP_NONE);
}