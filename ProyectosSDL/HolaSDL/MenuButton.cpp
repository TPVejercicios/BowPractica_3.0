#include "MenuButton.h"
#include "SDLApplication.h"


MenuButton::MenuButton(Vector2D _dir, Point2D _pos, int _h, int _w, Texture* _texture, GameState* _owner, int _id, SDLApplication* _app, CallBackOnClick* _cbOnClick)//,CallBackOnClick* _cbOnClick)
	: SDLGameObject(_dir, _pos, _h, _w, _texture, _owner, _id){
	app = _app;
	cbOnClick = _cbOnClick;
}

MenuButton::~MenuButton() {

}

void MenuButton::handleEvent(const SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p = { event.button.x, event.button.y };
		SDL_Rect* r = new SDL_Rect();
		r->x = this->pos.getX();
		r->y = this->pos.getY();
		r->h = this->height;
		r->w = this->width;
		if (SDL_PointInRect(&p, r) == SDL_TRUE) {
			cout << "boton clickado" << endl;
			cbOnClick(app);
		}
		r = nullptr;
	}
}

void CallBackPlay(SDLApplication* app) {
	app->Play();
}

void CallBackLoad(SDLApplication* app) {
	app->Load();
}

void CallBackSave(SDLApplication* app) {
	app->Save();
}

void CallBackMenu(SDLApplication* app) {
	app->Menu();
}

void CallBackExit(SDLApplication* app) {
	app->Exit();
}

void CallBackCont(SDLApplication* app) {
	app->Cont();
}


void CallBackPause(SDLApplication* app) {
	app->Pause();
}




