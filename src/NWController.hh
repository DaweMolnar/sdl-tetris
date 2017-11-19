#pragma once

#include "ControllerInterface.hh"
#include "Client.hh"
#include "KeyMap.hh"

class NWCController : public ControllerInterface
{
public:
	NWCController(std::shared_ptr<LogicInterface> logic, Character& character, std::shared_ptr<TcpClient> client)
	: ControllerInterface(logic, character)
	, client_(client)
	{}

	void handleKey(const SDL_Keycode&) override {}
	void tick() override;

private:
	void handleMessage(const std::string& message);
	std::shared_ptr<TcpClient> client_;
};

class NWSController : public ControllerInterface
{
public:
	NWSController(std::shared_ptr<LogicInterface> logic, Character& character, std::shared_ptr<TcpClient> client, KeyMap& keyMap)
	: ControllerInterface(logic, character)
	, keyMap_(keyMap)
	, client_(client)
	{}

	void handleKey(const SDL_Keycode&) override;
	void tick() override;

private:
	void sendMana();
	void sendGameOver();

	KeyMap keyMap_;
	std::shared_ptr<TcpClient> client_;
};
