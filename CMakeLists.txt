cmake_minimum_required(VERSION 3.0)
project(chip8-emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) 

add_compile_options(-g)

find_package(SDL2 REQUIRED)

file(GLOB IMGUI_FILES 
    ${CMAKE_SOURCE_DIR}/libs/imgui/*.cpp 
)

add_executable(ch8-emulator 
    ${IMGUI_FILES}
    ${CMAKE_SOURCE_DIR}/libs/imgui/backends/imgui_impl_sdl2.cpp
    ${CMAKE_SOURCE_DIR}/libs/imgui/backends/imgui_impl_sdlrenderer.cpp

    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Chip8/Chip8.cpp
    ${CMAKE_SOURCE_DIR}/src/Display/Display.cpp
    ${CMAKE_SOURCE_DIR}/src/Debugger/Debugger.cpp
)

target_include_directories(ch8-emulator  PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/libs
    ${CMAKE_SOURCE_DIR}/libs/imgui
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(ch8-emulator PUBLIC ${SDL2_LIBRARIES})
