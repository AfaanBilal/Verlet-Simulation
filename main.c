/**
 * Verlet Simulation of a Double Pendulum
 *
 * @author Afaan Bilal
 * @link   https://afaan.dev
 */

#include <stdio.h>
#include <SDL.h>
#include <math.h>

#include "constants.h"
#include "definitions.h"
#include "helpers.h"

int simulation_running = FALSE;
SDL_Window* window;
SDL_Renderer* renderer;

Uint64 last_frame_time = 0;

Rect anchor = { { WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 - 300 }, { 10, 10 } };
Rope rope;
Pendulum pendulum = {
	{ WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 2 - 50 },
	{ WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 2 - 50 },
	{ 20, 20 },
	20
};
Rope rope2;
Pendulum pendulum2 = {
	{ WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT / 2 + 200 },
	{ WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT / 2 + 200 },
	{ 20, 20 },
	20
};

int initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, ERROR_INITIALIZING_SDL);
		return FALSE;
	}

	window = SDL_CreateWindow(
		"Verlet Simulation (https://afaan.dev)",
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
	rope.p1 = anchor.pos;
	rope.p2 = pendulum.pos;
	rope.length = distance(rope.p1, rope.p2);

	rope2.p1 = pendulum.pos;
	rope2.p2 = pendulum2.pos;
	rope2.length = distance(rope2.p1, rope2.p2);
}

void maintainRopeLength(Rope* rope) {
	float dx = rope->p1.x - rope->p2.x;
	float dy = rope->p1.y - rope->p2.y;

	float dist = sqrt(dx * dx + dy * dy);
	float diff = rope->length - dist;

	float percent = (diff / dist) / 2;

	float offset_x = dx * percent;
	float offset_y = dy * percent;

	rope->p2.x -= offset_x;
	rope->p2.y -= offset_y;
}

void update() {
	last_frame_time = SDL_GetTicks64();
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks64() - last_frame_time);
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}

	float delta_time = (SDL_GetTicks64() - last_frame_time) / 1000.0f;

	float acc_x = 0;
	float acc_y = GRAVITY;

	float vel_x = pendulum.pos.x - pendulum.pos_old.x;
	float vel_y = pendulum.pos.y - pendulum.pos_old.y;

	pendulum.pos_old.x = pendulum.pos.x;
	pendulum.pos_old.y = pendulum.pos.y;

	rope.p2.x += vel_x + acc_x * delta_time * delta_time;
	rope.p2.y += vel_y + acc_y * delta_time * delta_time;

	maintainRopeLength(&rope);

	pendulum.pos.x = rope.p2.x;
	pendulum.pos.y = rope.p2.y;

	// Rope 2 (between Pendulum 1 and 2) - rigid
	rope2.p1.x = rope.p2.x;
	rope2.p1.y = rope.p2.y;

	float vel2_x = pendulum2.pos.x - pendulum2.pos_old.x;
	float vel2_y = pendulum2.pos.y - pendulum2.pos_old.y;

	pendulum2.pos_old.x = pendulum2.pos.x;
	pendulum2.pos_old.y = pendulum2.pos.y;

	rope2.p2.x += vel2_x + acc_x * delta_time * delta_time;
	rope2.p2.y += vel2_y + acc_y * delta_time * delta_time;

	maintainRopeLength(&rope2);

	pendulum2.pos.x = rope2.p2.x;
	pendulum2.pos.y = rope2.p2.y;
}

void render() {
	SDL_SetRenderDrawColor(renderer, 112, 128, 144, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 20, 20, 20, SDL_ALPHA_OPAQUE);

	SDL_Rect anchor_r = {
		(int)anchor.pos.x,
		(int)anchor.pos.y,
		(int)anchor.size.width,
		(int)anchor.size.height
	};

	SDL_RenderFillRect(renderer, &anchor_r);

	DrawRope(renderer, rope, anchor.size, pendulum.size);
	DrawPendulum(renderer, pendulum);

	DrawRope(renderer, rope2, pendulum.size, pendulum2.size);
	DrawPendulum(renderer, pendulum2);

	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
	printf("Simulation starting...\n");
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
