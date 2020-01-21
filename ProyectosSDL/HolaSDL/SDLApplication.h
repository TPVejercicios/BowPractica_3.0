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
const uint NUM_TEXTURES = 23;						//Num de texturas
const uint FRAME_RATE = 30;


//Estructura que ayuda a organizar la carga de texturas
struct image
{
	string filename;
	uint colls, rows;
};

//Array con las texturas y su número de columnas y filas para facilitar la carga
const image PATHS[] = { {"..\\images\\Arrow1.png", 1, 1}, {"..\\images\\Arrow2.png", 1, 1}, {"..\\images\\Background01.png", 1, 1}, {"..\\images\\Background02.png", 1, 1}, {"..\\images\\Background03.png", 1, 1},
{"..\\images\\Background04.png", 1, 1}, {"..\\images\\Background05.png", 1, 1}, {"..\\images\\Background06.png", 1, 1}, {"..\\images\\Ballons.png", 6, 7}, {"..\\images\\Bow1.png", 1, 1}, 
{"..\\images\\Bow2.png", 1, 1}, {"..\\images\\Bubble.png", 1, 1}, {"..\\images\\Butterfly.png", 10, 4}, {"..\\images\\Digits.png", 10, 1}, {"..\\images\\Rewards.png", 8, 10}, {"..\\images\\BotonPlay.png", 1, 1},
{"..\\images\\BotonGuardar.png", 8, 10}, {"..\\images\\BotonMenu.png", 8, 10}, {"..\\images\\BotonRestart.png", 8, 10}, {"..\\images\\BotonPausa.png", 8, 10}, {"..\\images\\BotonContinuar.png", 8, 10},
{"..\\images\\BackgroundEnd.png", 8, 10}, {"..\\images\\BackgroundMenu.png", 8, 10} };



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
	void Pause();
	void setBallonFrame(int frame) { currFrameBallon = frame; };
};

