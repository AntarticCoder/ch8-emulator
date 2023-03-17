#include <vector>
#include <fstream>

#include "Chip8.h"

Chip8::Chip8()
{
    std::cout << "CHIP-8 Emulator starting\n";

    table[0x0] = &Chip8::Table0;
    table[0x1] = &Chip8::OPC_1nnn;
    table[0x2] = &Chip8::OPC_2nnn;
    table[0x3] = &Chip8::OPC_3xkk;
    table[0x4] = &Chip8::OPC_4xkk;
    table[0x5] = &Chip8::OPC_5xy0;
    table[0x6] = &Chip8::OPC_6xkk;
    table[0x7] = &Chip8::OPC_7xkk;
    table[0x8] = &Chip8::Table8;
    table[0x9] = &Chip8::OPC_9xy0;
    table[0xA] = &Chip8::OPC_Annn;
    table[0xB] = &Chip8::OPC_Bnnn;
    table[0xC] = &Chip8::OPC_Cxkk;
    table[0xD] = &Chip8::OPC_Dxyn;
    table[0xE] = &Chip8::TableE;
    table[0xF] = &Chip8::TableF;

    for (size_t i = 0; i <= 0xE; i++)
    {
        table0[i] = &Chip8::OPC_NULL;
        table8[i] = &Chip8::OPC_NULL;
        tableE[i] = &Chip8::OPC_NULL;
    }

    table0[0x0] = &Chip8::OPC_00E0;
    table0[0xE] = &Chip8::OPC_00EE;

    table8[0x0] = &Chip8::OPC_8xy0;
    table8[0x1] = &Chip8::OPC_8xy1;
    table8[0x2] = &Chip8::OPC_8xy2;
    table8[0x3] = &Chip8::OPC_8xy3;
    table8[0x4] = &Chip8::OPC_8xy4;
    table8[0x5] = &Chip8::OPC_8xy5;
    table8[0x6] = &Chip8::OPC_8xy6;
    table8[0x7] = &Chip8::OPC_8xy7;
    table8[0xE] = &Chip8::OPC_8xyE;

    tableE[0x1] = &Chip8::OPC_ExA1;
    tableE[0xE] = &Chip8::OPC_Ex9E;

    for (size_t i = 0; i <= 0x65; i++)
    {
        tableF[i] = &Chip8::OPC_NULL;
    }

    tableF[0x07] = &Chip8::OPC_Fx07;
    tableF[0x0A] = &Chip8::OPC_Fx0A;
    tableF[0x15] = &Chip8::OPC_Fx15;
    tableF[0x18] = &Chip8::OPC_Fx18;
    tableF[0x1E] = &Chip8::OPC_Fx1E;
    tableF[0x29] = &Chip8::OPC_Fx29;
    tableF[0x33] = &Chip8::OPC_Fx33;
    tableF[0x55] = &Chip8::OPC_Fx55;
    tableF[0x65] = &Chip8::OPC_Fx65;
}

void Chip8::Initialize()
{
    std::cout << "Initializing CHIP-8\n";

    std::fill(std::begin(memory), std::end(memory), 0);
    std::fill(std::begin(display), std::end(display), 0);

    delayTimer = 0;
    soundTimer = 0;

    pc = ROM_START_ADDRESS;
    opcode = 0;
    indexRegister = 0;
    sp = 0;

    for (int i = 0; i < FONTSET_SIZE; ++i)
    {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }
}

void Chip8::LoadRom(std::string path)
{
    std::cout << "Loading ROM\n";
    std::ifstream rom(path, std::ios::binary | std::ios::ate);

	if (!rom.is_open()) { std::cout << "Failed to load ROM from disk\n"; exit(EXIT_FAILURE); }

    std::streampos romSize = rom.tellg();
    char* buffer = new char[romSize];

    rom.seekg(0, std::ios::beg);
    rom.read(buffer, romSize);
    rom.close();

    for (long i = 0; i < romSize; ++i)
    {
        memory[ROM_START_ADDRESS + i] = buffer[i];
    }

    delete[] buffer;
} 
void Chip8::Cycle()
{
    opcode = (memory[pc] << 8u) | memory[pc + 1];
    pc += 2;

    ((*this).*(table[(opcode & 0xF000u) >> 12u]))();

	if (delayTimer > 0) { --delayTimer; }
    if (soundTimer > 0) { --soundTimer; }
}

void Chip8::OPC_00E0()
{
    std::fill(std::begin(display), std::end(display), 0);
}

void Chip8::OPC_00EE()
{
    --sp;
    pc = stack[sp];
}

void Chip8::OPC_1nnn()
{
    uint16_t address = opcode & 0x0FFFu;
    pc = address;
}

void Chip8::OPC_2nnn()
{
    uint16_t address = opcode & 0x0FFFu;
    
    stack[sp] = pc;
    ++sp;
    pc = address;
}

void Chip8::OPC_3xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    if(registers[Vx] == byte)
    {
        pc += 2;
    }
}

void Chip8::OPC_4xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    if(registers[Vx] != byte)
    {
        pc += 2;
    }
}

void Chip8::OPC_5xy0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if(registers[Vx] == registers[Vy])
    {
        pc += 2;
    }
}

void Chip8::OPC_6xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    registers[Vx] = byte;
}

