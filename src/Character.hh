#pragma once

#include "Logic.hh"
#include <string>

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

class Ninja : public Character {
public:
	Ninja(Logic& selfLogic, Logic& enemyLogic)
	: Character(selfLogic, enemyLogic) {};
	char const* getAvatar() override { return "img/ninjachar.png"; }

private:
	void skillLow() override;
	void skillMedium() override;
	void skillHigh() override;
	std::array<std::string, 3> getSpecials() override { return {{"1 Wind","2 Shove","3 Copy"}}; }
};

class Mage : public Character {
public:
	Mage(Logic& selfLogic, Logic& enemyLogic)
	: Character(selfLogic, enemyLogic) {};
	char const* getAvatar() override { return "img/magechar.png"; }

private:
	void skillLow() override;
	void skillMedium() override;
	void skillHigh() override;
	std::array<std::string, 3> getSpecials() override { return {{"1 Erase","2 Transform","3 Mirror"}}; }
};

class Warrior : public Character {
public:
	Warrior(Logic& selfLogic, Logic& enemyLogic)
	: Character(selfLogic, enemyLogic) {};
	char const* getAvatar() override { return "img/warriorchar.png"; }

private:
	void skillLow() override;
	void skillMedium() override;
	void skillHigh() override;
	std::array<std::string, 3> getSpecials() override { return {{"1 Slice","2 Raise","3 Swap"}}; }
};
