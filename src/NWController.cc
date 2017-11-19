#include "NWController.hh"
#include "Utility.hh"
#include <sstream>

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
NWSController::sendMana()
{
  std::ostringstream ss;
	ss << "*M*" << logic_->getMana() << "*#";
	client_->send(ss.str());
}

void
NWSController::sendGameOver()
{
	client_->send("*L*#");
}

void
NWSController::tick()
{
	//TODO send mana and table and gameover
	sendMana();
	if (logic_->finished()) sendGameOver();
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if ( keystate[keyMap_.down] ) logic_->move(0, 1);
}

void
NWCController::handleMessage(const std::string& message)
{
	auto params = split(message, '*');
	if (params.size() < 1 || params.at(0).empty()) return;
	switch (params.at(0).at(0)) {
		case 'M':
			if (params.size() < 2) return;
			logic_->setMana(std::stoi(params.at(1)));
		break;
		case 'L':
			logic_->setFinished(true);
		break;
		default:
		break;
	}
}

void
NWCController::tick()
{
	std::string message = client_->receive(0);
	if (message.empty()) return;
	auto messages = split(message, '#');
	for (auto msg : messages) {
		handleMessage(msg);
	}
	//TODO receive, and parse messages, send plusLines from logic
}
