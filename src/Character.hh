#pragma once

#include "Logic.hh"

class Character {
public:
	Character(Logic& selfLogic, Logic& enemyLogic)
	: selfLogic_(selfLogic), enemyLogic_(enemyLogic) {}
	virtual ~Character() {}
	virtual void doSpecial()=0;
	virtual bool canDoSpecial()=0;
	virtual char* getAvatar()=0; 
protected:
	Logic& selfLogic_;
	Logic& enemyLogic_;
};

class BetaCharacter : public Character {
public:
	BetaCharacter(Logic& selfLogic, Logic& enemyLogic)
	: Character(selfLogic, enemyLogic) {};
	void doSpecial() override;
	char* getAvatar() override { return "img/betachar.png"; }
	bool canDoSpecial() override { return selfLogic_.getMana() > 2; }
};
