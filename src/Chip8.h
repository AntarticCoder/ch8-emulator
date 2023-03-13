#pragma once
#include <cstdint>
#include <iostream>

#include "Common.h"

const unsigned int ROM_START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

const unsigned int FONTSET_SIZE = 80;

const uint8_t fontset[FONTSET_SIZE] = 
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2 
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3 
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4 
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80,// F
};

class Chip8
{
public:
	uint8_t memory[4096] = {};
	uint8_t registers[16] = {};
	uint16_t indexRegister;
	uint16_t stack[16] = {};
	uint16_t pc;
	uint8_t sp;

	uint32_t display[SCREEN_SIZE] = {};
	uint8_t keyboard[16] = {};

	uint8_t delayTimer;
	uint8_t soundTimer;

	uint16_t opcode;

	typedef void (Chip8::*Chip8Func)();
	Chip8Func table[0xF + 1];
	Chip8Func table0[0xE + 1];
	Chip8Func table8[0xE + 1];
	Chip8Func tableE[0xE + 1];
	Chip8Func tableF[0x65 + 1];
public:
	Chip8();
    void Initialize();
    void LoadRom(std::string path);
	void Cycle();

	void Table0() { ((*this).*(table0[opcode & 0x000Fu]))(); }
	void Table8() { ((*this).*(table8[opcode & 0x000Fu]))(); }
	void TableE() { ((*this).*(tableE[opcode & 0x000Fu]))(); }
	void TableF() { ((*this).*(tableF[opcode & 0x00FFu]))(); }

	void OPC_00E0();
	void OPC_00EE();
	void OPC_1nnn();
	void OPC_2nnn();
	void OPC_3xkk();
	void OPC_4xkk();
	void OPC_5xy0();
	void OPC_6xkk();
	void OPC_7xkk();
	void OPC_8xy0();
	void OPC_8xy1();
	void OPC_8xy2();
	void OPC_8xy3();
	void OPC_8xy4();
	void OPC_8xy5();
	void OPC_8xy6();
	void OPC_8xy7();
	void OPC_8xyE();
	void OPC_9xy0();
	void OPC_Annn();
	void OPC_Bnnn();
	void OPC_Cxkk();
	void OPC_Dxyn();
	void OPC_Ex9E();
	void OPC_ExA1();
	void OPC_Fx07();
	void OPC_Fx0A();
	void OPC_Fx15();
	void OPC_Fx18();
	void OPC_Fx1E();
	void OPC_Fx29();
	void OPC_Fx33();
	void OPC_Fx55();
	void OPC_Fx65();
	void OPC_NULL() {}
};