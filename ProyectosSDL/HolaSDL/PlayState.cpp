#include "PlayState.h"
#include "SDLApplication.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"
//Antiguos ArrowGameObjects
#include "Bow.h"
#include "Arrow.h"

//Inicializa la escena de PlayState
PlayState::PlayState(GameStateMachine* _gsm, SDLApplication* _app) : GameState(_gsm, _app) {
	background = app->getTexture(2);
	createBow();
	//Boton Menu
	MenuButton* butonPause = new MenuButton({ 700,0 }, { 0, 0 }, 100, 100, app->getTexture(app->BOTON_PAUSA), this, 0, app, CallBackPause);
	this->addGameObject(butonPause);
	this->addEventObject(butonPause);
	butonPause = nullptr;
}

//Crea el bow
void PlayState::createBow() {
	Point2D pos;
	pos.setX(START_BOW_POS_X);
	pos.setY(BOW_POS_Y);
	Vector2D dir;
	int angle = 0;
	Bow* bow = new Bow(pos, dir, BOW_H, BOW_W, app->getTexture(app->BOW_1), this, OBJECT_BOW, BOW_SPEED);
	gameObjects.push_back(bow);
	eventObjects.push_back(bow);
	bow = nullptr;
}

void PlayState::createArrow(int x, int y) {
	remaingShoots--;
	Arrow* currArrow = new Arrow({ x,y }, { 1,0 }, ARROW_H, ARROW_W, app->getTexture(app->ARROW_1), this, OBJECT_ARROW, ARROW_SPEED);
	gameObjects.push_back(currArrow);
	currArrow = nullptr;
}
