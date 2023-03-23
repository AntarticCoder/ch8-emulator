#include <iostream>
#include <chrono>
#include <thread>

#include "Chip8/Chip8.h"
#include "Display/Display.h"
#include "Debugger/Debugger.h"

void UpdateDebugger(Chip8 chip, DebugInfo info)
{
    for(int i = 0; i < 16; i++) { info.registers[i] = chip.registers[i]; }
}

int main()
{
    std::cout << "CH8-Emulator starting up\n";

    Chip8 chip;
    chip.Initialize();
    chip.LoadRom("/Users/nick/Programming/ch8-emulator/roms/IBM.ch8");

    Display display;
    display.Initialize();

    Debugger debug;
    DebugInfo info;
    debug.Initialize();

    bool quit = false;
    while(!quit)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        chip.Cycle();

        display.Update(chip.display);
        debug.Update(info);

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