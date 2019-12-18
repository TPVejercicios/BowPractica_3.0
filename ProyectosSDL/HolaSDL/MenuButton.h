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

class MenuButton : public SDLGameObject, public EventHandler
{

public:
	MenuButton(Vector2D _dir, Point2D _pos, int h, int w, Texture* _texture, GameState* _owner, int _id);// , CallBackOnClick* _cbOnClick);
	~MenuButton();
	virtual void update() {};
	virtual void render() { texture->render({ pos.getX(), pos.getY(), width,height }, SDL_FLIP_NONE); };
	virtual void handleEvent(const SDL_Event event);
};

