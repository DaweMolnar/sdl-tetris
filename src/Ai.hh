#pragma once
#include "Logic.hh"
#include "ControllerInterface.hh"
#include <SDL.h>

class Ai : public ControllerInterface
{
public:
	Ai(Logic& logic);
	~Ai();
	void tick() override;
	void handleKey(const SDL_Keycode&) override {}
private:
	int getLogicScore(const Position pos, const Shape& shape) const;
};

