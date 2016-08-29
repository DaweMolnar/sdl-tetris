#pragma once
#include "Shapes.hh"

#include <stdexcept>
#include <memory>
#include <array>
#include <vector>
#include <cassert>

static const size_t TETRIS_ROW = 10;
static const size_t TETRIS_COL = 16;

enum class Color {
	none = 0,
	red = 1
};

struct Tetromino {
	std::vector<std::vector<Color>> shape;
	std::pair<unsigned, unsigned> topLeft;
	Tetromino()
	{
		std::vector<std::vector<unsigned>>& randomShape = *shapeList.at(0);
		Color randomColor = Color::red;
		//TODO random
		for (unsigned i = 0; i < randomShape.size(); i++) {
			std::vector<Color> tmpShape;
			for (unsigned j = 0; j < randomShape.at(i).size(); j++) {
				tmpShape.push_back((randomShape[i][j] == 1) ? randomColor : Color::none);
			}
			shape.push_back(tmpShape);
		}
		if (shape.size() <= 0) throw std::invalid_argument("Invalid shape");
		unsigned startCol = (TETRIS_COL / 2) - (shape.at(0).size() / 2);
		assert(startCol > 0 && startCol < TETRIS_COL);
		topLeft = std::make_pair(0u, startCol);
	}
};

class Logic
{
public:
	using TetrisTable = std::array<std::array<Color, TETRIS_COL>, TETRIS_ROW>;
	Logic();
	~Logic();
	Tetromino& getNextShape() { assert(currentShape_); return *nextShape_; }
	TetrisTable getTable();
private:
	void clear();
	std::unique_ptr<Tetromino> currentShape_;
	std::unique_ptr<Tetromino> nextShape_;
	TetrisTable landedTable_;
};

