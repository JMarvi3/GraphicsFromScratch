#include "gui.h"
#include <iostream>
using namespace std;

gui::gui() = default;

gui::gui(int init_width, int init_height) : height(init_height), width(init_width)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		throw exception();
	}

	window = SDL_CreateWindow("Graphics From Scratch", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		throw exception();
	}

	winSurface = SDL_GetWindowSurface(window);
	if (!winSurface) {
		cout << "Error getting surface: " << SDL_GetError() << endl;
		throw exception();
	}
	SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 255, 255));
	SDL_UpdateWindowSurface(window);
}

void gui::set_pixel(int x, int y, Uint32 color)
{
	const int sx = width / 2 + x, sy = height/2 - y;
	Uint32* pixels = static_cast<Uint32*>(winSurface->pixels);
	pixels[sy * winSurface->w + sx] = color;
}

void gui::update()
{
	SDL_UpdateWindowSurface(window);
}

void gui::wait_for_exit()
{
	SDL_Event event;
	while (true) {
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				return;
	}
}
