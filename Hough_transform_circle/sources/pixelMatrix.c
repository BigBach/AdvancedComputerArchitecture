#include "pixelMatrix.h"
#include <stdlib.h>

PixelMatrix *newPixelMatrix(int width, int height, int maxValue)
{
    PixelMatrix *p = (PixelMatrix*)malloc(1 * sizeof(PixelMatrix));
    p->width = width;
    p->height = height;
    p->maxValue = maxValue;
    p->values = (double*)calloc(width*height,sizeof(double));
    return p;
}

void freePixelMatrix(PixelMatrix *pixelMatrix)
{
    free(pixelMatrix->values);
    pixelMatrix->values = NULL;
    free(pixelMatrix);
    pixelMatrix = NULL;
}

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
    else
    {
        pixelMatrix->values[position] = value;
    }
}

void rescalePixels(PixelMatrix *pixelMatrix, double oldMinValue, double oldMaxValue, double newMinValue, double newMaxValue)
{
    int i;
    for(i = 0; i <(pixelMatrix->width * pixelMatrix->height); i++)
    {
        pixelMatrix->values[i] = rescalePixel(pixelMatrix->values[i],oldMinValue,oldMaxValue,newMinValue,newMaxValue);
    }
}

double rescalePixel(double pixel, double oldMinValue, double oldMaxValue, double newMinValue, double newMaxValue)
{
    return (((newMaxValue - newMinValue) * (pixel - oldMinValue)) / (oldMaxValue - oldMinValue));
}

double getMinPixelValue(PixelMatrix *pixelMatrix)
{
    double min = pixelMatrix->values[0];
    int i;
    for(i = 1; i < (pixelMatrix->width * pixelMatrix->height); i++)
    {
        if(pixelMatrix->values[i] < min)
        {
            min = pixelMatrix->values[i];
        }
    }
    return min;
}

double getMaxPixelValue(PixelMatrix *pixelMatrix)
{
    double max = pixelMatrix->values[0];
    int i;
    for(i = 1; i < (pixelMatrix->width * pixelMatrix->height); i++)
    {
        if(pixelMatrix->values[i] > max)
        {
            max = pixelMatrix->values[i];
        }
    }
    return max;
}


PixelMatrix *extendsBorders(PixelMatrix *pixelMatrix, int borderSize)
{
    PixelMatrix *outputMatrix = extendsBordersWithZero(pixelMatrix, borderSize);
    int i, j, filterSize;
    double pixel;
    filterSize = borderSize + 1;
    //Upper-left corner
    i = borderSize;
    j = borderSize;
    pixel = outputMatrix->values[i * outputMatrix->width + j];
    for(i = 0; i < filterSize; i++)
    {
        for(j = 0; j < filterSize; j++)
        {
            if ((i != borderSize) || (j != borderSize))
            {
                outputMatrix->values[i * outputMatrix->width + j] = pixel;
            }
        }

    }
    //Top border
    for(j = filterSize; j < (outputMatrix->width - filterSize); j++)
    {
        pixel = outputMatrix->values[borderSize * outputMatrix->width + j];
        for(i = 0; i < borderSize; i++)
        {
            outputMatrix->values[i * outputMatrix->width + j] = pixel;
        }
    }

    //Upper-right corner
    i = borderSize;
    j = outputMatrix->width - filterSize;
    pixel = outputMatrix->values[i * outputMatrix->width + j];
    for(i = 0; i < filterSize; i++)
    {
        for(j = 0; j < filterSize; j++)
        {
            if ((i != borderSize) || (j != borderSize))
            {
                outputMatrix->values[i * outputMatrix->width + outputMatrix->width - 1 - j] = pixel;
            }
        }

    }

    //Right border
    for(i = filterSize; i < (outputMatrix->height - borderSize); i++)
    {
        pixel = outputMatrix->values[i * outputMatrix->width + outputMatrix->width - filterSize];
        for(j = 0; j < borderSize; j++)
        {
            outputMatrix->values[i * outputMatrix->width + outputMatrix->width -1 - j] = pixel;
        }
    }

    //Lower-right corner
    i = outputMatrix->height -filterSize;
    j = outputMatrix->width - filterSize;
    pixel = outputMatrix->values[i * outputMatrix->width + j];
    for(i = 0; i < filterSize; i++)
    {
        for(j = 0; j < filterSize; j++)
        {
            if ((i != borderSize) || (j != borderSize))
            {
                outputMatrix->values[(outputMatrix->height -1 - i) * outputMatrix->width + outputMatrix->width - 1 - j] = pixel;
            }
        }

    }

    //Bottom border
    for(j = filterSize; j < (outputMatrix->width - filterSize); j++)
    {
        pixel = outputMatrix->values[(outputMatrix->height - 1 - borderSize) * outputMatrix->width + (outputMatrix->width - 1 - j)];
        for(i = 0; i < borderSize; i++)
        {
            outputMatrix->values[(outputMatrix->height - 1 - i) * outputMatrix->width + (outputMatrix->width - 1 - j)] = pixel;
        }
    }

    //Bottom-left corner
    i = outputMatrix->height -filterSize;
    j = borderSize;
    pixel = outputMatrix->values[i * outputMatrix->width + j];
    for(i = 0; i < filterSize; i++)
    {
        for(j = 0; j < filterSize; j++)
        {
            if ((i != borderSize) || (j != borderSize))
            {
                outputMatrix->values[(outputMatrix->height - 1 - i) * outputMatrix->width + j] = pixel;
            }
        }

    }

    //Left border
    for(i = filterSize - 1; i < (outputMatrix->height - filterSize); i++)
    {
        pixel = outputMatrix->values[(outputMatrix->height - 1 - i) * outputMatrix->width + filterSize];
        for(j = 0; j < borderSize; j++)
        {
            outputMatrix->values[(outputMatrix->height - 1 - i) * outputMatrix->width + j] = pixel;
        }
    }

    return outputMatrix;
}


PixelMatrix *extendsBordersWithZero(PixelMatrix *pixelMatrix, int borderSize)
{
    PixelMatrix *outputMatrix = newPixelMatrix(pixelMatrix->width + 2 * borderSize, pixelMatrix->height + 2 * borderSize,PXM_NO_MAX_VALUE);
    int i, displacemet;
    displacemet = 0;
    for(i = 0; i < (pixelMatrix->height * pixelMatrix->width); i++)
    {
        outputMatrix->values[i + borderSize * outputMatrix->width + borderSize + displacemet] = pixelMatrix->values[i];
        if(((i + 1) % pixelMatrix->width) == 0)
        {
            displacemet += (2 * borderSize + 1) -1;
        }
    }
    return outputMatrix;
}

