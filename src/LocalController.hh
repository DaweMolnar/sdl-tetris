#pragma once
#include "ControllerInterface.hh"

class LocalController : public ControllerInterface
{
public:
	LocalController(Logic& logic, Character& character) : ControllerInterface(logic, character) {}
	void handleKey(const SDL_Keycode& key) override;
	void tick() override {}
};
