#pragma once
#include <vector>
#include "SDLGameObject.h"
#include "EventHandler.h"
#include "SDLApplication.h"

using namespace std;

using Point2D = Vector2D;

const uint GAP = 31;						//Desfase gráfico que hay entre el arco cargado y el descargado
const uint PROPOR = 4;

class Bow : public SDLGameObject,public EventHandler{
private:
	bool charged = true;			//Variable que determina si el bow está cargado
public:
	Bow(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id,int _speed);
	virtual void update();
	virtual void handleEvent(const SDL_Event event);
	//virtual void saveToFile(string &data);
};