#pragma once
#include "Logic.hh"
#include <SDL.h>

class Ai
{
public:
	Ai(Logic& logic);
	~Ai();
	void makeNextMove() const { logic_.move(0, 1); }
private:
	Logic& logic_;
};

