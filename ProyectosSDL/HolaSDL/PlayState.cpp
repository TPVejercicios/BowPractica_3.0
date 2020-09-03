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
	//Cargamos el fondo 
	background = new SDLGameObject(Vector2D(0, 0), Vector2D(0, 0), WIN_HEIGHT, WIN_WIDTH, 
		nullptr, this, -1, 0);
	gameObjects.push_back(background);
	createSCB();
	loadLevel();
	createBow();
	MenuButton* butonPause = new MenuButton({ 700,0 }, { 0, 0 }, 100, 100, app->getTexture(Resources::TextureId::PauseButton),
		this, -1, app, CallBackPause);
	this->addGameObject(butonPause);
	this->addEventObject(butonPause);
	butonPause = nullptr;
}

//Constructor del playstate especifico para cargar el juego
PlayState::PlayState(GameStateMachine* _gsm, SDLApplication* _app, bool loadStatus) : GameState(_gsm, _app) {
	background = new SDLGameObject(Vector2D(0, 0), Vector2D(0, 0), WIN_HEIGHT, WIN_WIDTH,
		nullptr, this, -1, 0);
	gameObjects.push_back(background);
	createSCB();
}

void PlayState::changeSCB(int level_, int points_, int arrows_,int butterflie_) {
	setLevel(level_, points_, arrows_, butterflie_);
	//SCB->setSCB(nivel, puntos, flechas);
}

//Carga el nivel en función de currLevel
void PlayState::loadLevel() {
	//Asignamos una textura en función del nivel actual
	background->setTexture(app->getTexture(currLevel + 2));
	//Cargamos en la app la velocidad de movimiento de los globos
	app->setBallonFrame((int)LEVELS[currLevel].frame_ballon);
	//Cargamos el número de mariposas a crear en función del actual nivel
	currButterfies = LEVELS[currLevel].butterflyNum;
	//Cargamos la cantidad de flechas disponiles en función del nivel en que estamos
	remaingShoots += LEVELS[currLevel].arrows;
	//Creamos las mariposas
	currFrameBallon = LEVELS[currLevel].frame_ballon;
	for (int i = 0; i < LEVELS[currLevel].butterflyNum; i++) {
		createButterfly();
	}
}

//Crea el arco
void PlayState::createBow() {
	Point2D pos = Vector2D(0 , WIN_HEIGHT / 2);
	int id = Resources::TextureId::LoadedBow;
	Bow* bow = new Bow(pos, { 0,0 }, BOW_H, BOW_W, app->getTexture(id), this, id, BOW_SPEED);
	gameObjects.push_back(bow);
	eventObjects.push_back(bow);
	bow = nullptr;
}

//Crea una flecha en una posición dada
void PlayState::createArrow(Point2D _pos) {
	remaingShoots--;
	int id = (int)Resources::TextureId::ArrowRight;
	//Velocidad en la propia clase arrow? TODO
	Arrow* currArrow = new Arrow(_pos, { 1,0 }, ARROW_H, ARROW_W, app->getTexture(id), this, id, ARROW_SPEED);
	gameObjects.push_back(currArrow);
	arrows.push_back(currArrow);
	currArrow = nullptr;
	if (remaingShoots <= 0) {
		outOfArrows = true;
	}
}

//Crea un globo en una posición aleatoria
void PlayState::createBallon() {
	Point2D _pos;
	_pos.setX(rand() % (MAX_X_BALLON - MIN_X_BALLON) + MIN_X_BALLON);
	_pos.setY(MIN_Y_BALLON);
	int _speed = rand() % (BALLON_MAX_SPEED - BALLON_MIN_SPEED) + BALLON_MIN_SPEED;
	int id = (int)Resources::TextureId::Ballons;
	Ballon* currBallon = new Ballon(_pos, {0,-1}, (int)BALLON_H, (int)BALLON_W, app->getTexture(id), this, id, _speed);
	currBallon->setScale(currScaleBallon);
	gameObjects.push_back(currBallon);
	currBallon = nullptr;
}

//Crea un globo en una posición y velocidad determinadas
void PlayState::createBallon(int x_, int y_, int speed_)
{
	int id = (int)Resources::TextureId::Ballons;
	Ballon* currBallon = new Ballon({ (double)x_,(double)y_ }, { (double)0,(double)-1 },
		(int)BALLON_H, (int)BALLON_W, app->getTexture(id), this, id, speed_);
	currBallon->setScale(currScaleBallon);
	gameObjects.push_back(currBallon);
	currBallon = nullptr;
}

