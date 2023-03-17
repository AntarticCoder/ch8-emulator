#include <iostream>
#include <chrono>
#include <thread>

#include "Chip8/Chip8.h"
#include "Display/Display.h"
#include "Debugger/Debugger.h"

int main()
{
    std::cout << "CH8-Emulator starting up\n";

    Chip8 chip;
    chip.Initialize();
    chip.LoadRom("/Users/nick/Programming/ch8-emulator/roms/IBM.ch8");

    Display display;
    display.Initialize();

    Debugger debug;
    debug.Initialize();

    while(!display.ShouldWindowClose())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        chip.Cycle();

        debug.PollEvents();
        display.Update(chip.display);
        debug.Update();
    }

    debug.Destroy();
    display.Destroy();
    return 0;
}