#pragma once
#include <SDL2/SDL.h>
#include <iostream>

#include "Common.h"

#define FG_COLOR 0xFF1976D2
#define BG_COLOR 0xFF212121

class Display
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
public:
	void Initialize();
	void Update(const uint32_t (&display)[2048]);
	void Destroy();
	bool ShouldWindowClose();
};