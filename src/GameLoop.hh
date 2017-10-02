#pragma once
#include "Logic.hh"
#include "Ai.hh"
#include "View.hh"

#include <SDL.h>

enum class GameType {
	AI,
	TWOPLAYER,
	NETWORK
};

class GameLoop
{
public:
	GameLoop(Logic& logic1, Logic& logic2, View& view, GameType type);
	void loop();

private:
	void handleEvents(const SDL_Event& event);
	void handleKey(const SDL_Keycode& key);
	
	Logic& logicPlayer1_; 
	Logic& logicPlayer2_;
	View& view_;
	std::unique_ptr<Ai> ai_;
	bool run_;
};

