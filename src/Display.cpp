#include "Display.h"

void Display::Initialize()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Failed to Initialize SDL video: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("CHIP-8 Emulator", 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderSetLogicalSize(renderer, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    surface = SDL_GetWindowSurface(window);
}

void Display::Update(const uint32_t (&display)[2048])
{
    uint32_t pixelBuffer[2048 * 1];

    for(uint32_t px = 0; px < 2048; px += 1)
    {
        pixelBuffer[px] = ((FG_COLOR * display[px]) | BG_COLOR);
    }

    SDL_UpdateTexture(texture, nullptr, pixelBuffer, SCREEN_WIDTH * (sizeof(pixelBuffer[0])));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Display::Destroy()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Display::DisplayPollEvents()
{
    SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				return true;
			} 
        }
    }
    return false;
}