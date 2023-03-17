#pragma once
#include <SDL2/SDL.h>
#include <imgui/imgui.h>

class Debugger
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    ImGuiIO* io;
public:
    void Initialize();
    void Update();
    void Destroy();

    void PollEvents();
};