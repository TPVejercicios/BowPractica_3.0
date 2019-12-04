#pragma once
#include <SDL.h>
#include "Texture.h"

class GameState;
class GameStateMachine;

const uint NUM_TEXTURES = 14;

class SDLApplication
{
private: 
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStateMachine = nullptr;
	//Texture[NUM_TEXTURES] textures;
	bool exit = false;
public:
	void run() {};
};

