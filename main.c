#include <stdio.h>
#include <SDL.h>

#include "constants.h"

int simulation_running = FALSE;
SDL_Window* window;
SDL_Renderer* renderer;

Uint64 last_frame_time = 0;

struct ball {
	float x;
	float y;
	float width;
	float height;
} ball;

int initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, ERROR_INITIALIZING_SDL);
		return FALSE;
	}

	window = SDL_CreateWindow(
		"Verlet Simulation",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0
	);
	if (!window) {
		fprintf(stderr, ERROR_CREATING_WINDOW);
		return FALSE;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, ERROR_CREATING_RENDERER);
		return FALSE;
	}

	return TRUE;
}

void cleanup() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		simulation_running = FALSE;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			simulation_running = FALSE;
		}
		break;
	}
}

void setup() {
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 15;
}

void update() {
	last_frame_time = SDL_GetTicks64();
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks64() - last_frame_time);
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}

	float delta_time = (SDL_GetTicks64() - last_frame_time) / 1000.0f;

	ball.x += 20 * delta_time;
	ball.y += 10 * delta_time;
}

void render() {
	SDL_SetRenderDrawColor(renderer, 112, 128, 144, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_Rect ball_rect = {
		(int)ball.x,
		(int)ball.y,
		(int)ball.width,
		(int)ball.height
	};
	SDL_SetRenderDrawColor(renderer, 18, 20, 23, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
	printf("Simulation starting...");
	printf("(c) Afaan Bilal (https://afaan.dev)");

	simulation_running = initialize_window();

	setup();

	while (simulation_running) {
		process_input();
		update();
		render();
	}

	cleanup();

	return 0;
}
