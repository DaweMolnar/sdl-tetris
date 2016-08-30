#include "Logic.hh"

Logic::Logic()
{
	currentShape_ = std::make_unique<Tetromino>();
	nextShape_ = std::make_unique<Tetromino>();
	clear();
}

Logic::~Logic()
{
}

void
Logic::clear()
{
	for (size_t i = 0; i < landedTable_.size(); i++) {
		for (size_t j = 0; j < landedTable_.at(i).size(); j++) {
			landedTable_[i][j] = Color::none;
		}
	}
}

Logic::TetrisTable
Logic::getTable()
{
	TetrisTable fullTable = landedTable_;
	for (size_t i = 0; i < currentShape_->shape.size(); i++) {
		for (size_t j = 0; j < currentShape_->shape.at(i).size(); j++) {
			if (currentShape_->shape.at(i).at(j) == Color::none) continue;
			fullTable.at(j + currentShape_->topLeft.first).at(i + currentShape_->topLeft.second)
				= currentShape_->shape.at(i).at(j);
		}
	}
	return std::move(fullTable);
}

bool
Logic::canMoveTo(const Position& nextPos)
{
	for (size_t i = 0; i < currentShape_->shape.size(); i++) {
		for (size_t j = 0; j < currentShape_->shape.at(i).size(); j++) {
			if (currentShape_->shape.at(i).at(j) == Color::none) continue;
			unsigned nextX = j + nextPos.first;
			unsigned nextY = i + nextPos.second;
			if (nextX >= landedTable_.size() || nextY >= landedTable_.at(j).size()) return false;
			if (landedTable_.at(nextX).at(nextY) != Color::none) {
				return false;
			}
		}
	}
	return true;
}

void
Logic::landCurrent()
{
	landedTable_ = getTable();
	std::swap(nextShape_, currentShape_);
	nextShape_ = std::make_unique<Tetromino>();
}

void
Logic::update()
{
	std::pair<unsigned, unsigned> nextPos_ = currentShape_->topLeft;
	nextPos_.second += 1;
	if (canMoveTo(nextPos_)) currentShape_->topLeft = nextPos_;
	else landCurrent();
}

void
Logic::move(unsigned x, unsigned y)
{
	std::pair<unsigned, unsigned> nextPos_ = currentShape_->topLeft;
	nextPos_.first += x;
	nextPos_.second += y;
	if (canMoveTo(nextPos_)) currentShape_->topLeft = nextPos_;
}
