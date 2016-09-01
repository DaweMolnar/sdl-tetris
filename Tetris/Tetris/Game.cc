#include "Game.hh"
#include <stdexcept>
#include <SDL_image.h>
#include <string>

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
	TTF_Init();
	font_ = TTF_OpenFont("sample.ttf", 20);
}

Game::~Game()
{
	SDL_DestroyRenderer(ren_);
	SDL_DestroyWindow(window_);
}

void
Game::handleKey(const SDL_Keycode& key)
{
	if (key == SDLK_LEFT) {
		logic_.move(-1, 0);
	} else if (key == SDLK_RIGHT) {
		logic_.move(1, 0);
	} else if (key == SDLK_DOWN) {
		logic_.move(0, 1);
	} else if (key == SDLK_UP) {
		logic_.rotate();
	}
}
void
Game::handleEvents(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_KEYDOWN:
		handleKey(event.key.keysym.sym);
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
Game::renderTable(SDL_Texture* tex)
{
	SDL_Rect sect;
	SDL_Rect dest;
	auto table = logic_.getTable();
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < table.at(i).size(); j++) {
			if (table[i][j] == Color::none) continue;
			sect = getSect(table[i][j]);
			dest = getDest(j, i);
			SDL_RenderCopy(ren_, tex, &sect, &dest);
		}
	}
}

void
Game::renderNextShape(SDL_Texture* tex)
{
	SDL_Rect sect;
	SDL_Rect dest;
	dest.w = blockDimension / 2;
	dest.h = blockDimension / 2;
	auto shape = logic_.getNextShape();
	for (size_t i = 0; i < shape.shape.size(); i++) {
		for (size_t j = 0; j < shape.shape.at(i).size(); j++) {
			if (shape.shape[i][j] == Color::none) continue;
			sect = getSect(shape.shape[i][j]);
			dest.x = firstBlockX + dest.w * j + 400;
			dest.y = firstBlockY + dest.w * i + 30;
			SDL_RenderCopy(ren_, tex, &sect, &dest);
		}
	}
}
void
Game::renderScore()
{
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Rect destination;
	destination.x = 420;
	destination.y = 150;
	renderText(color, destination, std::to_string(logic_.getScore()));
}
void
Game::render()
{
	SDL_RenderClear(ren_);
	SDL_RenderCopy(ren_, background_, NULL, NULL);
	SDL_Texture* tex = IMG_LoadTexture(ren_, "img/blocks.png");
	if (tex == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	renderTable(tex);
	renderNextShape(tex);
	renderScore();
	SDL_RenderPresent(ren_);
}
void
Game::renderText(const SDL_Color& color, SDL_Rect& destination, const std::string& text)
{
	if (font_ == nullptr) {
		throw std::runtime_error("No font declared");
	}
	SDL_Surface *surf = TTF_RenderText_Blended(font_, text.c_str(), color);
	SDL_Texture* score = SDL_CreateTextureFromSurface(ren_, surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(score, NULL, NULL, &destination.w, &destination.h);
	SDL_RenderCopy(ren_, score, NULL, &destination);
}

void
Game::loop()
{
	while (run_) {
		logic_.update();
		const unsigned slowness = 50;
		for (size_t i = 0; i < slowness; i++) {
			render();
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				handleEvents(e);
			}
			if (logic_.finished()) {
				logic_.newGame();
			}
			if (!run_) break;
			SDL_Delay(1);
		}
		
	}
}