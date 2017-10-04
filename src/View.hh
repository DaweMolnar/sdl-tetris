#pragma once

#include "Logic.hh"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class View {
public:
	View(Logic& logic1, Logic& logic2);
	~View();
	void render();

private:
	void renderScore(Logic& logic, const unsigned topleftX, const unsigned topleftY);
	void renderHighScore(Logic& logic, const unsigned topleftX, const unsigned topleftY);
	void renderTable(Logic& logic, SDL_Texture* tex, const unsigned topleftX, const unsigned topleftY);
	void renderNextShape(Logic& logic, SDL_Texture* tex, const unsigned topleftX, const unsigned topleftY);
	void renderText(const SDL_Color& color, SDL_Rect& destination, const std::string& text);
	
	Logic& logicPlayer1_; 
	Logic& logicPlayer2_;

	SDL_Window* window_;
	SDL_Renderer* ren_;
	Mix_Music* bgMusic_;
	TTF_Font* font_;
	SDL_Texture *background_;
	SDL_Texture *blockTexture_;
};
