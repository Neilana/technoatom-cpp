#include "constants.h"

float FromPixeltoBox2D(int pixels)
{
    return static_cast<float>(pixels/16);
}

int FromBox2DtoPixel(float units)
{
    return static_cast<int>(units * 16);
}
