#include "PlayState.h"
#include "SDLApplication.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"
//Antiguos ArrowGameObjects
#include "ScoreBoard.h"
#include "Bow.h"
#include "Arrow.h"
#include "Ballon.h"
#include "Butterfly.h"

//Inicializa la escena de PlayState
PlayState::PlayState(GameStateMachine* _gsm, SDLApplication* _app) : GameState(_gsm, _app) {
	loadLevel();
	createBow();
	createSCB();
	//Boton Menu
	MenuButton* butonPause = new MenuButton({ 700,0 }, { 0, 0 }, 100, 100, app->getTexture(BOTON_PAUSA), this, 0, app, CallBackPause);
	this->addGameObject(butonPause);
	this->addEventObject(butonPause);
	butonPause = nullptr;
}
//Crea el arco
void PlayState::createBow() {
	Point2D pos;
	pos.setX(START_BOW_POS_X);
	pos.setY(BOW_POS_Y);
	Vector2D dir;
	int angle = 0;
	Bow* bow = new Bow(pos, dir, BOW_H, BOW_W, app->getTexture(BOW_1), this, OBJECT_BOW, BOW_SPEED);
	gameObjects.push_back(bow);
	eventObjects.push_back(bow);
	bow = nullptr;
}

//Crea una flecha en una posición dada
void PlayState::createArrow(Point2D _pos) {
	remaingShoots--;
	Arrow* currArrow = new Arrow(_pos, { 1,0 }, ARROW_H, ARROW_W, app->getTexture(ARROW_1), this, OBJECT_ARROW, ARROW_SPEED);
	gameObjects.push_back(currArrow);
	arrows.push_back(currArrow);
	currArrow = nullptr;
	if (remaingShoots == 0) {
		outOfArrows = true;
	}
}

//Crea un globo en una posición aleatoria
void PlayState::createBallon() {
	Point2D _pos;
	_pos.setX(rand() % (MAX_X_BALLON - MIN_X_BALLON) + MIN_X_BALLON);
	_pos.setY(MIN_Y_BALLON);
	Vector2D _dir;
	_dir.setY(-1);
	int _speed = rand() % (BALLON_MAX_SPEED - BALLON_MIN_SPEED) + BALLON_MIN_SPEED;
	Ballon* currBallon = new Ballon(_pos, _dir, BALLON_H, BALLON_W, app->getTexture(BALLONS), this, OBJECT_BALLON, _speed);
	currBallon->setScale(currScaleBallon);
	gameObjects.push_back(currBallon);
	currBallon = nullptr;
}

//Crea las mariposas en función de currLevel
void PlayState::createButterfly() {
	Point2D _pos;
	_pos.setX(rand() % (BUTT_MAX_X - BUTT_MIN_X) + BUTT_MIN_X);
	_pos.setY(rand() % WIN_HEIGHT - 50);
	Vector2D _dir;
	_dir.setX(rand() % -2 + 1);
	_dir.setY(rand() % -2 + 1);
	Butterfly* currButterfly = new Butterfly(_pos, _dir, BUTTERFLY_H, BUTTERFLY_W, app->getTexture(BUTTERFLY), this, OBJECT_BUTTERFLY, BUT_SPEED);
	gameObjects.push_back(currButterfly);
	currButterfly = nullptr;
}

//Carga el nivel en función de currLevel
void PlayState::loadLevel() {
	background = app->getTexture(LEVELS[currLevel].currTex);
	app->setBallonFrame(LEVELS[currLevel].frame_ballon);
	currButterfies = LEVELS[currLevel].butterflyNum;
	remaingShoots += LEVELS[currLevel].arrows;
	for (int i = 0; i < LEVELS[currLevel].butterflyNum; i++) {
		createButterfly();
	}
	//createScoreBoard();
}

//Comprueba si el jugador ha perdido el juego 
bool PlayState::endGame() {
	if (currButterfies == 0) {
		cout << "Has matado todas las mariposas " << endl;
		return  true;
	}
	else if (arrows.empty() && remaingShoots == 0 && outOfArrows && arrows.size() <= 1) {
		cout << "Te has quedado sin flechas" << endl;
		return  true;
	}
	else return false;
}

//Manda a destruir todas las butterflies que estan en escena
void PlayState::deleteAllbutterflies() {
	if (currButterfies > 0) {
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			auto aux = dynamic_cast<Butterfly*>(*it);
			if (aux != nullptr && !aux->isDeleting()) {
				killObject(aux);
			}
			aux = nullptr;
		}
	}
}

