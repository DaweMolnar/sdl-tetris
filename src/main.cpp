#include "GameLoop.hh"
#include "View.hh"
#include "Character.hh"

#include <exception>
#include <iostream>
#include <time.h>

int main(int argc, char *args[])
{
	srand((unsigned)time(NULL));
	try {
		Logic player1;
		Logic player2;
		player1.setEnemy(player2);
		player2.setEnemy(player1);
		std::shared_ptr<View> view = std::make_shared<View>(player1, player2);
		BetaCharacter character1(player1, player2);
		BetaCharacter character2(player2, player1);
		GameLoop game(player1, player2, view, character1, character2, GameType::AI);
		game.loop();
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		while (true) {}
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
