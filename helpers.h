#pragma once
/**
 * Verlet Simulation of a Double Pendulum
 *
 * @author Afaan Bilal
 * @link   https://afaan.dev
 */

#include <SDL.h>

#include "definitions.h"

float distance(Vec2 p1, Vec2 p2);
void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
void DrawRope(SDL_Renderer* renderer, Rope rope, Size p1s, Size p2s);
void DrawPendulum(SDL_Renderer* renderer, Pendulum pendulum);
