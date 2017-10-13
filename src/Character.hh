#pragma once

#include "Logic.hh"

class Character {
public:
	Character(Logic& selfLogic, Logic& enemyLogic)
	: selfLogic_(selfLogic), enemyLogic_(enemyLogic) {}
	virtual ~Character() {}
	virtual void doSpecial()=0;
protected:
	Logic& selfLogic_;
	Logic& enemyLogic_;
};

class BetaCharacter : public Character {
public:
	BetaCharacter(Logic& selfLogic, Logic& enemyLogic)
	: Character(selfLogic, enemyLogic) {};
	void doSpecial() override { selfLogic_.clearMana(); }
};
