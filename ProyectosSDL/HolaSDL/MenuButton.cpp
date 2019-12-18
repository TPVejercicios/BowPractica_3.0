#include "MenuButton.h"



MenuButton::MenuButton(Texture* _texture, Vector2D _dir, Point2D _pos, int _h, int _w, GameState* _owner)
	: SDLGameObject(_texture, _dir, _pos, _h, _w, _owner) , EventHandler()
{
	

}

MenuButton::~MenuButton() {

}

void MenuButton::handleEvent(const SDL_Event event) {

}

