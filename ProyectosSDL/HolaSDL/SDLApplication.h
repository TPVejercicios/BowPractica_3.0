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
public:
	SDLApplication();
	~SDLApplication();
	void run();
	void loadTextures();
	Texture* getTexture(int index) { return textures[index]; };
	//Indice de texturas
	enum indexTexturas
	{
		ARROW_1 = 0, ARROW_2 = 1, BG_1 = 2, BG_2 = 3, BG_3 = 4, BG_4 = 5, BG_5 = 6, BG_6 = 7, BALLONS = 8,
		BOW_1 = 9, BOW_2 = 10, BUBBLE = 11, BUTTERFLY = 12, DIGITS = 13, REWARDS = 14, BOTON_PLAY = 15, BOTON_GUARDAR = 16,
		BOTON_MENU = 17, BOTON_REINICIAR = 18, BOTON_PAUSA = 19, BOTON_REANUDAR = 20, BG_END = 21, BG_MENU = 22
	};
};

