#pragma once
#include "Logic.hh"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class Game
{
public:
	Game(Logic& logic1, Logic& logic2);
	~Game();
	void loop();

private:
	void renderText(const SDL_Color& color, SDL_Rect& destination, const std::string& text);
	void handleEvents(const SDL_Event& event);
	void handleKey(const SDL_Keycode& key);
	void render();
	void renderScore(Logic& logic, const unsigned topleftX, const unsigned topleftY);
	void renderHighScore(Logic& logic, const unsigned topleftX, const unsigned topleftY);
	void renderTable(Logic& logic, SDL_Texture* tex, const unsigned topleftX, const unsigned topleftY);
	void renderNextShape(Logic& logic, SDL_Texture* tex, const unsigned topleftX, const unsigned topleftY);

	SDL_Window* window_;
	SDL_Renderer* ren_;
	Mix_Music* bgMusic_;
	TTF_Font* font_;
	SDL_Texture *background_;
	SDL_Texture *blockTexture_;
	Logic& logicPlayer1_; 
	Logic& logicPlayer2_;
	bool run_;
};

