#pragma once
#include "Shapes.hh"

#include <stdexcept>
#include <memory>
#include <array>
#include <vector>
#include <cassert>

static const size_t TETRIS_ROW = 11;
static const size_t TETRIS_COL = 17;

enum class Color {
	none = 0,
	red = 1,
	yellow = 2,
	green = 3,
	grey = 4,
	blue = 5,
	purple = 6
};

static Color
getColor(unsigned color) {
	switch (color) {
	case 0: return Color::none;
	case 1: return Color::red;
	case 2: return Color::yellow;
	case 3: return Color::green;
	case 4: return Color::grey;
	case 5: return Color::blue;
	case 6: return Color::purple;
	default: return Color::none;
	}
}

struct Tetromino {
	std::vector<std::vector<Color>> shape;
	std::pair<unsigned, unsigned> topLeft;
	Tetromino()
	{
		std::vector<std::vector<unsigned>>& randomShape = *shapeList.at(rand() % shapeList.size());
		Color randomColor = getColor(rand() % 5 + 1);
		for (unsigned i = 0; i < randomShape.size(); i++) {
			std::vector<Color> tmpShape;
			for (unsigned j = 0; j < randomShape.at(i).size(); j++) {
				tmpShape.push_back((randomShape[i][j] == 1) ? randomColor : Color::none);
			}
			shape.push_back(tmpShape);
		}
		if (shape.size() <= 0) throw std::invalid_argument("Invalid shape");
		unsigned startRow = (TETRIS_ROW / 2) - (shape.at(0).size() / 2);
		assert(startRow > 0 && startRow < TETRIS_ROW);
		topLeft = std::make_pair(startRow, 0u);
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

