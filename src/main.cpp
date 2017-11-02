#include "GameLoop.hh"
#include "View.hh"
#include "Character.hh"

#include <exception>
#include <iostream>
#include <time.h>
#include <tclap/CmdLine.h>

std::shared_ptr<Character>
makeCharacter(char type, Logic& self, Logic& enemy)
{
	switch(type) {
		case 'n':
			return std::make_shared<BetaCharacter>(self,enemy);
		case 'm':
			return std::make_shared<BetaCharacter>(self,enemy);
		case 'w':
			return std::make_shared<BetaCharacter>(self,enemy);
		default:
			return std::make_shared<BetaCharacter>(self,enemy);
	}
}

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	try {
		TCLAP::CmdLine cmd("Multiplayer tetris", ' ', "0.1.1");
		TCLAP::ValueArg<char> char1("c1", "character-1", "Player 1 character", false, 'n', "name", cmd);
		TCLAP::ValueArg<char> char2("c2", "character-2", "Player 1 character", false, 'm', "name", cmd);
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
		std::shared_ptr<View> view = std::make_shared<View>(player1, player2, character1, character2);
		GameLoop game(player1, player2, view, character1.get(), character2.get(), GameType::AI);
		game.loop();
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
