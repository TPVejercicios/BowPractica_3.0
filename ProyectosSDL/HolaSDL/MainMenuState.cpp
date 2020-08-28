#include "MainMenuState.h"
#include "GameState.h"
#include "Texture.h"
#include <SDL.h>
#include "MenuButton.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(GameStateMachine* _gsm, SDLApplication* _app):
	GameState(_gsm, _app)
{
	SDLGameObject* bg = new SDLGameObject(Vector2D(0, 0), Vector2D(0, 0), app->getWindowsH(), app->getWindowsW(), 
		app->getTexture(Resources::TextureId::BackgroundMenu), this, -1, 0);
	gameObjects.push_back(bg);
	bg = nullptr;
	createPlayButton();
	createLoadButton();
	createExitButton();
}

void MainMenuState::createPlayButton() {

	Point2D buttonPos = Vector2D(BUTTON_W, app->getWindowsH()  - BUTTON_H * 2);
	MenuButton* butonPlay = new MenuButton(buttonPos, {0,0}, BUTTON_W, BUTTON_H,
		app->getTexture(Resources::TextureId::PlayButton), this, 0, app, CallBackPlay);
	gameObjects.push_back(butonPlay);
	eventObjects.push_back(butonPlay);
	butonPlay = nullptr;
}

void MainMenuState::createLoadButton() {
	Point2D buttonPos = Vector2D(app->getWindowsW() / 2 - (BUTTON_W / 2), app->getWindowsH() - BUTTON_H * 2);
	MenuButton* butonLoad = new MenuButton(buttonPos, { 0,0 }, BUTTON_W, BUTTON_H,
		app->getTexture(Resources::TextureId::LoadButton), this, 0, app, CallBackLoad);
	gameObjects.push_back(butonLoad);
	eventObjects.push_back(butonLoad);
	butonLoad = nullptr;
}

void MainMenuState::createExitButton() {
	Point2D buttonPos = Vector2D(app->getWindowsW() - (BUTTON_W * 2), app->getWindowsH() - BUTTON_H * 2);
	MenuButton* butonExit = new MenuButton(buttonPos, { 0,0 }, BUTTON_W, BUTTON_H,
		app->getTexture(Resources::TextureId::CloseButton), this, 0, app, CallBackExit);
	gameObjects.push_back(butonExit);
	eventObjects.push_back(butonExit);
	butonExit = nullptr;
}