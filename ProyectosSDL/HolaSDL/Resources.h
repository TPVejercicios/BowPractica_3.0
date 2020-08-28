#pragma once
#include <string>	//Para la agregar la ruta de las imagenes
#include <vector>	//Para el vector de imagesInfo
#include "checkML.h"

using namespace std;

class Resources
{
public:
	
	//Enumerado con las texturas del juego
	enum TextureId : size_t
	{
		ArrowRight,
		ArrowUp,
		Background1,
		Background2,
		Background3,
		Background4,
		Background5,
		Background6,
		BackgroundEnd,
		BackgroundMenu,
		Ballons,
		ContinueButton,
		SaveButton,
		MenuButton,
		PauseButton,
		PlayButton,
		ResetButton,
		LoadedBow,
		DischargedBow,
		Bubble,
		Butterflies,
		Digits,
		Rewards,
		SavedButton,
		CloseButton,
		LoadButton,
		EndButterflie,
		EndBow,
		EndArrow,
	};

	//Struct para la gestión de imagenes
	struct ImageInfo {
		TextureId id;
		string fileName;
		int row;
		int colls;
	};

	//Vector con las rutas e ids
	static vector<ImageInfo> images_; 
};