//Manda a destruir todos los eventos que se hayan quedado en la escena
void PlayState::deleteAllRewards() {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		auto aux = dynamic_cast<Reward*>(*it);
		if (aux != nullptr && !aux->isDeleting()) {
			killObject(aux);
		}
	}
}

//Manda a eleminar todas las flechas que pudieron quedarse en la escena
void PlayState::deleteAllArrows() {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		auto aux = dynamic_cast<Arrow*>(*it);
		if (aux != nullptr && !aux->isDeleting()) {
			killObject(aux);
		}
	}
}

//Manda a destruir todas los ballons que estan en escena
void PlayState::deleteAllBallons() {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		auto aux = dynamic_cast<Ballon*>(*it);
		if (aux != nullptr && !aux->isDeleting()) {
			killObject(aux);
		}
	}
}

//Determina si el jugador gana el actual nivel y reinicia los elementos de la escena
void PlayState::nextLevel() {
	if (currLevel < MAX_LEVELS && currPoints >= LEVELS[currLevel].pointsToReach) {
		currLevel++;
		setBallonScale(1);
		//killObject(SCB);
		deleteAllbutterflies();
		deleteAllBallons();
		deleteAllArrows();
		deleteAllRewards();
		loadLevel();
	}
}

//Multiplica los puntos por cada globo que una flecha haya destruido y añade puntos extra
void PlayState::stackArrows(int _stacks) {
	currPoints += pow(_stacks - 1, BONUS_POINTS) + POINTS_TO_ADD * _stacks;
	static_cast<ScoreBoard*>(SCB)->updatePoints(currPoints);
}

//Comprueba las colisiones entre las flechas y los elementos "colisionbles"
void PlayState::checkCollision() {
	for (auto arrowIT = arrows.begin(); arrowIT != arrows.end(); ++arrowIT) {
		for (auto gameObIT = gameObjects.begin(); gameObIT != gameObjects.end(); ++gameObIT) {
			auto* currGO = dynamic_cast<SDLGameObject*>(*gameObIT);
			SDL_Rect rc = (*arrowIT)->getRectForCollision();
			if (currGO != nullptr && currGO->isCollisionable() && SDL_HasIntersection(&currGO->getRect(), &rc))
			{
				switch (currGO->getId())
				{
				case OBJECT_BALLON:
					(*arrowIT)->addStack();
					break;
				case OBJECT_BUTTERFLY:
					if (currPoints - POINTS_TO_SUB < 0) currPoints = 0;			//Nunca se obtiene una puntuación negativa
					else currPoints -= POINTS_TO_SUB;
					currButterfies--;
					//SCB->updatePoints(currPoints);
					break;
				case OBJECT_REWARD:
					static_cast<Reward*>(currGO)->setState(1);
				default:
					break;
				}
				nextLevel();
				currGO->startDestruction();
			}
		}
	}
}

//Agrega un numero determinado de mariposas a la escena
void PlayState::addButterflies(int _butterfliesToAdd) {
	currButterfies += _butterfliesToAdd;
	for (int i = 0; i < _butterfliesToAdd; i++) {
		createButterfly();
	}
}

//Crea un premio en una posición dada
void PlayState::createReward(Point2D _pos) {
	int rnd = rand() % MAX_REWARDS;
	Reward* currReward = nullptr;
	switch (rnd)
	{
	case 0:
		currReward = new AddArrows(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(BUBBLE), this, OBJECT_REWARD, REWARD_SPEED, app->getTexture(REWARDS));
		break;
	case 1:
		currReward = new RemoveArrows(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(BUBBLE), this, OBJECT_REWARD, REWARD_SPEED, app->getTexture(REWARDS));
		break;
	case 2:
		currReward = new ReviveButterflies(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(BUBBLE), this, OBJECT_REWARD, REWARD_SPEED, app->getTexture(REWARDS));
		break;
	case 3:
		currReward = new BigBallons(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(BUBBLE), this, OBJECT_REWARD, REWARD_SPEED, app->getTexture(REWARDS));
		break;
	default:
		break;
	}
	if (currReward != nullptr) {
		gameObjects.push_back(currReward);
		eventObjects.push_back(currReward);
		currReward = nullptr;
	}
}

//Crea al score board y lo asigna a un puntero para su posterior uso
void PlayState::createSCB() {
	ScoreBoard* scoreBoard = new ScoreBoard(app->getTexture(DIGITS), app->getTexture(ARROW_2), currPoints, remaingShoots, this);
	if (scoreBoard != nullptr) {
		SCB = scoreBoard;
		gameObjects.push_back(scoreBoard);
	}
	else
	{
		throw domain_error("El scoreBoard no se ha podido crear");
	}
}


