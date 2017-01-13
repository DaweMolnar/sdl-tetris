#pragma once
#include "Shape.hh"

class Tetroid
{
public:
	Tetroid();
	~Tetroid();
private:
	std::shared_ptr<Shape> shape_;
};

