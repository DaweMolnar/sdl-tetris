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
	for (int i = 0; i < currentShape_->shape.size(); i++) {
		for (int j = 0; j < currentShape_->shape.at(i).size(); j++) {
			fullTable.at(j + currentShape_->topLeft.first).at(i + currentShape_->topLeft.second)
				= currentShape_->shape.at(i).at(j);
		}
	}
	return std::move(fullTable);
}
