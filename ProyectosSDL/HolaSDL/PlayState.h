#pragma once
#include "GameState.h"
#include "Vector2D.h"
#include "Reward.h"


class MenuButton;
class ScoreBoard;

using uint = unsigned int;
using Point2D = Vector2D;

//Constantes para los diferentes objectos de la escena
#pragma region CONST
//Constantes para la creación de bow
const uint START_BOW_POS_X = 0;
const uint BOW_POS_Y = 0;
const uint BOW_H = 100;
const uint BOW_W = 100;
const uint BOW_SCALE = 1;
const int BOW_SPEED = 20;

//Constantes para generar el boton de pause
const uint BUTTON_POS_X = 400;
const uint BUTTON_POS_Y = 400;

//Constantes para la creación de una flecha
const uint ARROW_H = 20;
const uint ARROW_W = 100;
const uint ARROW_SPEED = 50;
const int START_SHOOTS = 10;

//Constantes para la creación de globos
const uint MIN_X_BALLON = 200;
const uint MAX_X_BALLON = 600;
const uint MIN_Y_BALLON = 700;
const uint BALLON_MAX_SPEED = 18;
const uint BALLON_MIN_SPEED = 5;
const uint BALLON_H = 100;
const uint BALLON_W = 100;

//Constantes para la creación de una mariposa
const uint BUTTERFLY_H = 96;
const uint BUTTERFLY_W = 93;
const uint BUTT_MIN_X = 150;
const uint BUTT_MAX_X = 750;
const uint BUTT_MAX_Y = 550;
const uint BUT_SPEED = 2;

//Constantes para los puntos
const int POINTS_TO_ADD = 10;
const int BONUS_POINTS = 2;
const int POINTS_TO_SUB = 15;

//Constantes para rewards 
const uint REWARD_H = 50;
const uint REWARD_W = 50;
const uint REWARD_SPEED = 1;
const int MAX_REWARDS = 4;

#pragma endregion

class PlayState : public GameState
{
private:
	int remaingShoots = START_SHOOTS;
	int currButterfies = 0;
	int currLevel = 0;
	int currPoints = 0;
	int currScaleBallon = 1;
	bool outOfArrows = false;
	ScoreBoard* SCB = nullptr;
	void createBow();
	void createButterfly();
public:
	//El cambio de nivel lo debe desencadenar el metodo update
	PlayState(GameStateMachine* _gsm, SDLApplication* _app);
	~PlayState() { SCB = nullptr; };

	void checkCollision();

	void createArrow(Point2D _pos);
	void createBallon();
	void createSCB();

	bool canShoot() { return remaingShoots > 0 ? true : false; };
	void giveArrows() { remaingShoots += 100; };//Para probar flechas
	void loadLevel();
	bool endGame();
	void nextLevel();
	void deleteAllBallons();
	void deleteAllArrows();
	void deleteAllRewards();
	void deleteAllbutterflies();
	void stackArrows(int stack);
	int getRemainingShots() { return remaingShoots; };

	//Métodos para los rewards
	void createReward(Point2D _pos);
	void addArrows(int _arrowsToAdd) { remaingShoots += _arrowsToAdd; };
	void addButterflies(int _butterfliesToAdd);							
	void setBallonScale(int _newScale) { currScaleBallon = _newScale; };
};