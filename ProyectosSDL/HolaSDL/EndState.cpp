#include "EndState.h"
#include "SDLApplication.h"


EndState::EndState(GameStateMachine* _gsm, SDLApplication* _app) : GameState(_gsm, _app) {
	background = app->getTexture(21);
}