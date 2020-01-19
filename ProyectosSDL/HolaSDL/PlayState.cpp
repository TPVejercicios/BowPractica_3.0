#include "PlayState.h"
#include "SDLApplication.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"
//Antiguos ArrowGameObjects
#include "Bow.h"
#include "Arrow.h"
#include "Ballon.h"
#include "Butterfly.h"

//Inicializa la escena de PlayState
PlayState::PlayState(GameStateMachine* _gsm, SDLApplication* _app) : GameState(_gsm, _app) {
	background = app->getTexture(2);
	createBow();
	//Boton Menu
	MenuButton* butonPause = new MenuButton({ 700,0 }, { 0, 0 }, 100, 100, app->getTexture(app->BOTON_PAUSA), this, 0, app, CallBackPause);
	this->addGameObject(butonPause);
	this->addEventObject(butonPause);
	butonPause = nullptr;
	//Para probar
	for (int i = 0; i < 10; i++) {
		createBallon();
		createButterfly();
	}
}

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

void PlayState::createBallon() {
	Point2D _pos;
	_pos.setX(rand() % (MAX_X_BALLON - MIN_X_BALLON) + MIN_X_BALLON);
	_pos.setY(MIN_Y_BALLON);
	Vector2D _dir;
	_dir.setY(-1);
	int _speed = rand() % (BALLON_MAX_SPEED - BALLON_MIN_SPEED) + BALLON_MIN_SPEED;
	Ballon* currBallon = new Ballon(_pos, _dir, BALLON_H, BALLON_W, app->getTexture(app->BALLONS), this, OBJECT_BALLON, _speed);
	gameObjects.push_back(currBallon);
	currBallon = nullptr;
}

void PlayState::createButterfly() {
	Point2D _pos;
	_pos.setX(rand() % (BUTT_MAX_X - BUTT_MIN_X) + BUTT_MIN_X);
	_pos.setY(rand() % WIN_HEIGHT);
	Vector2D _dir;
	_dir.setX(rand() % -2 + 1);
	_dir.setY(rand() % -2 + 1);
	Butterfly* currButterfly = new Butterfly(_pos, _dir, BUTTERFLY_H, BUTTERFLY_W, app->getTexture(app->BUTTERFLY), this, OBJECT_BUTTERFLY, BUT_SPEED);
	gameObjects.push_back(currButterfly);
	currButterfly = nullptr;
}
