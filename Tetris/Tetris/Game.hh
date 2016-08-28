#pragma once
#include <SDL.h>

class Game
{
public:
	Game();
	~Game();
	void loop();

private:
	void handleEvents(const SDL_Event& event);
	void render();

	SDL_Window* window_;
	SDL_Renderer* ren_;
	SDL_Texture *background_;
	bool run_;
};

