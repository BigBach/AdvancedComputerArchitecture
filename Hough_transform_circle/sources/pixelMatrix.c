#include "pixelMatrix.h"

void setPixel(PixelMatrix *pixelMatrix, int position, double value)
{
    if (pixelMatrix->maxValue >= 0)
    {
        if (value > pixelMatrix->maxValue)
        {
            pixelMatrix->values[position] = pixelMatrix->maxValue;
        }
        else
        {
            pixelMatrix->values[position] = value;
        }
    }
}
