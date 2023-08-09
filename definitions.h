#pragma once
/**
 * Verlet Simulation of a Double Pendulum
 *
 * @author Afaan Bilal
 * @link   https://afaan.dev
 */

typedef struct Vec2 {
	float x;
	float y;
} Vec2;

typedef struct Size {
	int width;
	int height;
} Size;

typedef struct Rect {
	Vec2 pos;
	Size size;
} Rect;

typedef struct Rope {
	Vec2 p1;
	Vec2 p2;
	float length;
} Rope;

typedef struct Pendulum {
	Vec2 pos_old;
	Vec2 pos;
	Size size;
	float radius;
	float length;
} Pendulum;
