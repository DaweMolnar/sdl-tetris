#include "NWController.hh"

void
NWSController::handleKey(const SDL_Keycode& key)
{
	if (key == keyMap_.left) {
		logic_->move(-1, 0);
	} else if (key == keyMap_.right) {
		logic_->move(1, 0);
	} else if (key == keyMap_.up) {
		logic_->rotate();
	} else if (key == keyMap_.special) {
		character_.doSpecial();
		//TODO send special
	}
}

void
NWSController::tick()
{
	//TODO send mana and table and gameover
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if ( keystate[keyMap_.down] ) logic_->move(0, 1);
}

void
NWCController::tick()
{
	std::string message = client_->receive(0);
	if (message.empty()) return;
	//TODO receive, and parse messages, send plusLines from logic
}
