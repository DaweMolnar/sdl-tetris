#include "Game.hh"
#include <stdexcept>
#include <SDL_image.h>

static const unsigned firstBlockX = 18;
static const unsigned firstBlockY = 24;
static const unsigned blockDimension = 35;

Game::Game(Logic& logic)
: run_(true)
, logic_(logic)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	window_ = SDL_CreateWindow("Tetris", 100, 100, 560, 640, SDL_WINDOW_SHOWN);
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
	background_ = IMG_LoadTexture(ren_, "img/background.png");
	if (background_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}
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

SDL_Rect
getSect(Color color)
{
	SDL_Rect sect;
	sect.y = 0;
	sect.w = 50;
	sect.h = 50;
	switch (color) {
	case Color::yellow :
		sect.x = 50;
		break;
	case Color::green:
		sect.x = 0;
		break;
	case Color::grey:
		sect.x = 100;
		break;
	case Color::blue:
		sect.x = 150;
		break;
	case Color::red:
		sect.x = 200;
		break;
	case Color::purple:
		sect.x = 250;
		break;
	}
	return sect;
}

SDL_Rect
getDest(unsigned row, unsigned col)
{
	SDL_Rect dest;
	dest.x = firstBlockX + blockDimension * row;
	dest.y = firstBlockY + blockDimension * col;
	dest.w = blockDimension;
	dest.h = blockDimension;
	return dest;
}

void
Game::render()
{
	SDL_RenderClear(ren_);
	SDL_RenderCopy(ren_, background_, NULL, NULL);
	SDL_Rect sect;
	SDL_Rect dest;
	SDL_Texture* tex = IMG_LoadTexture(ren_, "img/blocks.png");
	if (tex == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	auto table = logic_.getTable();
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table.at(i).size(); j++) {
			if (table[i][j] == Color::none) continue;
			sect = getSect(table[i][j]);
			dest = getDest(i, j);
			SDL_RenderCopy(ren_, tex, &sect, &dest);
		}
	}
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