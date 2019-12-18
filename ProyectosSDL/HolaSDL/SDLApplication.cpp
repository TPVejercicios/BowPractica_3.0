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
	uint frame_time = 0, start_time = SDL_GetTicks();
	while (!exit) {
		frame_time = SDL_GetTicks() - start_time;
		gameStateMachine->currentState()->handleEvents();	//Reacciona a los eventos del estado actual
		if (frame_time >= FRAME_RATE) {
			cout << "actualiza frame" << endl;
			gameStateMachine->currentState()->update();			//Actualiza los Objetos del estado actual
			SDL_RenderClear(renderer);							//Limpia el renderer
			gameStateMachine->currentState()->render();			//Actualiza el renderer
			SDL_RenderPresent(renderer);						//Muestra el renderer por pantalla
			start_time = SDL_GetTicks();
		}
	}
	cout << "App cerrada" << endl;
}

void SDLApplication::Play() {
	gameStateMachine->loadGameState();
}
