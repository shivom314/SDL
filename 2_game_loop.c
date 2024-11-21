#include<SDL.h>
#include <stdbool.h>

#define WINDOWWIDTH 800 
#define WINDOWHEIGHT 600 

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window1 = SDL_CreateWindow("legacy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer1 = SDL_CreateRenderer(window1, -1, SDL_RENDERER_ACCELERATED);

	// game loop

	SDL_Event event1;
	bool running = true;
	while (running) {

		// enabling user exit
		while (SDL_PollEvent(&event1)) {
			if (event1.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_SetRenderDrawColor(renderer1, 255, 255, 255, 255);
		SDL_RenderClear(renderer1);
		SDL_RenderPresent(renderer1);
	}
	SDL_DestroyRenderer(renderer1);
	SDL_DestroyWindow(window1);
	SDL_Quit();
	
	return 0;
}