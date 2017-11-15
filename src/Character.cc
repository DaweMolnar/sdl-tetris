#include "Character.hh"

static int
getFirstNonEmpty(Logic::TetrisTable table)
{
	size_t firstNonEmpty = 0;
	for (firstNonEmpty = 0 ; firstNonEmpty < table.size(); firstNonEmpty++) {
		if (std::find_if_not(table.at(firstNonEmpty).begin(), table.at(firstNonEmpty).end(), [](auto i) { return (i == Color::none); }) != table.at(firstNonEmpty).end()) break;
	}
	return firstNonEmpty;
}

void
Character::doSpecial() {
	size_t mana = selfLogic_.getMana();
	if (mana >= 3) {
		skillHigh();
	} else if (mana >= 2) {
		skillMedium();
	} else if (mana >= 1) {
		skillLow();
	} else {
		return;
	}
	selfLogic_.clearMana();
}


void
Ninja::skillLow()
{
	Logic::TetrisTable self = selfLogic_.getTable();
	int firstNonEmpty = getFirstNonEmpty(self);
	for (size_t i = firstNonEmpty; i < self.size(); i++) {
		for (int j = self.at(i).size() - 1; j >= 0; j--) {
			if (self.at(i).at(j) == Color::none) {
				int cellToSwitch = j;
				for (; cellToSwitch >= 0; cellToSwitch--) {
					if (self.at(i).at(cellToSwitch) != Color::none) break;
				}
				if (cellToSwitch < 0) break;
				self.at(i).at(j) = self.at(i).at(cellToSwitch);
				self.at(i).at(cellToSwitch) = Color::none;
			}
		}
	}
	selfLogic_.changeTable(self);
}

void
Ninja::skillMedium()
{
	for (int i = 0; i < 2; i++) selfLogic_.removeLine();
	for (int i = 0; i < 2; i++) enemyLogic_.addPlusLine();
}

void
Ninja::skillHigh()
{
	Logic::TetrisTable enemy = enemyLogic_.getTable();
	selfLogic_.changeTable(enemy);
}

void
Warrior::skillLow()
{
	selfLogic_.removeTopLines(4);
}

void
Warrior::skillMedium()
{
	for (int i = 0; i < 5; i++) enemyLogic_.addPlusLine();
}

void
Warrior::skillHigh()
{
	Logic::TetrisTable self = selfLogic_.getTable();
	Logic::TetrisTable enemy = enemyLogic_.getTable();
	selfLogic_.changeTable(enemy);
	enemyLogic_.changeTable(self);
}

void
Mage::skillLow()
{
	for (int i = 0; i < 4; i++) selfLogic_.removeLine();
}

void
Mage::skillMedium()
{
	selfLogic_.generateNewCurrentShape();
}

void
Mage::skillHigh()
{
	Logic::TetrisTable enemy = enemyLogic_.getTable();
	int firstNonEmpty = getFirstNonEmpty(enemy);
	for (size_t i = firstNonEmpty; i < enemy.size(); i++) {
		for (size_t j = 0; j < enemy.at(i).size(); j++) {
			if (enemy.at(i).at(j) == Color::none) {
				enemy.at(i).at(j) = Color::grey;
			} else {
				enemy.at(i).at(j) = Color::none;
			}
		}
	}
	enemyLogic_.changeTable(enemy);
}
