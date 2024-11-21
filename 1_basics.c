#include <SDL.h>

#define WINDOWWIDTH 400
#define WINDOWHEIGHT 300

int main(int argc, char** argv) {

	// 1 | Initiate SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// 2 | making window (paper)
	SDL_Window* window1 = SDL_CreateWindow("mytitle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SKIP_TASKBAR);

	// 3 | Renderer (pen)
	SDL_Renderer* renderer1 = SDL_CreateRenderer(window1, -1, SDL_RENDERER_ACCELERATED);

	// 4 | setting color of pen
	SDL_SetRenderDrawColor(renderer1, 0, 255, 0, 255);

	// 5| clear waste in renderer
	SDL_RenderClear(renderer1);

	// 6 | presenting screen
	SDL_RenderPresent(renderer1);

	// 7 | Delay 
	SDL_Delay(5000);

	// 8 | Destroy all things
	SDL_DestroyRenderer(renderer1);
	SDL_DestroyWindow(window1);
	SDL_Quit();


}