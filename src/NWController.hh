#pragma once

#include "ControllerInterface.hh"
#include "Client.hh"

class NWCController : public ControllerInterface
{
public:
	NWCController(Logic& logic, Character& character, std::shared_ptr<TcpClient> client)
	: ControllerInterface(logic, character)
	, client_(client)
	{}

	void handleKey(const SDL_Keycode& key) override {}
	void tick() override {}

private:
	std::shared_ptr<TcpClient> client_;
};

class NWSController : public ControllerInterface
{
public:
	NWSController(Logic& logic, Character& character, std::shared_ptr<TcpClient> client)
	: ControllerInterface(logic, character)
	, client_(client)
	{}

	void handleKey(const SDL_Keycode& key) override {}
	void tick() override {}

private:
	std::shared_ptr<TcpClient> client_;
};
