#include "SDLApplication.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"
#include "Resources.h"

//Constructor del juego
SDLApplication::SDLApplication() {
	//Inicialización de SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Creación del window y el renderer
	window = SDL_CreateWindow("BOW3.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Comprobación de error
	if (window == nullptr || renderer == nullptr)
		throw domain_error("Error al cargar SDL");
	else
	{
		srand(time(NULL));	//Semilla aleatoria
		loadTextures();		//Carga de texturas
		gameStateMachine = new GameStateMachine(this);	//Inicia la app en el esta MainMenuState
	}
}	

//Destrucción de todas las texturas
SDLApplication::~SDLApplication() {
	//Borrado de texturas
	auto size = Resources::images_.size();
	for (int i = 0; i < size; i++) delete textures[i];

	//Borrado de la máquina de estados
	delete gameStateMachine;

	//Cerrar SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Carga las texturas en un vector
void SDLApplication::loadTextures() {
	for (int i = 0; i < Resources::images_.size(); i++) {
		textures[i] = new Texture(renderer, Resources::images_[i].fileName, 
			Resources::images_[i].row, Resources::images_[i].colls);
	}
}

//Devuelve la la textura en función de un indice
Texture* SDLApplication::getTexture(int index) {
	if (index > Resources::images_.size() || index < 0) {
		throw invalid_argument("El indice no corresponde a ninguna textura");
	}
	return textures[index];
}

//Bucle principal del juego
void SDLApplication::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {
		frameTime = SDL_GetTicks() - startTime;
		gameStateMachine->currentState()->handleEvents();	//Reacciona a los eventos del estado actual
		if (frameTime >= FRAME_RATE) {
			gameStateMachine->currentState()->update();			//Actualiza los Objetos del estado actual
			SDL_RenderClear(renderer);							//Limpia el renderer
			gameStateMachine->currentState()->render();			//Actualiza el renderer
			SDL_RenderPresent(renderer);						//Muestra el renderer por pantalla
			startTime = SDL_GetTicks();
		}
		gameStateMachine->deleteStates();
	}
	cout << "App cerrada" << endl;
}

void SDLApplication::Play() {
	gameStateMachine->loadPlayState();
}

void SDLApplication::Menu() {
	gameStateMachine->loadMenuState();
}

void SDLApplication::Load() {
	gameStateMachine->nextStateToPush(STATES::LoadState);	
	cout << "Cargar partida" << endl;
}

void SDLApplication::Save() {
	gameStateMachine->nextStateToPush(STATES::SaveState);
	cout << "Guardamos partida" << endl;
}

void SDLApplication::Exit() {
	exit = true;
}

void SDLApplication::Cont() {
	gameStateMachine->killStates(1);
}

void SDLApplication::endState(int status) {
	//	status
	//	0 = sin flechas
	//	1 = sin mariposas
	//	2 = has ganado
	gameStateMachine->loadEndState(status);
}

void SDLApplication::Pause() {
	gameStateMachine->loadPauseState(false);
}
