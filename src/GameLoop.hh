#pragma once
#include "Logic.hh"
#include "ControllerInterface.hh"
#include "View.hh"
#include "Character.hh"
#include "Client.hh"

#include <SDL.h>

enum class GameType {
	AI,
	TWOPLAYER,
	NETWORK
};

class GameLoop
{
public:
	GameLoop(
			std::shared_ptr<LogicInterface> logic1
			, std::shared_ptr<LogicInterface> logic2
			, std::shared_ptr<ViewInterface> view
			, Character& character1
			, Character& character2
			, GameType type
			, std::shared_ptr<TcpClient> client
	);
	void loop();

private:
	void handleEvents(const SDL_Event& event);
	
	std::shared_ptr<LogicInterface> logicPlayer1_; 
	std::shared_ptr<LogicInterface> logicPlayer2_;
	std::shared_ptr<ViewInterface> view_;
	std::unique_ptr<ControllerInterface> controlPlayer1_;
	std::unique_ptr<ControllerInterface> controlPlayer2_;
	bool run_;
};

