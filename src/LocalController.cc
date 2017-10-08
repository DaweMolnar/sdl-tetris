#include "LocalController.hh"

void
LocalController::handleKey(const SDL_Keycode& key)
{
	if (key == SDLK_LEFT) {
		logic_.move(-1, 0);
	} else if (key == SDLK_RIGHT) {
		logic_.move(1, 0);
	} else if (key == SDLK_DOWN) {
		logic_.move(0, 1);
	} else if (key == SDLK_UP) {
		logic_.rotate();
	} else if (key == SDLK_SPACE) {
		character_.doSpecial();
	}

	/*if (ai_) return;

	if (key == SDLK_a) {
		logicPlayer1_.move(-1, 0);
	} else if (key == SDLK_d) {
		logicPlayer1_.move(1, 0);
	} else if (key == SDLK_s) {
		logicPlayer1_.move(0, 1);
	} else if (key == SDLK_w) {
		logicPlayer1_.rotate();
	}
	*/
}

