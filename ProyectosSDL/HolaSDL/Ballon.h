#pragma once
#include "SDLGameObject.h"
#include "Texture.h"

const int MAX_ROW = 6;

enum class  status : int
{
	SWOLLEN, PUNCTURED
};


class Ballon :public SDLGameObject
{
private:
	//El actual estado del globo, se inicializa con inflado
	status currStatus = status::SWOLLEN;
	//Fila del globo para renderizar 
	int row = 0;
	//Columna del globo para renderizar
	int col = 0;
	//Límite del globo en y que es igual a menos la altura del globo
	double topLimit = 0;
public:
	//Constructor
	Ballon(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed) 
		:SDLGameObject(_pos, _dir, _h, _w, _texture, _owner, _id, _speed) {
		row = rand() % MAX_ROW;
		topLimit = -_h;
	};
	void render() override { texture->renderFrame(getRect(), row, col, SDL_FLIP_NONE); };
	//Se encarga de gestionar los diferentes estados del globo y determinar si el globo llega al límite en y para destruirlo
	void update() override;
	//Comienza la destrucción del globo de forma externa, cuando una flecha colisiona contra el globo
	void startDestruction() override;
	//Cambia la escala del globo
	void setScale(int _newScale) { width *= _newScale; height *= _newScale; };
	void saveObject(ofstream& write)override;
};

