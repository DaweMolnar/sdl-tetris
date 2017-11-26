#pragma once

#include "ControllerInterface.hh"
#include "Client.hh"
#include "KeyMap.hh"

class NWCController : public ControllerInterface
{
public:
	NWCController(std::shared_ptr<LogicInterface> logic, std::shared_ptr<LogicInterface> otherLogic, Character& character, std::shared_ptr<TcpClient> client)
	: ControllerInterface(logic, character)
	, client_(client)
	, serverLogic_(otherLogic)
	{}

	void handleKey(const SDL_Keycode&) override {}
	void tick() override;

private:
	void handleMessage(const std::string& message);
	void updateTable(const std::string& table);
	std::shared_ptr<TcpClient> client_;
	std::shared_ptr<LogicInterface> serverLogic_;
};

class NWSController : public ControllerInterface
{
public:
	NWSController(std::shared_ptr<LogicInterface> logic, std::shared_ptr<LogicInterface> otherLogic, Character& character, std::shared_ptr<TcpClient> client, KeyMap& keyMap)
	: ControllerInterface(logic, character)
	, keyMap_(keyMap)
	, client_(client)
	, clientLogic_(otherLogic)
	{}

	void handleKey(const SDL_Keycode&) override;
	void tick() override;

private:
	void sendMana();
	void sendLinesToAdd();
	void sendGameOver();
	void sendTetromino();
	void sendSpecial();
	void sendTable();

	const time_t tableSendDelay_ = 1/100;
	time_t lastTableSent_ = 0;
	KeyMap keyMap_;
	std::shared_ptr<TcpClient> client_;
	std::shared_ptr<LogicInterface> clientLogic_;
};
