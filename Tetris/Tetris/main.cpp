#include "Game.hh"
#include <exception>
#include <iostream>
#include <time.h>

int main(int argc, char *args[])
{
	srand((unsigned)time(NULL));
	try {
		Logic logic1;
		Logic logic2;
		Game game(logic1, logic2);
		game.loop();
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		while (true) {}
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}