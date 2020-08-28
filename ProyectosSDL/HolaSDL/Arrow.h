#pragma once
#include "SDLGameObject.h"
#include "PlayState.h"
#include "SDLApplication.h"

#pragma region CONSTANTES
const int H_FOR_COLLISION = 5;
const int W_FOR_COLLISION = 50;
const int GAP_COll = 55;
#pragma endregion


class Arrow: public SDLGameObject
{
private:
	//L�mite en x de las fechas = al tama�o del juego en x m�s el tama�o de la fecha
	int arrowLimit = 0;
	//Cantidad de globos que destruye �sta flecha
	int stack = 0;
public:
	Arrow(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id, int _speed) 
		:SDLGameObject(_pos, _dir, _h, _w, _texture, _owner, _id,_speed) {
		arrowLimit = _owner->getApp()->getWindowsW() + _w;
	};
	//Mueve a la flecha y determina cuando la fecha sale del juego por el eje x
	void update() override;
	//Agrega un stack a la flecha al destruir un globo
	inline void addStack() { stack++; };
	inline void addStack(int number) { stack = number; };
	//Devuelve el n�mero de globos que �sta flecha a destruido
	inline int getStacks() { return stack; }
	//Devuelve el rect para gestionar la colisi�n
	inline SDL_Rect getRectForCollision() const {
		return SDL_Rect({ (int)pos.getX() + GAP_COll,(int)pos.getY(),W_FOR_COLLISION,H_FOR_COLLISION });
	}

	void saveObject(ofstream& write) override;
};

