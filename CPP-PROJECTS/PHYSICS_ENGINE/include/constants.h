#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 980;
constexpr int FPS = 120;

constexpr float GRAVITY = 9.81f;

constexpr float PIXEL_TO_METER = 1.0f / 6200.0f;	// Exact connection to the real screen size (in meters) with the number of pixels.
constexpr float METER_TO_PIXEL = 6200.0f;	// so, 6200 pixels represent 1 m, 620 pixels represent 10 cm, and 62 pixels represent 1 cm.

constexpr float SCALING = 0.1f;

#endif
