#pragma once

#include "Logic.hh"

class Character {
public:
	Character(Logic& selfLogic, Logic& enemyLogic)
	: selfLogic_(selfLogic), enemyLogic_(enemyLogic) {}
	virtual ~Character() {}
	
	void doSpecial();
	
	virtual std::array<std::string, 3> getSpecials()=0;
	virtual char const* getAvatar()=0; 
protected:
	virtual void skillLow()=0;
	virtual void skillMedium()=0;
	virtual void skillHigh()=0;

	Logic& selfLogic_;
	Logic& enemyLogic_;
};

class BetaCharacter : public Character {
public:
	BetaCharacter(Logic& selfLogic, Logic& enemyLogic)
	: Character(selfLogic, enemyLogic) {};
	char const* getAvatar() override { return "img/betachar.png"; }

private:
	void skillLow() override;
	void skillMedium() override;
	void skillHigh() override;
	std::array<std::string, 3> getSpecials() override;
};
