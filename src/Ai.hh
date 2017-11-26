#pragma once
#include "Logic.hh"
#include "ControllerInterface.hh"
#include <SDL.h>
#include <chrono>

class Ai : public ControllerInterface
{
public:
	Ai(std::shared_ptr<LogicInterface> logic, Character& character) : ControllerInterface(logic, character) {}
	void tick() override;
	void handleKey(const SDL_Keycode&) override {}
private:
	void useSpecial();
	int getLogicScore(const Position pos, const Shape& shape) const;
	const std::chrono::duration<double> thinkTime_ = std::chrono::milliseconds(50) ;
	std::chrono::time_point<std::chrono::system_clock> lastMove_ = std::chrono::time_point<std::chrono::system_clock>::min();
};

