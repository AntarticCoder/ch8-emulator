#include <Debugger/Debugger.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl2.h>
#include <imgui/backends/imgui_impl_sdlrenderer.h>

void Debugger::Initialize()
{
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("CHIP-8 Emulator Debugger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, windowFlags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); 
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);
}

void Debugger::Update()
{
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowSize(ImVec2(io->DisplaySize.x, io->DisplaySize.y));
    ImGui::SetNextWindowPos(ImVec2(0,0));

    bool demo = true;
    ImGui::ShowDemoWindow(&demo);

    ImGui::Render();
    SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, (Uint8)(0), (Uint8)(0), (Uint8)(0), (Uint8)(0));
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}

void Debugger::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Debugger::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if(event.window.windowID == SDL_GetWindowID(window)) { ImGui_ImplSDL2_ProcessEvent(&event); }
    }
}