#pragma once

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

float FromPixeltoBox2D(int pixels);

int FromBox2DtoPixel(float units);

enum class Direction { Up, Down, Left, Right };
