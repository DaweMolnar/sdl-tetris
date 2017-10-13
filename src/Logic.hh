#pragma once
#include "Shapes.hh"

#include <stdexcept>
#include <algorithm>
#include <memory>
#include <array>
#include <vector>
#include <cassert>

static const size_t TETRIS_ROW = 11;
static const size_t TETRIS_COL = 17;
static const size_t MANA_PROBABILITY = 20;

enum class Color {
	none = 0,
	red = 1,
	yellow = 2,
	green = 3,
	grey = 4,
	blue = 5,
	purple = 6,
	magic = 7
};

using Shape = std::vector<std::vector<Color>>;
using Position = std::pair<unsigned, unsigned>;

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
	case 7: return Color::magic;
	default: return Color::none;
	}
}

Shape rotate(const Shape& shape);

struct Tetromino {
	Shape shape;
	Position topLeft;
	Tetromino()
	{
		std::vector<std::vector<unsigned>>& randomShape = *shapeList.at(rand() % shapeList.size());
		Color randomColor = getColor(rand() % 5 + 1);
		for (unsigned i = 0; i < randomShape.size(); i++) {
			std::vector<Color> tmpShape;
			for (unsigned j = 0; j < randomShape.at(i).size(); j++) {
				int hasMagic = (rand() % MANA_PROBABILITY) == 0;
				tmpShape.push_back((randomShape[i][j] == 1) ? (hasMagic ? Color::magic : randomColor) : Color::none);
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
	using TetrisTable = std::array<std::array<Color, TETRIS_ROW>, TETRIS_COL>;

	Logic();
	~Logic();

	Tetromino& getNextShape() { assert(nextShape_); return *nextShape_; }
	Tetromino& getCurrentShape() { assert(currentShape_); return *currentShape_; }
	TetrisTable getTable();

	void newGame();
	void update();
	void move(unsigned x, unsigned y);
	bool finished();
	void rotate();

	size_t getScore() { return currentScore_; }
	size_t highScore() { return highScore_; }
	size_t getMana() { return currentMana_; }
	void clearMana() { currentMana_ = 0; }

	bool pointIsEmpty(unsigned x, unsigned y) {
		if (x >= landedTable_.size() || y >= landedTable_.at(0).size()) return false;
		return (landedTable_.at(x).at(y) == Color::none);
	}

	void setEnemy(Logic& enemy) { enemy_ = &enemy; }

	void addPlusLine();
	bool canMoveTo(const Shape& shape, const Position& nextPos);

private:

	void clear();
	void landCurrent();
	void cleanFullLines();
	void cleanLine(size_t line);

	std::unique_ptr<Tetromino> currentShape_;
	std::unique_ptr<Tetromino> nextShape_;
	TetrisTable landedTable_;
	size_t currentScore_ = 0;
	size_t highScore_ = 0;
	size_t currentMana_ = 0;
	Logic* enemy_ = nullptr;
};

