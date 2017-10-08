#pragma once
#include "Logic.hh"
#include "ControllerInterface.hh"
#include "View.hh"
#include "Character.hh"

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
			Logic& logic1
			, Logic& logic2
			, View& view
			, Character& character1
			, Character& character2
			, GameType type
	);
	void loop();

private:
	void handleEvents(const SDL_Event& event);
	
	Logic& logicPlayer1_; 
	Logic& logicPlayer2_;
	View& view_;
	std::unique_ptr<ControllerInterface> controlPlayer1_;
	std::unique_ptr<ControllerInterface> controlPlayer2_;
	bool run_;
};

