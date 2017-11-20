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
		sendSpecial();
	}
}

void
NWSController::sendSpecial()
{
	client_->send("*S*#");
}


void
NWSController::sendMana()
{
  std::ostringstream ss;
	ss << "*M*" << logic_->getMana() << "*#";
	client_->send(ss.str());
}

void
NWSController::sendLinesToAdd()
{
	if (!clientLogic_->linesToAdd()) return;
  std::ostringstream ss;
	ss << "*A*" << clientLogic_->linesToAdd() << "*#";
	client_->send(ss.str());
	clientLogic_->linesAdded();
}

void
NWSController::sendGameOver()
{
	client_->send("*L*#");
}

void
NWSController::tick()
{
	//TODO table
	sendMana();
	sendLinesToAdd();
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
		case 'S':
			character_.doSpecial();
		break;
		case 'A':
			if (params.size() < 2) return;
			for (int i = 0; i < std::stoi(params.at(1)); i++) {
				serverLogic_->addPlusLine();
			}
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