void PlayState::setLevel(int _currLevel, int _currPoints, int _arrows, int _butterflies)
{
	currLevel = _currLevel;
	currPoints = _currPoints;
	remaingShoots = _arrows;
	background->setTexture(app->getTexture(currLevel + 2));
	app->setBallonFrame((int)LEVELS[currLevel].frame_ballon);
	currFrameBallon = LEVELS[currLevel].frame_ballon;
	MenuButton* butonPause = new MenuButton({ 700,0 }, { 0, 0 }, 100, 100, app->getTexture(Resources::TextureId::PauseButton),
		this, -1, app, CallBackPause);
	this->addGameObject(butonPause);
	this->addEventObject(butonPause);
	butonPause = nullptr;
	SCB->updateArrows(remaingShoots);
	SCB->updatePoints(currPoints);
}

//Crea las mariposas en función de currLevel
void PlayState::createButterfly() {

	Point2D _pos;
	_pos.setX(rand() % (BUTT_MAX_X - BUTT_MIN_X) + BUTT_MIN_X);
	_pos.setY(rand() % (WIN_HEIGHT - 50));
	Vector2D _dir;
	_dir.setX(rand() % -2 + 1);
	_dir.setY(rand() % -2 + 1);
	//cout << "MARIPOSA POS: {" << _pos.getX() << ", " << _pos.getY() << "} DIR: {" << _dir.getX() << ", " << _dir.getY() << "}" << endl;
	int id = (int)Resources::TextureId::Butterflies;
	Butterfly* currButterfly = new Butterfly(_pos, _dir, BUTTERFLY_H, BUTTERFLY_W, app->getTexture(id),
		this, id, BUT_SPEED);
	gameObjects.push_back(currButterfly);
	currButterfly = nullptr;
}

//Update
void PlayState::update()
{
	GameState::update();
	checkCollision();
	//cout << "FLECHAS RESTANTES: " << remaingShoots << endl;

	if (SDL_GetTicks() - lastBallonCreated  > currFrameBallon) {
		lastBallonCreated = SDL_GetTicks();
		createBallon();
	}
	if (arrows.empty() && outOfArrows) {
		cout << "Te has quedado sin flechas" << endl;
		app->endState(0);
	}
	if (scaleBallonActived && SDL_GetTicks() - scaledBallons > SCALED_BALLONS_TIME) {
		scaledBallons = SDL_GetTicks();
		currScaleBallon = 1;
		scaleBallonActived = false;
		cout << "cambio de escala \n";
	}
	if (currButterfies <= 0) {
		app->endState(1);
	}
}

void PlayState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type != SDL_QUIT) {
			for (auto eventIT = eventObjects.begin(); eventIT != eventObjects.end(); ++eventIT) {
				auto* aux = dynamic_cast<EventHandler*>(*eventIT);
				(aux)->handleEvent(event);
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)app->Exit();

			//CHEATS para testeo
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_0) {
					addArrows(5);
					cout << "Activa truco addArrows" << endl;
				}
				if (event.key.keysym.sym == SDLK_1) {
					addArrows(-2);
					cout << "Activa truco removeArrows" << endl;
				}
				if (event.key.keysym.sym == SDLK_2) {
					addButterflies(2);
					cout << "Activa truco ReviveButterflies" << endl;
				}
				if (event.key.keysym.sym == SDLK_3) {
					setBallonScale(2);
					cout << "Activa truco bigBallons" << endl;
				}
			}
		}
	}
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
		//Pasamos al siguiente nivel
		currLevel++;
		//Devolvemos los globos a la escala normal
		setBallonScale(1);
		//Eliminamos las mariposas que hayan quedado en escena
		deleteAllbutterflies();
		//Eliminamos los globos que hayan quedado en escena
		deleteAllBallons();
		//Eliminamos las flechas que hayan quedado en escena
		deleteAllArrows();
		//Eliminamos las premios que hayan quedado en escena
		deleteAllRewards();
		//Cargamos el siguiente nivel
		loadLevel();
	}
	//Gameover
	else if (currLevel > MAX_LEVELS) {
		app->endState(2);
	}
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
				case Resources::TextureId::Ballons:
					(*arrowIT)->addStack();
					currPoints += pow((*arrowIT)->getStacks() - 1, BONUS_POINTS) + (POINTS_TO_ADD * (*arrowIT)->getStacks());
					SCB->updatePoints(currPoints);
					break;
				case Resources::TextureId::Butterflies:
					if (currPoints - POINTS_TO_SUB < 0) currPoints = 0;			//Nunca se obtiene una puntuación negativa
					else currPoints -= POINTS_TO_SUB;
					break;
				case Resources::TextureId::Rewards:
					//state 0 es dentro de la burbuja y 1 fuera
					if (static_cast<Reward*>(currGO)->getState() == 0) static_cast<Reward*>(currGO)->setState(1);
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
		currReward = new AddArrows(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(Resources::TextureId::Bubble),
			this, Resources::TextureId::Rewards, REWARD_SPEED, app->getTexture(Resources::TextureId::Rewards));
		break;
	case 1:
		currReward = new RemoveArrows(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(Resources::TextureId::Bubble),
			this, Resources::TextureId::Rewards, REWARD_SPEED, app->getTexture(Resources::TextureId::Rewards));
		break;
	case 2:
		currReward = new ReviveButterflies(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(Resources::TextureId::Bubble),
			this, Resources::TextureId::Rewards, REWARD_SPEED, app->getTexture(Resources::TextureId::Rewards));
		break;
	case 3:
		currReward = new BigBallons(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(Resources::TextureId::Bubble),
			this, Resources::TextureId::Rewards, REWARD_SPEED, app->getTexture(Resources::TextureId::Rewards));
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

