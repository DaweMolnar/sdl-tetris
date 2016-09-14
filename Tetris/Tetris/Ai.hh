#pragma once
#include "Logic.hh"
#include <SDL.h>

class Ai
{
public:
	Ai(Logic& logic);
	~Ai();
	int getLogicScore(const Position pos, const Shape& shape) const;
	void makeNextMove() const;
private:
	Logic& logic_;
};

