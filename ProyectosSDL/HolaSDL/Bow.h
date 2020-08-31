#pragma once
#include <vector>
#include "SDLGameObject.h"
#include "EventHandler.h"
#include "SDLApplication.h"

using namespace std;

using Point2D = Vector2D;

const uint GAP = 31;						//Desfase gráfico que hay entre el arco cargado y el descargado
const uint BOW_1_W = 100;
const uint BOW_2_W = 41;
const uint PROPOR = 4;

class Bow : public SDLGameObject,public EventHandler{
private:
	//Variable que determina si el bow está cargado
	bool charged = true;			
public:
	Bow(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _texture, GameState* _owner, int _id,int _speed);
	//Mueve al arco
	void update()override;
	//Escucha los eventos que conciernen al arco
	void handleEvent(const SDL_Event event) override;
	void saveObject(ofstream& write) override;
	void changeBowStatus(int status);
};