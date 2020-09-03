#pragma once
#include "checkML.h"

class GameObject
{
public:
	virtual ~GameObject() {};
	virtual void update() = 0;
	virtual void render() = 0;
};

