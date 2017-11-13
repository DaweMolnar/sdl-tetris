#include "GameLoop.hh"
#include "View.hh"
#include "Character.hh"
#include "Client.hh"

#include <exception>
#include <iostream>
#include <time.h>
#include <tclap/CmdLine.h>

std::shared_ptr<Character>
makeCharacter(char type, Logic& self, Logic& enemy)
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

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	try {
		TCLAP::CmdLine cmd("Multiplayer tetris", ' ', "0.1.1");
		TCLAP::ValueArg<char> char1("1", "character-1", "Player 1 character", true, 'n', "name", cmd);
		TCLAP::ValueArg<char> char2("2", "character-2", "Player 1 character", true, 'm', "name", cmd);
		TCLAP::SwitchArg localgame("l", "local-game", "Local multiplayer", cmd, false);
		TCLAP::SwitchArg aigame("a", "ai-game", "Against AI", cmd, false);
		TCLAP::ValueArg<std::string> networkgame("n", "enemy-addr", "Network game enemy address", false, {"tcp://127.0.0.1:4242"}, "address", cmd);
		
		cmd.parse(argc, argv);

		Logic player1;
		Logic player2;
		player1.setEnemy(player2);
		player2.setEnemy(player1);

		std::shared_ptr<Character> character1 = makeCharacter(char1.getValue(), player1, player2);
		std::shared_ptr<Character> character2 = makeCharacter(char2.getValue(), player2, player1);
		std::shared_ptr<View> view = std::make_shared<View>(player1, player2, *character1, *character2);

		std::shared_ptr<TcpClient> client;
		std::string address = networkgame.getValue();

		GameType type;
		if (localgame.getValue()) {
			type = GameType::TWOPLAYER;
		}else if (aigame.getValue()) {
			type = GameType::AI;
		}else if (!address.empty()) {
			auto delim = address.find(":");
			if (delim == std::string::npos) throw std::runtime_error("Wrong format for IP address");
			std::string ip = address.substr(0, delim);
			std::string port = address.substr(delim+1);
			std::cerr << "before" << std::endl;
			client = std::make_shared<TcpClient>(ip, std::stoi(port));
			std::string message = client->receive(0);
			if (message != "start") throw std::runtime_error("Invalid game start message received");
			type = GameType::NETWORK;
		} else {
			throw std::runtime_error("No game type selected. Please select a game type");
		}

		GameLoop game(player1, player2, view, *character1, *character2, type, client);
		game.loop();
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
