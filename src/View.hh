#pragma once

#include "Logic.hh"
#include "Character.hh"

#include <SDL.h>
#include <SDL_ttf.h>

class ViewInterface {
public:
	ViewInterface(std::shared_ptr<LogicInterface> logic1, std::shared_ptr<LogicInterface> logic2)
	: logicPlayer1_(logic1)
	, logicPlayer2_(logic2) {}

	virtual ~ViewInterface() {}
	virtual void render()=0;

protected:
	std::shared_ptr<LogicInterface> logicPlayer1_;
	std::shared_ptr<LogicInterface> logicPlayer2_;
};

class View : public ViewInterface {
public:
	View(std::shared_ptr<LogicInterface> logic1, std::shared_ptr<LogicInterface> logic2, Character& player1Character, Character& player2Character);
	~View();
	void render() override;

private:
	void renderMana(std::shared_ptr<LogicInterface> logic, const unsigned topleftX, const unsigned topleftY);
	void renderAvatar(SDL_Texture* texture, const unsigned topleftX, const unsigned topleftY);
	void renderWins(std::shared_ptr<LogicInterface> logic, const unsigned topleftX, const unsigned topleftY);
	void renderTable(std::shared_ptr<LogicInterface> logic, SDL_Texture* tex, const unsigned topleftX, const unsigned topleftY);
	void renderNextShape(std::shared_ptr<LogicInterface> logic, SDL_Texture* tex, const unsigned topleftX, const unsigned topleftY);
	void renderText(const SDL_Color& color, SDL_Rect& destination, const std::string& text);
	void renderSpecial(Character& character, const unsigned topleftX, const unsigned topleftY);
	
	SDL_Window* window_;
	SDL_Renderer* ren_;
	TTF_Font* font_;
	SDL_Texture* background_;
	SDL_Texture* blockTexture_;
	SDL_Texture* player1Avatar_;
	SDL_Texture* player2Avatar_;
	Character& character1_;
	Character& character2_;
};
