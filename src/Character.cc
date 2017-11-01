#include "Character.hh"
#include <string>

void
Character::doSpecial() {
	size_t mana = selfLogic_.getMana();
	if (mana >= 9) {
		skillHigh();
	} else if (mana >= 6) {
		skillMedium();
	} else if (mana >= 3) {
		skillLow();
	} else {
		return;
	}
	selfLogic_.clearMana();
}

void
BetaCharacter::skillLow()
{
	enemyLogic_.addPlusLine();
}

void
BetaCharacter::skillMedium()
{
	Logic::TetrisTable self = selfLogic_.getTable();
	Logic::TetrisTable enemy = enemyLogic_.getTable();
	selfLogic_.changeTable(enemy);
	enemyLogic_.changeTable(self);
}

void
BetaCharacter::skillHigh()
{
	selfLogic_.clearTable();
}

std::array<std::string, 3>
BetaCharacter::getSpecials()
{
	return {{"1 Wind","2 Shove","3 Copy"}};
}
