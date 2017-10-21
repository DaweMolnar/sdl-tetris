#include "Character.hh"

void
BetaCharacter::doSpecial() {
	//selfLogic_.clearTable();
	Logic::TetrisTable self = selfLogic_.getTable();
	Logic::TetrisTable enemy = enemyLogic_.getTable();
	selfLogic_.changeTable(enemy);
	enemyLogic_.changeTable(self);
	if (canDoSpecial()) {
		selfLogic_.clearMana();
	}
}
