#pragma once
#include "ControllerInterface.hh"
#include "KeyMap.hh"

class LocalController : public ControllerInterface
{
public:
	LocalController(std::shared_ptr<LogicInterface> logic, Character& character, KeyMap& keyMap) : ControllerInterface(logic, character), keyMap_(keyMap) {}
	void handleKey(const SDL_Keycode& key) override;
	void tick() override;
private:
	KeyMap keyMap_;
};
