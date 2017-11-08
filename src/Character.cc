#include "Character.hh"

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
	//TODO wind
	enemyLogic_.addPlusLine();
}

void
Ninja::skillMedium()
{
	//TODO move bottom 2
	Logic::TetrisTable self = selfLogic_.getTable();
	Logic::TetrisTable enemy = enemyLogic_.getTable();
	selfLogic_.changeTable(enemy);
	enemyLogic_.changeTable(self);
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
	int firstNonEmpty = 0;
	for (firstNonEmpty = 0 ; firstNonEmpty < enemy.size(); firstNonEmpty++) {
		if (std::find_if_not(enemy.at(firstNonEmpty).begin(), enemy.at(firstNonEmpty).end(), [](auto i) { return (i == Color::none); }) != enemy.at(firstNonEmpty).end()) break;
	}

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
