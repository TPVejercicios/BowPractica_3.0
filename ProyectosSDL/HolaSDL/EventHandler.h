#pragma once
#include "SDL.h"
#include "checkML.h"

class EventHandler
{
public:
virtual void handleEvent(const SDL_Event event) = 0;
};

//No tiene .cpp
