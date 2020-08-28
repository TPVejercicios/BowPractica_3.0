#pragma once
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "EventHandler.h"
#include "GameState.h"

class SDLApplication;
class Texture;
using Point2D = Vector2D;

using CallBackOnClick = void(SDLApplication* app);

void CallBackPlay(SDLApplication* app);
void CallBackLoad(SDLApplication* app);
void CallBackSave(SDLApplication* app);
void CallBackMenu(SDLApplication* app);
void CallBackExit(SDLApplication* app);
void CallBackCont(SDLApplication* app);
void CallBackPause(SDLApplication* app);

class MenuButton : public SDLGameObject, public EventHandler
{
	CallBackOnClick* cbOnClick = nullptr;
	SDLApplication* app;
public:
	MenuButton(Vector2D _dir, Point2D _pos, int h, int w, Texture* _texture, GameState* _owner, int _id, SDLApplication* _app, CallBackOnClick* _cbOnClick);// , CallBackOnClick* _cbOnClick);
	~MenuButton();
	virtual void update() {};
	virtual void render() override {
		texture->render(SDL_Rect({ (int)pos.getX(), (int)pos.getY(), (int)width,(int)height }), SDL_FLIP_NONE);
	};
	virtual void handleEvent(const SDL_Event event);
};

