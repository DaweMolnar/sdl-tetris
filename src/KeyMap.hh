#pragma once

#include <SDL.h>

struct KeyMap {
	SDL_Keycode left;
	SDL_Keycode right;
	SDL_Keycode up;
	SDL_Keycode down;
	SDL_Keycode special;
};
