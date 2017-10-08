#include "LocalController.hh"

void
LocalController::handleKey(const SDL_Keycode& key)
{
	if (key == keyMap_.left) {
		logic_.move(-1, 0);
	} else if (key == keyMap_.right) {
		logic_.move(1, 0);
	} else if (key == keyMap_.down) {
		logic_.move(0, 1);
	} else if (key == keyMap_.up) {
		logic_.rotate();
	} else if (key == keyMap_.special) {
		character_.doSpecial();
	}
}

