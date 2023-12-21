#include <iostream>
#include <conio.h>
#include "snake_funcs.hpp"
#include <c:/SDL2/include/SDL.h>

using namespace std;

//Initializng game variables
void init() {
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fX = rand() % width;
    fY = rand() % height;
    tailLen = 0;
    Score = 0;
}


//Printing game state to screen
void Draw(SDL_Renderer* renderer) {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Drawing border to the buffer
    SDL_SetRenderDrawColor(renderer, 144, 238, 144, 255);
    SDL_Rect border = { 0, 0, width * 16, height * 16 };
    SDL_RenderDrawRect(renderer, &border);

    //Drawing snake's head to the buffer
    SDL_Rect head = { x * 16, y * 16, 16, 16 };
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
    SDL_RenderFillRect(renderer, &head);

    // Drawing snake's food to the buffer
    SDL_Rect food = { fX * 16, fY * 16, 16, 16 };
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
    SDL_RenderFillRect(renderer, &food);

    // Drawing snake's tail to the buffer
    for (int i = 0; i <= tailLen; i++) {
        SDL_Rect tail = { tailX[i] * 16, tailY[i] * 16, 16, 16 };
        SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
        SDL_RenderFillRect(renderer, &tail);
    }

    // Update screen
    SDL_RenderPresent(renderer);
}

//User input function
void Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isGameOver = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_w:
                sDir = STOP;
                sDir = UP;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                sDir = STOP;
                sDir = DOWN;
                break;
            case SDLK_LEFT:
            case SDLK_a:
                sDir = STOP;
                sDir = LEFT;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                sDir = STOP;
                sDir = RIGHT;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

//Game state update function
void update() {

    switch (sDir) {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    if (x == fX && y == fY) {
        Score += 10;
        fX = rand() % width;
        fY = rand() % height;
        tailLen++;
    }
    for (int i = tailLen; i > 0; i--) {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }

    tailX[0] = x;
    tailY[0] = y;
}

//Collision Detection
void collision() {
    if (tailLen > 0) {
        for (int i = 1; i <= tailLen; i++) {
            if (x == tailX[i] && y == tailY[i]) {
                isGameOver = true;
            }
        }
    }
    if (x == -1 || x == width || y == -1 || y == height) {
        isGameOver = true;
    }
}

//Game Over function
void gameOver() {
    cout << "Game Over!\n";
    cout << "Press any key to exit...";
    _getch();
}
