#pragma once
#include "ControllerInterface.hh"

class LocalController : public ControllerInterface
{
public:
	LocalController(Logic& logic) : ControllerInterface(logic) {}
	void handleKey(const SDL_Keycode& key) override;
	void tick() override {}
};
