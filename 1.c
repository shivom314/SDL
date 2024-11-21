#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

typedef enum { EMPTY, PLAYER_X, PLAYER_O } Cell;
Cell** board;
int n;
int currentPlayer;

void drawBoard(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    SDL_RenderClear(renderer);

    int cellSize = WINDOW_WIDTH / n;

    // Draw grid
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Black
    for (int i = 1; i < n; i++) {
        SDL_RenderDrawLine(renderer, 0, i * cellSize, WINDOW_WIDTH, i * cellSize);
        SDL_RenderDrawLine(renderer, i * cellSize, 0, i * cellSize, WINDOW_HEIGHT);
    }

    // Draw Xs and Os
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (board[y][x] == PLAYER_X) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Red for X
                SDL_RenderDrawLine(renderer, x * cellSize, y * cellSize,
                    (x + 1) * cellSize, (y + 1) * cellSize);
                SDL_RenderDrawLine(renderer, (x + 1) * cellSize, y * cellSize,
                    x * cellSize, (y + 1) * cellSize);
            }
            else if (board[y][x] == PLAYER_O) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for O
                int centerX = x * cellSize + cellSize / 2;
                int centerY = y * cellSize + cellSize / 2;
                for (int r = 0; r < cellSize / 4; r++) {
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
    int gridX = x / (WINDOW_WIDTH / n);
    int gridY = y / (WINDOW_HEIGHT / n);
    if (gridX < n && gridY < n && board[gridY][gridX] == EMPTY) {
        board[gridY][gridX] = (currentPlayer == 0) ? PLAYER_X : PLAYER_O;
        currentPlayer = 1 - currentPlayer; // Switch player
    }
}

int main() {
    printf("Enter the size of the Tic Tac Toe grid (n x n): ");
    scanf("%d",&n);

    // Allocate memory for the board
    board = malloc(n * sizeof(Cell*));
    for (int i = 0; i < n; i++) {
        board[i] = malloc(n * sizeof(Cell));
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    currentPlayer = 0; // Player X starts
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j]=EMPTY;
        }
    }

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

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