void PlayState::createKnowReward(Point2D _pos, int _kind, int _state)
{
	Reward* currReward = nullptr;
	switch (_kind)
	{
	case 0:
		currReward = new AddArrows(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(Resources::TextureId::Bubble),
			this, Resources::TextureId::Rewards, REWARD_SPEED, app->getTexture(Resources::TextureId::Rewards), _state);
		break;
	case 1:
		currReward = new RemoveArrows(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(Resources::TextureId::Bubble),
			this, Resources::TextureId::Rewards, REWARD_SPEED, app->getTexture(Resources::TextureId::Rewards), _state);
		break;
	case 2:
		currReward = new ReviveButterflies(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(Resources::TextureId::Bubble),
			this, Resources::TextureId::Rewards, REWARD_SPEED, app->getTexture(Resources::TextureId::Rewards), _state);
		break;
	case 3:
		currReward = new BigBallons(_pos, { 0,1 }, REWARD_H, REWARD_W, app->getTexture(Resources::TextureId::Bubble),
			this, Resources::TextureId::Rewards, REWARD_SPEED, app->getTexture(Resources::TextureId::Rewards), _state);
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

void PlayState::addArrows(int _arrowsToAdd)
{
	remaingShoots += _arrowsToAdd;
	//if (remaingShoots <= 0) outOfArrows = true;
}

//Cambia la escala de los globos
void PlayState::setBallonScale(int _newScale)
{
	scaleBallonActived = true;
	currScaleBallon = _newScale;
	scaledBallons = SDL_GetTicks();
}

//Métodos para cargar el juego
//Crea un mariposa en una posición determinada
void PlayState::createButterfly(Vector2D pos_, Vector2D dir_)
{
	currButterfies++;
	int id = (int)Resources::TextureId::Butterflies;
	Butterfly* currButterfly = new Butterfly(pos_, dir_, BUTTERFLY_H, BUTTERFLY_W, app->getTexture(id),
		this, id, BUT_SPEED);
	gameObjects.push_back(currButterfly);
	currButterfly = nullptr;
}

//Crea el arco
void PlayState::setBow(int x_, int status_)
{
	Point2D pos = Vector2D(0, (double)x_);
	int id = Resources::TextureId::LoadedBow;
	Bow* bow = new Bow(pos, { 0,0 }, BOW_H, BOW_W, app->getTexture(id), this, id, BOW_SPEED);
	bow->changeBowStatus(status_);
	gameObjects.push_back(bow);
	eventObjects.push_back(bow);
	bow = nullptr;
}

//Crea una flecha
void PlayState::createArrow(int x_, int y_, int stacks_)
{
	int id = (int)Resources::TextureId::ArrowRight;
	Arrow* currArrow = new Arrow({(double)x_,(double)y_},
		{ 1,0 }, ARROW_H, ARROW_W, app->getTexture(id), this, id, ARROW_SPEED);
	currArrow->addStack(stacks_);
	gameObjects.push_back(currArrow);
	arrows.push_back(currArrow);
	currArrow = nullptr;
}

//Crea al score board y lo asigna a un puntero para su posterior uso
void PlayState::createSCB() {
	ScoreBoard* scoreBoard = new ScoreBoard(app->getTexture(Resources::TextureId::Digits), 
		app->getTexture(Resources::TextureId::ArrowUp), currPoints, remaingShoots, this);
	if (scoreBoard != nullptr) {
		SCB = scoreBoard;
		gameObjects.push_back(scoreBoard);
	}
	else
	{
		throw domain_error("El scoreBoard no se ha podido crear");
	}
	scoreBoard = nullptr;
}