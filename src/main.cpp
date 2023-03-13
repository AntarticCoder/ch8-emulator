#include <iostream>
#include <chrono>
#include <thread>

#include "Chip8.h"
#include "Display.h"

int main()
{
    std::cout << "CH8-Emulator starting up\n";

    Chip8 chip;
    chip.Initialize();
    chip.LoadRom("/Users/nick/Programming/ch8-emulator/roms/IBM.ch8");

    Display display;
    display.Initialize();

    while(!display.DisplayPollEvents())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        chip.Cycle();

        display.Update(chip.display);
    }

    display.Destroy();
    return 0;
}