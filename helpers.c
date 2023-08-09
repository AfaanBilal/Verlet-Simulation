/**
 * Verlet Simulation of a Double Pendulum
 *
 * @author Afaan Bilal
 * @link   https://afaan.dev
 */

#include <math.h>
#include <SDL.h>

#include "definitions.h"

float distance(Vec2 p1, Vec2 p2) {
	float x = (p2.x - p1.x);
	float y = (p2.y - p1.y);
	return sqrt(x * x + y * y);
}

void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
	int diameter = radius * 2;
	int r2 = radius * radius;
	for (int w = 0; w < diameter; w++) {
		for (int h = 0; h < diameter; h++) {
			int dx = radius - w;
			int dy = radius - h;

			if ((dx * dx + dy * dy) <= r2) {
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}

void DrawRope(SDL_Renderer* renderer, Rope rope, Size p1s, Size p2s) {
	SDL_RenderDrawLineF(renderer,
		rope.p1.x + p1s.width / 2.0f,
		rope.p1.y + p1s.height / 2.0f,
		rope.p2.x + p2s.width / 2.0f,
		rope.p2.y + p2s.height / 2.0f
	);
}

void DrawPendulum(SDL_Renderer* renderer, Pendulum pendulum) {
	DrawCircle(renderer, pendulum.pos.x + pendulum.size.width / 2.0f, pendulum.pos.y + pendulum.size.height / 2.0f, pendulum.radius);
}
