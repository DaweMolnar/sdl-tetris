#pragma once

#include "Logic.hh"
#include "Character.hh"
#include <SDL.h>

class ControllerInterface {
public:
	ControllerInterface(Logic& logic, Character& character) : logic_(logic), character_(character) {}
	virtual ~ControllerInterface() {}
	virtual void handleKey(const SDL_Keycode& key) = 0;
	virtual void tick() = 0; //TODO maybe separate tick with timer inside
protected: //TODO make private and add interface function for needed logic functions
	Logic& logic_;
	Character& character_;
};
