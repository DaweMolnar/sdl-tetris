#pragma once
#include "Logic.hh"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class Game
{
public:
	Game(Logic& logic);
	~Game();
	void loop();

private:
	void renderText(const SDL_Color& color, SDL_Rect& destination, const std::string& text);
	void handleEvents(const SDL_Event& event);
	void handleKey(const SDL_Keycode& key);
	void render();
	void renderScore();
	void renderTable(SDL_Texture* tex);
	void renderNextShape(SDL_Texture* tex);

	SDL_Window* window_;
	SDL_Renderer* ren_;
	Mix_Music* bgMusic_;
	TTF_Font* font_;
	SDL_Texture *background_;
	SDL_Texture *blockTexture_;
	Logic& logic_;
	bool run_;
};

