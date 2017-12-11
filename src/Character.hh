#pragma once

#include "Logic.hh"
#include <string>

class Character {
public:
	Character(std::shared_ptr<LogicInterface> selfLogic, std::shared_ptr<LogicInterface> enemyLogic)
	: selfLogic_(selfLogic), enemyLogic_(enemyLogic) {}
	virtual ~Character() {}
	
	void doSpecial();
	
	virtual std::array<std::string, 3> getSpecials()=0;
	virtual char const* getAvatar()=0; 
protected:
	virtual void skillLow()=0;
	virtual void skillMedium()=0;
	virtual void skillHigh()=0;

	std::shared_ptr<LogicInterface> selfLogic_;
	std::shared_ptr<LogicInterface> enemyLogic_;
};

class Ninja : public Character {
public:
	Ninja(std::shared_ptr<LogicInterface> selfLogic, std::shared_ptr<LogicInterface> enemyLogic)
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
	Mage(std::shared_ptr<LogicInterface> selfLogic, std::shared_ptr<LogicInterface> enemyLogic)
	: Character(selfLogic, enemyLogic) {};
	char const* getAvatar() override { return "img/magechar.png"; }

private:
	void skillLow() override;
	void skillMedium() override;
	void skillHigh() override;
	std::array<std::string, 3> getSpecials() override { return {{"1 Erase","2 Convert","3 Mirror"}}; }
};

class Warrior : public Character {
public:
	Warrior(std::shared_ptr<LogicInterface> selfLogic, std::shared_ptr<LogicInterface> enemyLogic)
	: Character(selfLogic, enemyLogic) {};
	char const* getAvatar() override { return "img/warriorchar.png"; }

private:
	void skillLow() override;
	void skillMedium() override;
	void skillHigh() override;
	std::array<std::string, 3> getSpecials() override { return {{"1 Slice","2 Raise","3 Swap"}}; }
};
