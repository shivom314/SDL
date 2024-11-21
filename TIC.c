#include <SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300
#define CELL_SIZE 100

typedef enum { EMPTY, PLAYER_X, PLAYER_O } Cell;
Cell board[3][3];
int currentPlayer;

void drawBoard(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255); // White
    SDL_RenderClear(renderer);

    // Draw grid
    SDL_SetRenderDrawColor(renderer, 0, 0, 0,255); // Black
    for (int i = 1; i < 3; i++) {
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, WINDOW_WIDTH, i * CELL_SIZE);
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_HEIGHT);
    }

    // Draw Xs and Os
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[y][x] == PLAYER_X) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0,255); // Red for X
                SDL_RenderDrawLine(renderer, x * CELL_SIZE, y * CELL_SIZE,
                    (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
                SDL_RenderDrawLine(renderer, (x + 1) * CELL_SIZE, y * CELL_SIZE,
                    x * CELL_SIZE, (y + 1) * CELL_SIZE);
            }
            else if (board[y][x] == PLAYER_O) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255,255); // Blue for O
                int centerX = x * CELL_SIZE + CELL_SIZE / 2;
                int centerY = y * CELL_SIZE + CELL_SIZE / 2;
                for (int r = 0; r < CELL_SIZE / 4; r++) {
                    SDL_RenderDrawPoint(renderer, centerX + r, centerY);
                    SDL_RenderDrawPoint(renderer, centerX - r, centerY);
                    SDL_RenderDrawPoint(renderer, centerX, centerY + r);
                    SDL_RenderDrawPoint(renderer, centerX, centerY - r);
                }
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void handleClick(int x, int y) {
    int gridX = x / CELL_SIZE;
    int gridY = y / CELL_SIZE;
    if (gridX < 3 && gridY < 3 && board[gridY][gridX] == EMPTY) {
        board[gridY][gridX] = (currentPlayer == 0) ? PLAYER_X : PLAYER_O;
        currentPlayer = 1 - currentPlayer; // Switch player
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    currentPlayer = 0; // Player X starts
    memset(board, EMPTY, sizeof(board));

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                handleClick(event.button.x, event.button.y);
            }
        }
        drawBoard(renderer);
        SDL_Delay(100); // Limit frame rate
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}