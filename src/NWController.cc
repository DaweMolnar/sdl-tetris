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
NWSController::sendTable()
{
  std::ostringstream ss;
	ss << "*T*";
	auto table = logic_->getTable();
	for (auto line : table) {
		for (auto elem : line) {
			switch (elem) {
				case Color::none:
					ss << 'E';
				break;
				case Color::magic:
					ss << 'M';
				break;
				default:
					ss << 'C';
				break;
			}
		}
	}
	ss << "*#";
	client_->send(ss.str());
}

void
NWSController::sendTetromino()
{
  std::ostringstream ss;
	ss << "*E*";
	auto tetromino = logic_->getCurrentShape();
	ss << tetromino.topLeft.first << "*" << tetromino.topLeft.second << "*";
	auto shape = tetromino.shape;
	ss << shape.size() << "*" << (shape.size() != 0 ? shape.at(0).size() : 0) << "*";
	for (auto line : shape) {
		for (auto elem : line) {
			switch (elem) {
				case Color::none:
					ss << 'E';
				break;
				case Color::magic:
					ss << 'M';
				break;
				default:
					ss << 'C';
				break;
			}
		}
	}
	ss << "*#";
	client_->send(ss.str());
}

void
NWSController::tick()
{
	time_t currentTime = time(nullptr);
	if (currentTime > lastTableSent_ + tableSendDelay_) {
		lastTableSent_ = currentTime;
		sendTable();
		sendTetromino();
		sendMana();
	}
	sendLinesToAdd();
	if (logic_->finished()) sendGameOver();
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if ( keystate[keyMap_.down] ) logic_->move(0, 1);
}

void
NWCController::updateTetromino(size_t pos1, size_t pos2, size_t row, size_t col, const std::string& shape)
{
	if (row * col > shape.size()) return;
	Position pos = std::make_pair(pos1, pos2);
	Shape finalShape;
	int currentPos = 0;
	for (size_t i = 0; i < row; i++) {
		std::vector<Color> tmpShape;
		for (size_t j = 0; j < col; j++) {
			switch (shape.at(currentPos++)) {
				case 'C':
					tmpShape.push_back(Color::blue);
				break;
				case 'M':
					tmpShape.push_back(Color::magic);
				break;
				default:
					tmpShape.push_back(Color::none);
				break;
			}
		}
		finalShape.push_back(tmpShape);
	}
	if (shape.size() <= 0) return;
	std::shared_ptr<Tetromino> tetromino = std::make_shared<Tetromino>(finalShape, pos);
	logic_->changeCurrentShape(tetromino);
}

void
NWCController::updateTable(const std::string& recTable)
{
	//TODO handle partial table
	if ((TETRIS_ROW * TETRIS_COL) > recTable.size()) return;
	auto table = logic_->getTable();
	int currentPos = 0;
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table.at(i).size(); j++) {
			switch (recTable.at(currentPos++)) {
				case 'C':
					table.at(i).at(j) = Color::blue;
				break;
				case 'M':
					table.at(i).at(j) = Color::magic;
				break;
				default:
					table.at(i).at(j) = Color::none;
				break;
			}
		}
	}
	logic_->changeTable(table);
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
		case 'T':
			if (params.size() < 2) return;
			updateTable(params.at(1));
		break;
		case 'E':
			if (params.size() < 6) return;
			updateTetromino(std::stoi(params.at(1)), std::stoi(params.at(2)), std::stoi(params.at(3)), std::stoi(params.at(4)), params.at(5));
		break;
		case 'D':
			throw std::runtime_error("Enemy disconnected");
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
