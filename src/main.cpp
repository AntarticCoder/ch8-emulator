#include <iostream>
#include <chrono>
#include <thread>

#include "Chip8.h"

int main()
{
    std::cout << "CH8-Emulator starting up\n";

    Chip8 chip;
    chip.Initialize();
    chip.LoadRom("/Users/nick/Programming/ch8-emulator/roms/test_opcode.ch8");

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));

        std::cout << "CH8-Emulator emulating cycle\n";
        chip.Cycle();
    }
    return 0;
}