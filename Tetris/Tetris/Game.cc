#include "Game.hh"
#include <stdexcept>
#include <SDL_image.h>

Game::Game(Logic& logic)
: run_(true)
, logic_(logic)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	window_ = SDL_CreateWindow("Tetris", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (window_ == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}
	ren_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw std::runtime_error(SDL_GetError());
	}
	/*background_ = IMG_LoadTexture(ren_, "img/background.png");
	if (background_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}*/
}

Game::~Game()
{
	SDL_DestroyRenderer(ren_);
	SDL_DestroyWindow(window_);
}

void
Game::handleEvents(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_KEYDOWN:
		run_ = false;
		break;
	case SDL_QUIT:
		run_ = false;
		break;
	default:
		run_ = true;
		break;
	}
}

void
Game::render()
{
	SDL_RenderClear(ren_);
	SDL_RenderCopy(ren_, background_, NULL, NULL);
	SDL_RenderPresent(ren_);
}

void
Game::loop()
{
	while (run_) {
		render();
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			handleEvents(e);
		}
	}
}