#pragma once
#include <iostream>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include <string>

using namespace std;
class GameState;
class GameStateMachine;

//Constantes para game
const uint WIN_WIDTH = 800;							//Anchura del juego
const uint WIN_HEIGHT = 600;						//Altura del juego
const uint NUM_TEXTURES = 29;						//Num de texturas
const uint FRAME_RATE = 30;


//Estructura que ayuda a organizar la carga de texturas
struct image
{
	string filename;
	uint colls, rows;
};


class SDLApplication
{
private: 
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStateMachine = nullptr;
	Texture* textures[NUM_TEXTURES];
	bool exit = false;
	int currFrameBallon = 0;
public:
	SDLApplication();
	~SDLApplication();
	void run();
	void loadTextures();
	Texture* getTexture(int index);
	void Play();
	void Menu();
	void Load();
	void Exit();
	void Save();
	void Cont();
	void endState(int status);
	void Pause();
	void setBallonFrame(int frame) { currFrameBallon = frame; };
	uint getWindowsW() { return WIN_WIDTH; }
	uint getWindowsH() { return WIN_HEIGHT; }
	SDL_Renderer* getRenderer() { return renderer; };
};

