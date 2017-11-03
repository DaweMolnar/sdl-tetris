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
	enemyLogic_.addPlusLine();
}

void
Ninja::skillMedium()
{
	Logic::TetrisTable self = selfLogic_.getTable();
	Logic::TetrisTable enemy = enemyLogic_.getTable();
	selfLogic_.changeTable(enemy);
	enemyLogic_.changeTable(self);
}

void
Ninja::skillHigh()
{
	selfLogic_.clearTable();
}

void
Warrior::skillLow()
{
	selfLogic_.removeTopLines(4);
}

void
Warrior::skillMedium()
{
	Logic::TetrisTable self = selfLogic_.getTable();
	Logic::TetrisTable enemy = enemyLogic_.getTable();
	selfLogic_.changeTable(enemy);
	enemyLogic_.changeTable(self);
}

void
Warrior::skillHigh()
{
	selfLogic_.clearTable();
}

void
Mage::skillLow()
{
	for (int i = 0; i < 4; i++) selfLogic_.removeLine();
}

void
Mage::skillMedium()
{
	Logic::TetrisTable self = selfLogic_.getTable();
	Logic::TetrisTable enemy = enemyLogic_.getTable();
	selfLogic_.changeTable(enemy);
	enemyLogic_.changeTable(self);
}

void
Mage::skillHigh()
{
	selfLogic_.clearTable();
}
