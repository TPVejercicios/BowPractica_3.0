#include "PlayState.h"
#include "SDLApplication.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"
//Antiguos ArrowGameObjects
#include "Bow.h"


PlayState::PlayState(GameStateMachine* _gsm, SDLApplication* _app) : GameState(_gsm, _app) {
	background = app->getTexture(2);
	CreateBow();
	//Boton Menu
	MenuButton* butonPause = new MenuButton({ 700,0 }, { 100, 100 }, 100, 100, app->getTexture(19), this, 0, app, CallBackPause);
	this->addGameObject(butonPause);
	this->addEventObject(butonPause);
	butonPause = nullptr;
}

void PlayState::CreateBow() {
	Point2D pos;
	pos.setX(START_BOW_POS_X);
	pos.setY(BOW_POS_Y);
	Vector2D dir;
	int angle = 0;
	Bow* bow = new Bow(pos, dir, BOW_H, BOW_W, app->getTexture(9), this, OBJECT_BOW);
	gameObjects.push_back(bow);
	eventObjects.push_back(bow);
	bow = nullptr;
}