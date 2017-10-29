#pragma once

#include "Logic.hh"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class ViewInterface {
public:
	ViewInterface(Logic& logic1, Logic& logic2)
	: logicPlayer1_(logic1)
	, logicPlayer2_(logic2) {}

	virtual ~ViewInterface() {}
	virtual void render()=0;

protected:
	Logic& logicPlayer1_;
	Logic& logicPlayer2_;
};

class View : public ViewInterface {
public:
	View(Logic& logic1, Logic& logic2, const char* player1Avatar, const char* player2Avatar);
	~View();
	void render() override;

private:
	void renderMana(Logic& logic, const unsigned topleftX, const unsigned topleftY);
	void renderAvatar(SDL_Texture* texture, const unsigned topleftX, const unsigned topleftY);
	void renderWins(Logic& logic, const unsigned topleftX, const unsigned topleftY);
	void renderTable(Logic& logic, SDL_Texture* tex, const unsigned topleftX, const unsigned topleftY);
	void renderNextShape(Logic& logic, SDL_Texture* tex, const unsigned topleftX, const unsigned topleftY);
	void renderText(const SDL_Color& color, SDL_Rect& destination, const std::string& text);
	
	SDL_Window* window_;
	SDL_Renderer* ren_;
//	Mix_Music* bgMusic_;
	TTF_Font* font_;
	SDL_Texture* background_;
	SDL_Texture* blockTexture_;
	SDL_Texture* player1Avatar_;
	SDL_Texture* player2Avatar_;
};
