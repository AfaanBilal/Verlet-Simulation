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

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void DrawRope(SDL_Renderer* renderer, Rope rope, Size p1s, Size p2s) 
{
	SDL_RenderDrawLineF(renderer,
		rope.p1.x + p1s.width / 2.0f,
		rope.p1.y + p1s.height / 2.0f,
		rope.p2.x + p2s.width / 2.0f,
		rope.p2.y + p2s.height / 2.0f
	);
}

void DrawPendulum(SDL_Renderer* renderer, Pendulum pendulum)
{
	DrawCircle(renderer, pendulum.pos.x + pendulum.size.width / 2.0f, pendulum.pos.y + pendulum.size.height / 2.0f, pendulum.radius);
}
