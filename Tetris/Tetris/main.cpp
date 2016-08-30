#include "Game.hh"
#include <exception>
#include <iostream>
#include <time.h>

int main(int argc, char *args[])
{
	srand((unsigned)time(NULL));
	try {
		Logic logic;
		Game game(logic);
		game.loop();
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}