#include "GameLoop.hh"
#include "Ai.hh"
#include "LocalController.hh"
#include "NWController.hh"
#include "KeyMap.hh"
#include <memory>

GameLoop::GameLoop(std::shared_ptr<LogicInterface> logic1, std::shared_ptr<LogicInterface> logic2, std::shared_ptr<ViewInterface> view, Character& character1, Character& character2, GameType type, std::shared_ptr<TcpClient> client)
: logicPlayer1_(logic1)
, logicPlayer2_(logic2)
, view_(view)
, run_(true)
{
	if (!view_) throw std::runtime_error("View parameter cannot be empty in gameloop");
	KeyMap km2{SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDL_SCANCODE_DOWN, SDLK_RSHIFT};
	KeyMap km1{SDLK_a, SDLK_d, SDLK_w, SDL_SCANCODE_S, SDLK_LSHIFT}; //TODO get from parameter
	if (type == GameType::NETWORK) {
		controlPlayer1_ = std::make_unique<NWSController>(logicPlayer1_, character1, client, km1);
		controlPlayer2_ = std::make_unique<NWCController>(logicPlayer2_, character2, client);
	} else if (type == GameType::AI) {
		controlPlayer1_ = std::make_unique<LocalController>(logicPlayer1_, character1, km1);
		controlPlayer2_ = std::make_unique<Ai>(logicPlayer2_, character2);
	} else {
		controlPlayer1_ = std::make_unique<LocalController>(logicPlayer1_, character1, km1);
		controlPlayer2_ = std::make_unique<LocalController>(logicPlayer2_, character2, km2);
	}
}

void
GameLoop::handleEvents(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			run_ = false;
			return;
		}
		controlPlayer1_->handleKey(event.key.keysym.sym);
		controlPlayer2_->handleKey(event.key.keysym.sym);
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
		logicPlayer1_->update();
		logicPlayer2_->update();
		unsigned slowness = 50;
		if (slowness < 1) slowness = 1;
		for (size_t i = 0; i < slowness; i++) {
			view_->render();
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				handleEvents(e);
			}
			controlPlayer1_->tick();
			controlPlayer2_->tick();
			if (logicPlayer1_->finished() || logicPlayer2_->finished()) {
				logicPlayer1_->newGame();
				logicPlayer2_->newGame();
			}
			if (!run_) break;
			SDL_Delay(1);
		}	
	}
}
