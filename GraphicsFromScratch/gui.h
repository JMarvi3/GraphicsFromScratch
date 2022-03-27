#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>

class gui
{
	SDL_Surface* winSurface = NULL;
	SDL_Window* window = NULL;
public:
	int height = 0, width = 0;
	gui();
	gui(int width, int height);
	void set_pixel(int x, int y, Uint32 color);
	void update();
	void wait_for_exit();
};

