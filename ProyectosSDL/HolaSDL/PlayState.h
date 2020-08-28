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
const double BALLON_H = 100;
const double BALLON_W = 100;

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
	//Flechas que quedan al jugador
	int remaingShoots = START_SHOOTS;
	//Número de mariposas que hay en el nivel
	int currButterfies = 0;
	//Puntos que lleva el jugador
	int currPoints = 0;
	//Escala de los globos
	int currScaleBallon = 1;
	//Bool que determina si e jugador se ha quedado son flechas
	bool outOfArrows = false;
	//Puntero al marcador
	ScoreBoard* SCB = nullptr;
	//Actual frame rate de los globos para crearlos
	double currFrameBallon = 0;
	//Tiempo del último globo creado
	double lastBallonCreated = 0;
	//Puntero al fondo del nivel
	SDLGameObject* background = nullptr;
	//Tiempo que llevan los globos escalados
	double scaledBallons = 0;
	//Tiempo que los globos van a estar sobre-escalados
	const double SCALED_BALLONS_TIME = 8500;
	//Booleando que determina si está activo el rewards de bigBallons
	bool scaleBallonActived = false;

	//Crea el arco
	void createBow();
	//Crea una mariposa en una posición aleatoria
	void createButterfly();
public:
	//Constructor por defecto
	PlayState(GameStateMachine* _gsm, SDLApplication* _app);
	//Constructor en función si ha guardado el juego o no
	PlayState(GameStateMachine* _gsm, SDLApplication* _app, bool loadStatus);
	//Se encarga de setear los valores del SCB cuando se carga el juego
	void changeSCB(int nivel, int puntos, int flechas, int butterflie_);
	~PlayState() { delete background; delete SCB; };

	//métodos para controlar el nivel
	void update() override;
	//Gestiona las colisiones entre las flechas y los demás elementos
	void checkCollision();

	//Métodos para construir un nivel
		//Agrega x mariposas al total de mariposas y las agrega a la escena
	void addButterflies(int _butterfliesToAdd);			
		//Carga el nivel actual
	void loadLevel();
		//Determina si se ha conseguido superar el actual nivel
	void nextLevel();
		//Crea el scoreboard
	void createSCB();
		//Crea un globo en una posición aleatoria
	void createBallon();
	
	void createBallon(int x_, int y_, int speed_);
		//Cargar un nivel
	void setLevel(int currLevel, int currPoints, int arrows, int _butterflies);

	//Métodos para las flechas
		//Crea una flecha
	void createArrow(Point2D _pos);
		//Determina si se puede crear una flecha
	bool canShoot() { return remaingShoots > 0 ? true : false; };
		//Método para agregar 100 flechas // para testeo
	void giveArrows() { remaingShoots += 100; };
		//Devuelve la cantidad de flechas que le quedan al arco
	int getRemainingShots() { return remaingShoots; };

	void removeButterfly() { currButterfies--; }
	

	//Métodos para destruir el nivel actual
	void deleteAllBallons();
	void deleteAllArrows();
	void deleteAllRewards();
	void deleteAllbutterflies();

	//Métodos para los rewards
	void createReward(Point2D _pos);
	void addArrows(int _arrowsToAdd) { remaingShoots += _arrowsToAdd; };
	void setBallonScale(int _newScale);

	void loadGameFromFile() {
		//T ob = new T(forward<T>(args)...);
		//gameObjects.push_back(ob);
	};

	void createButterfly(Vector2D pos_, Vector2D dir_);
	void setBow(int x_, int status_);
	void createArrow(int x_, int y_, int stacks_);
	inline int getButterfliesLeft() { return currButterfies; };
};