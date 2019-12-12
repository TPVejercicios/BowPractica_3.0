#pragma once
#include "SDLGameObject.h"
#include "Vector2D.h"

class Game;
class Texture;

using Point2D = Vector2D;
using CallBackOnClick = void(Game* game);

class MenuButton : public SDLGameObject
{
private:

public:
	MenuButton(Texture* _texture, Vector2D _dir, Point2D _pos, int h, int w,GameState* _owner);
	~MenuButton();
	virtual void update() {};
	virtual void render() {};
	virtual void handleEvent() {};
	CallBackOnClick* action {};
};

