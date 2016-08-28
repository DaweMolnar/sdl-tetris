#include "Game.hh"
#include <exception>
#include <iostream>

int main(int argc, char *args[])
{
	try {
		Game game;
		game.loop();
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}