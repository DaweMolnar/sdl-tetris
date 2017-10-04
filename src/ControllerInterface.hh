#pragma once

#include "Logic.hh"
#include <SDL.h>

class ControllerInterface {
public:
	ControllerInterface(Logic& logic) : logic_(logic) {}
	//TODO virtual destructor 
	virtual void handleKey(const SDL_Keycode& key) = 0;
	virtual void tick() = 0; //TODO maybe separate tick with timer inside
protected:
	Logic& logic_;
};
