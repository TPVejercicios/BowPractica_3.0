#include "SDLApplication.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

SDLApplication::SDLApplication() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Practica2", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else
	{
		srand(time(NULL));
		loadTextures();
		gameStateMachine = new GameStateMachine(this);
		
	}
}	

SDLApplication::~SDLApplication() {
	for (int i = 0; i < NUM_TEXTURES; i++) delete textures[i];
}

//Carga las texturas en un vector (couts for debug)
void SDLApplication::loadTextures() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer, PATHS[i].filename, PATHS[i].rows, PATHS[i].colls);
	}
}

//Bucle del juego
void SDLApplication::run() {
	while (!exit) {
		gameStateMachine->currentState()->update();
		gameStateMachine->currentState()->render();
		SDL_RenderPresent(renderer);
		gameStateMachine->currentState()->handleEvents();
	}
}

void SDLApplication::Play() {
	gameStateMachine->loadGameState();
}
