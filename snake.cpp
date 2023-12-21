#include <iostream>
#include <conio.h>
#include "snake_funcs.hpp"
#include <SDL2/SDL.h>

//Variables 
direction sDir = STOP;
char buffer[width + 2][height + 2];
int x, y;
int fX, fY;
int Score;
int tailX[100], tailY[100];
int tailLen;
bool isGameOver;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;


int main() {
    //Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //Creating the window
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }


    init();
    //Main game loop
    while (!isGameOver) {
        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        Draw(renderer);
        Input();
        update();
        collision();

        // Update screen
        SDL_RenderPresent(renderer);
    }

    Draw(renderer);

    // Destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return 0;
}