#include <string>

#include <Debugger/Debugger.h>

void Debugger::StartFrame()
{
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();
}

void Debugger::EndFrame()
{
    ImGui::Render();
    SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, (Uint8)(0), (Uint8)(0), (Uint8)(0), (Uint8)(0));
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}

void Debugger::Initialize()
{
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("CHIP-8 Emulator Debugger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, windowFlags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); 
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io->Fonts->AddFontFromFileTTF("/Users/nick/Programming/ch8-emulator/assets/fonts/Source_Code_Pro/static/SourceCodePro-SemiBold.ttf", 18);

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);
}

void Debugger::Update(Chip8 chip)
{
    StartFrame();

    ImGui::Begin("Registers");
    ImGui::Text("V0: %X", chip.registers[0]);
    ImGui::Text("V1: %X", chip.registers[1]);
    ImGui::Text("V2: %X", chip.registers[2]);
    ImGui::Text("V3: %X", chip.registers[3]);
    ImGui::Text("V4: %X", chip.registers[4]);
    ImGui::Text("V5: %X", chip.registers[5]);
    ImGui::Text("V6: %X", chip.registers[6]);
    ImGui::Text("V7: %X", chip.registers[7]);
    ImGui::Text("V8: %X", chip.registers[8]);
    ImGui::Text("V9: %X", chip.registers[9]);
    ImGui::Text("VA: %X", chip.registers[10]);
    ImGui::Text("VB: %X", chip.registers[11]);
    ImGui::Text("VC: %X", chip.registers[12]);
    ImGui::Text("VD: %X", chip.registers[13]);
    ImGui::Text("VE: %X", chip.registers[14]);
    ImGui::Text("VF: %X", chip.registers[15]);
    ImGui::End();

    ImGui::Begin("Timers");
    ImGui::Text("General Timer: %i", chip.delayTimer);
    ImGui::Text("Sound Timer: %i", chip.soundTimer);
    ImGui::End();

    EndFrame();
}

void Debugger::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}