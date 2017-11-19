#include "GameLoop.hh"
#include "View.hh"
#include "Character.hh"
#include "Client.hh"

#include <exception>
#include <iostream>
#include <time.h>
#include <tclap/CmdLine.h>

std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(std::move(item));
  }
  return elems;
}

std::shared_ptr<Character>
makeCharacter(char type, std::shared_ptr<LogicInterface> self, std::shared_ptr<LogicInterface> enemy)
{
	switch(type) {
		case 'n':
			return std::make_shared<Ninja>(self,enemy);
		case 'm':
			return std::make_shared<Mage>(self,enemy);
		case 'w':
			return std::make_shared<Warrior>(self,enemy);
		default:
			throw std::runtime_error("Given character type is not valid");
	}
}

char
getNWCharacter(std::shared_ptr<TcpClient> client)
{
	std::string message = client->receive(5);
	if (message.empty()) throw std::runtime_error("Enemy character did not received in time");
	auto msg = split(message, '*');
	if (msg.size() < 3 || msg.at(1) != "C" || msg.at(2).size() != 1) throw std::runtime_error("Bad message format when receiving message from client");
	return msg.at(2).at(0);
}

void
sendLocalCharacter(char character, std::shared_ptr<TcpClient> client)
{
  std::ostringstream ss;
	ss << "*C*" << character << "*#";
	client->send(ss.str());
}

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	try {
		TCLAP::CmdLine cmd("Multiplayer tetris", ' ', "0.1.1");
		TCLAP::ValueArg<char> char1("1", "character-1", "Player 1 character", true, 'n', "name", cmd);
		TCLAP::ValueArg<char> char2("2", "character-2", "Player 2 character", false, ' ', "name", cmd);
		TCLAP::SwitchArg localgame("l", "local-game", "Local multiplayer", cmd, false);
		TCLAP::SwitchArg aigame("a", "ai-game", "Against AI", cmd, false);
		TCLAP::ValueArg<std::string> networkgame("n", "enemy-addr", "Network game enemy address", false, {"tcp://127.0.0.1:4242"}, "address", cmd);
		
		cmd.parse(argc, argv);

		std::shared_ptr<LogicInterface> player1 = std::make_shared<Logic>();
		std::shared_ptr<LogicInterface> player2;

		std::shared_ptr<TcpClient> client;
		std::string address = networkgame.getValue();
		char charStr1 = char1.getValue();
		char charStr2;
		GameType type;
		if (localgame.getValue()) {
			charStr2 = char2.getValue();
			player2 = std::make_shared<Logic>();
			type = GameType::TWOPLAYER;
		}else if (aigame.getValue()) {
			charStr2 = char2.getValue();
			player2 = std::make_shared<Logic>();
			type = GameType::AI;
		}else if (!address.empty()) {
			auto delim = address.find(":");
			if (delim == std::string::npos) throw std::runtime_error("Wrong format for connect address");
			std::string ip = address.substr(0, delim);
			std::string port = address.substr(delim+1);
			client = std::make_shared<TcpClient>(ip, std::stoi(port));
			std::string message = client->receive(5);
			if (message.empty()) throw std::runtime_error("Did not find any opponent");
			if (message != "start") throw std::runtime_error("Invalid game start message received");
			sendLocalCharacter(charStr1, client);
			charStr2 = getNWCharacter(client);
			player2 = std::make_shared<PassiveLogic>();
			type = GameType::NETWORK;
		} else {
			throw std::runtime_error("No game type selected. Please select a game type");
		}

		player1->setEnemy(player2);
		player2->setEnemy(player1);

		std::shared_ptr<Character> character1 = makeCharacter(charStr1, player1, player2);
		std::shared_ptr<Character> character2 = makeCharacter(charStr2, player2, player1);
		std::shared_ptr<View> view = std::make_shared<View>(player1, player2, *character1, *character2);

		GameLoop game(player1, player2, view, *character1, *character2, type, client);
		game.loop();
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
