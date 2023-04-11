#pragma once
#include <SDL2/SDL.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl2.h>
#include <imgui/backends/imgui_impl_sdlrenderer.h>

#include <Chip8/Chip8.h>

class Debugger
{
private:
    SDL_Renderer* renderer;
    ImGuiIO* io;

    void StartFrame();
    void EndFrame();
public:
     SDL_Window* window;

    void Initialize();
    void Update(Chip8 chip);
    void Destroy();
};