void Chip8::OPC_7xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    registers[Vx] += byte;
}

void Chip8::OPC_8xy0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] = registers[Vy];
}

void Chip8::OPC_8xy1()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] |= registers[Vy];
}

void Chip8::OPC_8xy2()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] &= registers[Vy];
}

void Chip8::OPC_8xy3()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] ^= registers[Vy];
}

void Chip8::OPC_8xy4()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    uint16_t vSum = registers[Vx] + registers[Vy];

    if(vSum > 255u) 
    { 
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

    registers[Vx] = vSum & 0xFFu;
}

void Chip8::OPC_8xy5()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    uint16_t vSum = registers[Vx] + registers[Vy];

    if(registers[Vx] > registers[Vy]) 
    { 
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

    registers[Vx] -= registers[Vy];
}

void Chip8::OPC_8xy6()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    registers[0xF] = (registers[Vx] & 0x1u);
    registers[Vx] >>= 1;
}

void Chip8::OPC_8xy7()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if(registers[Vy] > registers[Vx]) 
    { 
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

    registers[Vx] = registers[Vy] - registers[Vx];
}

void Chip8::OPC_8xyE()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    registers[0xF] = (registers[Vx] & 0x80u) >> 7u;
    registers[Vx] <<= 1;
}

void Chip8::OPC_9xy0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if(registers[Vx] != registers[Vy])
    {
        pc += 2;
    }
}

void Chip8::OPC_Annn()
{
    uint16_t address = opcode & 0x0FFFu;
    indexRegister = address;
}

void Chip8::OPC_Bnnn()
{
    uint16_t address = opcode & 0x0FFFu;
    pc = registers[0] + address;
}

void Chip8::OPC_Cxkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    // Set Vx to random byte: TODO
    //registers[Vx] = randByte & byte;
}

void Chip8::OPC_Dxyn()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    uint8_t height = opcode & 0x000Fu;

    uint8_t xPos = registers[Vx] % SCREEN_WIDTH;
    uint8_t yPos = registers[Vy] % SCREEN_HEIGHT;

    registers[0xF] = 0;

    for(unsigned int row = 0; row < height; ++row)
    {
        uint8_t spriteByte = memory[indexRegister + row];

        for(unsigned int col = 0; col < 8; ++col)
        {
            uint8_t spritePixel = spriteByte & (0x80u >> col);
            uint32_t* screenPixel = &display[(yPos + row) * SCREEN_WIDTH + (xPos + col)];

            if (spritePixel)
            {
                if (*screenPixel == 0xFFFFFFFF)
                {
                    registers[0xF] = 1;
                }
                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }
}

void Chip8::OPC_Ex9E()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t key = registers[Vx];

    if (keyboard[key])
    {
        pc += 2;
    }
}

void Chip8::OPC_ExA1()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t key = registers[Vx];

    if(!keyboard[key])
    {
        pc += 2;
    }
}

void Chip8::OPC_Fx07()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    registers[Vx] = delayTimer;
}

void Chip8::OPC_Fx0A()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    if(keyboard[0])
    {
        registers[Vx] = 0;
    }
    else if(keyboard[1])
    {
        registers[Vx] = 1;
    }
    else if(keyboard[2])
    {
        registers[Vx] = 2;
    }
    else if(keyboard[3])
    {
        registers[Vx] = 3;
    }
    else if(keyboard[4])
    {
        registers[Vx] = 4;
    }
    else if(keyboard[5])
    {
        registers[Vx] = 5;
    }
    else if(keyboard[6])
    {
        registers[Vx] = 6;
    }
    else if(keyboard[7])
    {
        registers[Vx] = 7;
    }
    else if(keyboard[8])
    {
        registers[Vx] = 8;
    }
    else if(keyboard[9])
    {
        registers[Vx] = 9;
    }
    else if(keyboard[10])
    {
        registers[Vx] = 10;
    }
    else if(keyboard[11])
    {
        registers[Vx] = 11;
    }
    else if(keyboard[12])
    {
        registers[Vx] = 12;
    }
    else if(keyboard[13])
    {
        registers[Vx] = 13;
    }
    else if(keyboard[14])
    {
        registers[Vx] = 14;
    }
    else if(keyboard[15])
    {
        registers[Vx] = 15;
    }
    else
    {
        pc -= 2;
    }
}

void Chip8::OPC_Fx15()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    delayTimer = registers[Vx];
}

void Chip8::OPC_Fx18()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    soundTimer = registers[Vx];
}

void Chip8::OPC_Fx1E()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    indexRegister += registers[Vx];
}

void Chip8::OPC_Fx29()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t digit = registers[Vx];

    indexRegister = FONTSET_START_ADDRESS + (5 * digit);
}

void Chip8::OPC_Fx33()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t value = registers[Vx];

    memory[indexRegister + 2] = value % 10;
    value /= 10;

    memory[indexRegister + 1] = value % 10;
    value /= 10;

    memory[indexRegister] = value % 10;
}

void Chip8::OPC_Fx55()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    for (uint8_t i = 0; i <= Vx; ++i)
    {
        memory[indexRegister + i] = registers[i];
    }
}

void Chip8::OPC_Fx65()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    for (uint8_t i = 0; i <= Vx; ++i)
    {
        registers[i] = memory[indexRegister + i];
    }
}