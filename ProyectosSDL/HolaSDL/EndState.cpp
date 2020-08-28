#include "EndState.h"
#include "SDLApplication.h"	//Para pedir texturas
#include "GameState.h"		//Para pushear los objetos a la lista de gameObjects
#include "MenuButton.h"		//Para crear los diferentes botones


EndState::EndState(GameStateMachine* _gsm, SDLApplication* _app, int _status) : GameState(_gsm, _app) {
	SDLGameObject* bg = new SDLGameObject(Vector2D(0, 0), Vector2D(0, 0), app->getWindowsH(), app->getWindowsW(),
		app->getTexture(Resources::TextureId::BackgroundEnd), this, -1, 0);
	gameObjects.push_back(bg);
	bg = nullptr;
	
	//Boton Menu
	MenuButton* menuButton = new MenuButton({ 350,420 }, { 100, 100 }, 100, 100, app->getTexture(Resources::TextureId::MenuButton),
		this, 0, app, CallBackMenu);
	gameObjects.push_back(menuButton);
	eventObjects.push_back(menuButton);
	menuButton = nullptr;

	double x = (app->getWindowsW() / 2) - 150;
	double y = (app->getWindowsH() / 3) - 150;
	SDLGameObject* endImage = new SDLGameObject(Vector2D(x, y), Vector2D(0, 0), 300, 300, nullptr, this, -1, 0);
		
	cout << "Fin " << _status << endl;
	switch (_status)
	{
	case 0:
		endImage->setTexture(app->getTexture(Resources::EndArrow));
		break;
	case 1:
		endImage->setTexture(app->getTexture(Resources::EndButterflie));
		break;
	case 2:
		endImage->setTexture(app->getTexture(Resources::EndBow));
		break;
	default:
		break;
	}
	gameObjects.push_back(endImage);
	endImage = nullptr;
}