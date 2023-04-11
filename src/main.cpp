#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

#include "Chip8/Chip8.h"
#include "Display/Display.h"
#include "Debugger/Debugger.h"

int main(int argc, char* argv[])
{
    std::cout << '\n';

    if(argc == 1) { std::cout << "Chip 8 ROM not specified, please enter rom path as a full path and not relative\n\n"; return 0; }
    if(argc >= 3) { std::cout << "Too many arguements passed in, please pass in the full path of the rom by itself\n\n"; return 0; }

    std::stringstream romPath;
    romPath << argv[1];

    std::cout << "CH8-Emulator starting up\n";

    Chip8 chip;
    chip.Initialize();
    chip.LoadRom(romPath.str());

    Display display;
    display.Initialize();

    Debugger debug;
    debug.Initialize();

    bool quit = false;
    while(!quit)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        chip.Cycle();

        display.Update(chip.display);
        debug.Update(chip);

        SDL_Event event;
        while(SDL_PollEvent(&event) > 0)
        {
            if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(display.window))
            {
                return 0;
            } 
            if(event.window.windowID == SDL_GetWindowID(debug.window)) { ImGui_ImplSDL2_ProcessEvent(&event); }
        }
    }

    debug.Destroy();
    display.Destroy();
    return 0;
}