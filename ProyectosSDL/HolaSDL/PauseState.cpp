#include "PauseState.h"
#include "SDLApplication.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"

PauseState::PauseState(GameStateMachine* _gsm, SDLApplication* _app, bool status) : GameState(_gsm, _app) {
	//Fondo de la pausa
	SDLGameObject* bg = new SDLGameObject(Vector2D(0, 0), Vector2D(0, 0), app->getWindowsH(), app->getWindowsW(),
		app->getTexture(currLevel + 2), this, -1, 0);
	gameObjects.push_back(bg);
	bg = nullptr;

	//Botón de volver
	Point2D resetButtonPos = Vector2D( W_BUTTON , app->getWindowsH() - (H_BUTTON * 2));
	MenuButton* resetButton = new MenuButton(resetButtonPos, { 0,0 }, W_BUTTON, H_BUTTON,
		app->getTexture(Resources::TextureId::ResetButton), this, 0, app, CallBackCont);
	gameObjects.push_back(resetButton);
	eventObjects.push_back(resetButton);
	resetButton = nullptr;

	//Boton Menu
	Point2D menuButtonPos = Vector2D(app->getWindowsW() / 2 - (W_BUTTON / 2 ), app->getWindowsH() - (H_BUTTON * 2));
	MenuButton* menuButton = new MenuButton(menuButtonPos, { 0, 0 }, W_BUTTON, H_BUTTON,
		app->getTexture(Resources::TextureId::MenuButton), this, 0, app, CallBackMenu);
	gameObjects.push_back(menuButton);
	eventObjects.push_back(menuButton);
	menuButton = nullptr;

	//Boton guardar
	Point2D saveButtonPos = Vector2D(app->getWindowsW() - (W_BUTTON * 2), app->getWindowsH() - (H_BUTTON * 2));
	MenuButton* saveButton = new MenuButton(saveButtonPos, { 0, 0 }, W_BUTTON, H_BUTTON,
		app->getTexture(Resources::TextureId::SaveButton), this, 0, app, CallBackSave);
	if (status) {
		saveButton->setTexture(app->getTexture(Resources::SavedButton));
	}
	gameObjects.push_back(saveButton);
	eventObjects.push_back(saveButton);
	saveButton = nullptr;
}

