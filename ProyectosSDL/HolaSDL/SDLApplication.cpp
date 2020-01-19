#include "SDLApplication.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

//Constructor del juego
SDLApplication::SDLApplication() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("BOW3.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw domain_error("Error al cargar SDL");
	else
	{
		srand(time(NULL));
		loadTextures();
		gameStateMachine = new GameStateMachine(this);
		
	}
}	

//Destrucción de todas las texturas
SDLApplication::~SDLApplication() {
	for (int i = 0; i < NUM_TEXTURES; i++) delete textures[i];
}

//Carga las texturas en un vector (couts for debug)
void SDLApplication::loadTextures() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer, PATHS[i].filename, PATHS[i].rows, PATHS[i].colls);
	}
}

//Devuelve la la textura en función de un indice
Texture* SDLApplication::getTexture(int index) {
	if (index <= NUM_TEXTURES) {
		return this->textures[index];
	}
	else
	{
		throw invalid_argument("El indice no corresponde a ninguna textura");
	}
}

//Bucle principal del juego
void SDLApplication::run() {
	uint frame_time = 0, start_time = SDL_GetTicks();
	while (!exit) {
		if (typeid(gameStateMachine->currentState()) == typeid(PauseState)) cout << "Pausado" << endl;
		frame_time = SDL_GetTicks() - start_time;
		gameStateMachine->currentState()->handleEvents();	//Reacciona a los eventos del estado actual
		if (frame_time >= FRAME_RATE) {
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
	PlayState* game = new PlayState(gameStateMachine, this);
	gameStateMachine->pushState(game);
	game = nullptr;
}

void SDLApplication::Menu() {
	gameStateMachine->popState();	//Se quita o el Pause/End
	gameStateMachine->popState();	//Se quita el Play
	//Debajo de estos 2 está el menu
}

void SDLApplication::Load() {
	cout << "Cargar partida" << endl;
}

void SDLApplication::Save() {
	cout << "Guardamos partida" << endl;
}

void SDLApplication::Exit() {
	exit = true;
}

void SDLApplication::Cont() {
	gameStateMachine->popState();	//Se quita el Pause
}

void SDLApplication::Pause() {
	//Se añade el estado de Pause
	cout << "Se PAUSA" << endl;
	PauseState* pause = new PauseState(gameStateMachine, this);
	gameStateMachine->pushState(pause);
	pause = nullptr;
}



/*PILA DE ESTADOS
	1. PAUSE O END
	2. GAME	
	3. MENU (siempre por debajo)
*/
