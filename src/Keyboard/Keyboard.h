#pragma once
#include <SDL2/SDL.h>

#include <Chip8/Chip8.h>

class Keyboard
{
public:
    static void ProcessKeyDown(Chip8 chip, SDL_Keycode code)
    {
        switch(code)
        {
            case SDLK_1: 
                chip.keyboard[0] = true;
            case SDLK_2: 
                chip.keyboard[1] = true;
            case SDLK_3: 
                chip.keyboard[2] = true;
            case SDLK_4: 
                chip.keyboard[3] = true;

            case SDLK_q: 
                chip.keyboard[4] = true;
            case SDLK_w: 
                chip.keyboard[5] = true;
            case SDLK_e: 
                chip.keyboard[6] = true;
            case SDLK_r: 
                chip.keyboard[7] = true;

            case SDLK_a: 
                chip.keyboard[8] = true;
            case SDLK_s: 
                chip.keyboard[9] = true;
            case SDLK_d: 
                chip.keyboard[10] = true;
            case SDLK_f: 
                chip.keyboard[11] = true;

            case SDLK_z: 
                chip.keyboard[12] = true;
            case SDLK_x: 
                chip.keyboard[13] = true;
            case SDLK_c: 
                chip.keyboard[14] = true;
            case SDLK_v: 
                chip.keyboard[15] = true;
        };
    }

    static void ProcessKeyUp(Chip8 chip, SDL_Keycode code)
    {
        switch(code)
        {
            case SDLK_1: 
                chip.keyboard[0] = false;
            case SDLK_2: 
                chip.keyboard[1] = false;
            case SDLK_3: 
                chip.keyboard[2] = false;
            case SDLK_4: 
                chip.keyboard[3] = false;

            case SDLK_q: 
                chip.keyboard[4] = false;
            case SDLK_w: 
                chip.keyboard[5] = false;
            case SDLK_e: 
                chip.keyboard[6] = false;
            case SDLK_r: 
                chip.keyboard[7] = false;

            case SDLK_a: 
                chip.keyboard[8] = false;
            case SDLK_s: 
                chip.keyboard[9] = false;
            case SDLK_d: 
                chip.keyboard[10] = false;
            case SDLK_f: 
                chip.keyboard[11] = false;

            case SDLK_z: 
                chip.keyboard[12] = false;
            case SDLK_x: 
                chip.keyboard[13] = false;
            case SDLK_c: 
                chip.keyboard[14] = false;
            case SDLK_v: 
                chip.keyboard[15] = false;
        };
    }
};