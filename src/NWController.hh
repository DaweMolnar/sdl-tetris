#pragma once

#include "ControllerInterface.hh"
#include "Client.hh"
#include "KeyMap.hh"
#include <chrono>

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
	void updateTetromino(size_t pos1, size_t pos2, size_t row, size_t col, const std::string& shape);
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

	const std::chrono::duration<double> tableSendDelay_ = std::chrono::milliseconds(600) ;
	std::chrono::time_point<std::chrono::system_clock> lastTableSent_ = std::chrono::time_point<std::chrono::system_clock>::min();
	KeyMap keyMap_;
	std::shared_ptr<TcpClient> client_;
	std::shared_ptr<LogicInterface> clientLogic_;
};
