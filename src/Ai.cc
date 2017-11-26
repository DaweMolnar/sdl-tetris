#include "Ai.hh"
#include <iostream>
#include <cassert>

int
Ai::getLogicScore(const Position pos, const Shape& shape)
const
{
	unsigned score = 0;
	for (size_t i = 0; i < shape.size(); i++) {
		for (size_t j = 0; j < shape.at(i).size(); j++) {
			if (shape.at(i).at(j) != Color::none) {
				int lineNeg = (TETRIS_COL - (pos.second + i));
				score += lineNeg;
				unsigned p = 1;
				while (logic_->pointIsEmpty(i+p, j)) {
					score += 1;
					p++;
				}
			}
		}
	}
	return score;
}

void
Ai::useSpecial()
{
	size_t dangerZone = 4;
	auto table = logic_->getTable();
	assert(dangerZone < table.size());
	for (size_t i = 0 ; i < dangerZone; i++) {
		if (std::find_if_not(table.at(i).begin(), table.at(i).end(), [](auto i) { return (i == Color::none); }) != table.at(i).end()) {
			character_.doSpecial();
		}
	}
}

void
Ai::tick()
{
	auto currentTime = std::chrono::system_clock::now();
	if (currentTime < lastMove_ + thinkTime_) return;
	lastMove_ = currentTime;
	useSpecial();
	auto originShape = logic_->getCurrentShape().shape;
	auto currentPos = logic_->getCurrentShape().topLeft;

	int minLogicScore = 999;
	Position wantedPos;
	int wantedRotation = 0;

	for (size_t i = 0; i < TETRIS_ROW; i++) {
		currentPos.first = i;
		auto shape = originShape;
		for (int rotation = 0; rotation < 4; rotation++) {
			currentPos.second = 0;
			if (!logic_->canMoveTo(shape, currentPos)) continue;
			for (size_t j = 0; j < TETRIS_COL; j++) {
				currentPos.second = j;
				if (!logic_->canMoveTo(shape, currentPos)) break;
				auto score = getLogicScore(currentPos, shape);
				if (minLogicScore > score) {
					minLogicScore = score;
					wantedPos = currentPos;
					wantedRotation = rotation;
					assert(wantedRotation >= 0);
				}
			}
			shape = rotate(shape);
		}
	}

	if (wantedRotation != 0) { logic_->rotate();}
	int move = wantedPos.first - logic_->getCurrentShape().topLeft.first;
	if (move != 0) logic_->move(move < 1 ? -1 : 1, 0);
	else logic_->move(0, 1);
}
