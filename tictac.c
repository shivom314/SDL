#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define CELL_SIZE 350

char board[3][3];
char current_player;
int game_mode; // 1 for Single Player, 2 for Two Players

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void reset_board();
void draw_board();
void draw_mark(int row, int col);
void switch_player();
int check_winner();
int is_draw();
void handle_touch(int x, int y);
void computer_move();
int minimax(int is_maximizing);

int main(int argc, char*argv) {
    printf("Tic Tac Toe Game\n");
    printf("1. Single Player\n");
    printf("2. Two Players\n");
    printf("Choose mode (1 or 2): ");
    scanf_s("%d", &game_mode);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    reset_board();
    current_player = 'X';

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                handle_touch(x, y);
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        draw_board();
        SDL_RenderPresent(renderer);

        if (check_winner()) {
            printf("Player %c wins!\n", current_player);
            SDL_Delay(2000);
            reset_board();
        }
        else if (is_draw()) {
            printf("It's a draw!\n");
            SDL_Delay(2000);
            reset_board();
        }

        // If single-player mode and it's the computer's turn
        if (game_mode == 1 && current_player == 'O' && !check_winner() && !is_draw()) {
            computer_move();
            if (!check_winner() && !is_draw())
                switch_player();
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void reset_board() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    current_player = 'X';
}

void draw_board() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 1; i < 3; i++) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE);
    }

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] != ' ')
                draw_mark(row, col);
        }
    }
}

void draw_mark(int row, int col) {
    int x = col * CELL_SIZE + CELL_SIZE / 2;
    int y = row * CELL_SIZE + CELL_SIZE / 2;

    if (board[row][col] == 'X') {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, x - 20, y - 20, x + 20, y + 20);
        SDL_RenderDrawLine(renderer, x + 20, y - 20, x - 20, y + 20);
    }
    else if (board[row][col] == 'O') {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_Rect rect = { x - 20, y - 20, 40, 40 };
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void switch_player() {
    current_player = (current_player == 'X') ? 'O' : 'X';
}

int check_winner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == current_player && board[i][1] == current_player && board[i][2] == current_player)
            return 1;
        if (board[0][i] == current_player && board[1][i] == current_player && board[2][i] == current_player)
            return 1;
    }
    if (board[0][0] == current_player && board[1][1] == current_player && board[2][2] == current_player)
        return 1;
    if (board[0][2] == current_player && board[1][1] == current_player && board[2][0] == current_player)
        return 1;
    return 0;
}

int is_draw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void handle_touch(int x, int y) {
    int row = y / CELL_SIZE;
    int col = x / CELL_SIZE;

    if (row < 3 && col < 3 && board[row][col] == ' ') {
        board[row][col] = current_player;

        if (!check_winner() && !is_draw()) {
            switch_player();
        }
    }
}

// Always-winning strategy for the computer
void computer_move() {
    // If center is available, choose it as the best move
    if (board[1][1] == ' ') {
        board[1][1] = 'O';
        return;
    }

    // Winning move: Try to complete a row, column, or diagonal with two "O"s
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == ' ') { board[i][2] = 'O'; return; }
        if (board[i][0] == ' ' && board[i][1] == 'O' && board[i][2] == 'O') { board[i][0] = 'O'; return; }
        if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == ' ') { board[2][i] = 'O'; return; }
    }

    // Blocking move: Block player "X" from winning if two "X"s are in a row, column, or diagonal
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == ' ') { board[i][2] = 'O'; return; }
    }

    // Pick any remaining empty spot as a last resort
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') { board[i][j] = 'O'; return; }
}