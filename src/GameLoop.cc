#include "GameLoop.hh"
#include <memory>

GameLoop::GameLoop(Logic& logic1, Logic& logic2, View& view, GameType type)
:  logicPlayer1_(logic1)
, logicPlayer2_(logic2)
, view_(view)
, run_(true)
{
	if (type == GameType::AI) {
		ai_ = std::make_unique<Ai>(logicPlayer1_);
	}
}

void
GameLoop::handleKey(const SDL_Keycode& key)
{
	if (key == SDLK_LEFT) {
		logicPlayer2_.move(-1, 0);
	} else if (key == SDLK_RIGHT) {
		logicPlayer2_.move(1, 0);
	} else if (key == SDLK_DOWN) {
		logicPlayer2_.move(0, 1);
	} else if (key == SDLK_UP) {
		logicPlayer2_.rotate();
	}

	if (ai_) return;

	if (key == SDLK_a) {
		logicPlayer1_.move(-1, 0);
	} else if (key == SDLK_d) {
		logicPlayer1_.move(1, 0);
	} else if (key == SDLK_s) {
		logicPlayer1_.move(0, 1);
	} else if (key == SDLK_w) {
		logicPlayer1_.rotate();
	}
}

void
GameLoop::handleEvents(const SDL_Event& event)
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

void
GameLoop::loop()
{
	while (run_) {
		logicPlayer1_.update();
		logicPlayer2_.update();
		unsigned slowness = 50;
		if (slowness < 1) slowness = 1;
		for (size_t i = 0; i < slowness; i++) {
			view_.render();
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				handleEvents(e);
			}
			if (ai_) ai_->makeNextMove();
			if (logicPlayer1_.finished() || logicPlayer2_.finished()) {
				logicPlayer1_.newGame();
				logicPlayer2_.newGame();
			}
			if (!run_) break;
			SDL_Delay(1);
		}
		
	}
}
