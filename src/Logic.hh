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

class LogicInterface
{
public:
	using TetrisTable = std::array<std::array<Color, TETRIS_ROW>, TETRIS_COL>;
	virtual ~LogicInterface() {}

	virtual void newGame() = 0;
	virtual void update() = 0;

	virtual void setEnemy(LogicInterface& enemy) = 0;

	virtual void removeLine() = 0;
	virtual void removeTopLines(size_t lines) = 0;
	virtual void clearTable() = 0;
	virtual void move(unsigned x, unsigned y) = 0;
	virtual void rotate() = 0;
	virtual void generateNewCurrentShape() = 0;

	virtual bool canMoveTo(const Shape& shape, const Position& nextPos) = 0;
	virtual bool pointIsEmpty(unsigned x, unsigned y) = 0;
	virtual bool finished() = 0;

	size_t gamesWon() { return gamesWon_; }
	size_t getMana() { return currentMana_; }
	void clearMana() { currentMana_ = 0; }
	void enemyClearedLine() { linesToAdd_++; }
	virtual void addPlusLine() = 0;

	void changeTable(TetrisTable& newTable) { resetCurrent(); landedTable_ = newTable; }

protected:
	virtual void resetCurrent() = 0;
	TetrisTable landedTable_;

	size_t linesToAdd_ = 0;
	size_t gamesWon_ = 0;
	size_t currentMana_ = 0;
};

class Logic : public LogicInterface
{
public:
	Logic();
	~Logic();

	Tetromino& getNextShape() { assert(nextShape_); return *nextShape_; }
	Tetromino& getCurrentShape() { assert(currentShape_); return *currentShape_; }
	TetrisTable getTableWithShape();
	TetrisTable getTable() { return landedTable_; }

	void newGame() override;
	void update() override;
	void move(unsigned x, unsigned y) override;
	bool finished() override;
	void rotate() override;
	void setEnemy(LogicInterface& enemy) override { enemy_ = &enemy; }

	void removeLine() override;
	void removeTopLines(size_t lines) override;
	void clearTable() override { clear(); }
	bool canMoveTo(const Shape& shape, const Position& nextPos) override;
	void generateNewCurrentShape() override { currentShape_ = std::make_unique<Tetromino>(); }
	void addPlusLine() override { linesToAdd_++; }

	bool pointIsEmpty(unsigned x, unsigned y) override;
private:
	void clear();
	void landCurrent();
	void resetCurrent() override;
	void cleanFullLines();
	void cleanLine(size_t line);
	void clearStats();
	void addLine();

	std::unique_ptr<Tetromino> currentShape_;
	std::unique_ptr<Tetromino> nextShape_;
	bool gameFailed_ = false;
	LogicInterface* enemy_ = nullptr;
};
