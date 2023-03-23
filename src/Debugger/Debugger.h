#pragma once
#include <SDL2/SDL.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl2.h>
#include <imgui/backends/imgui_impl_sdlrenderer.h>

struct DebugInfo
{
	uint8_t registers[16];
	uint16_t indexRegister;
	uint16_t pc;

	uint8_t delayTimer;
	uint8_t soundTimer;

	uint16_t opcode;
};

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
    void Update(DebugInfo info);
    void Destroy();
};