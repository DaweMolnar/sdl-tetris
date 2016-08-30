#pragma once
#include "Logic.hh"

#include <SDL.h>

class Game
{
public:
	Game(Logic& logic);
	~Game();
	void loop();

private:
	void handleEvents(const SDL_Event& event);
	void handleKey(const SDL_Keycode& key);
	void render();

	SDL_Window* window_;
	SDL_Renderer* ren_;
	SDL_Texture *background_;
	Logic& logic_;
	bool run_;
};

