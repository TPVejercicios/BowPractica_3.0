#pragma once
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "EventHandler.h"

class Game;
class Texture;
using Point2D = Vector2D;
using CallBackOnClick = void(Game* game);

class MenuButton : public SDLGameObject, public EventHandler
{
private:
	int num = 0;
public:
	MenuButton(Texture* _texture, Vector2D _dir, Point2D _pos, int h, int w,GameState* _owner);
	~MenuButton();
	virtual void update() {};
	virtual void render() { texture->render({ pos.getX(), pos.getY(), width,height }, SDL_FLIP_NONE); };
	virtual void handleEvent(const SDL_Event event);

	CallBackOnClick* action {};
};

