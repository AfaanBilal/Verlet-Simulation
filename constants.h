#pragma once

#define TRUE  1
#define FALSE 0

#define ERROR_INITIALIZING_SDL  "E0001: Error initializing SDL.\n"
#define ERROR_CREATING_WINDOW   "E0002: Error creating window.\n"
#define ERROR_CREATING_RENDERER "E0003: Error creating renderer.\n"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
