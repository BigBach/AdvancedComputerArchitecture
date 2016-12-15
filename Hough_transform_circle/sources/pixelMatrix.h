#ifndef PIXELMATRIX_H_INCLUDED
#define PIXELMATRIX_H_INCLUDED
#define PXM_NO_MAX_VALUE -1

typedef struct{
    double *values;
    int width;
    int height;
    double maxValue;
} PixelMatrix;

PixelMatrix *newPixelMatrix(int,int,int);

void freePixelMatrix(PixelMatrix *);

void setPixel(PixelMatrix *,int, double);

void rescalePixels(PixelMatrix *, double, double, double, double);

double rescalePixel(double, double, double, double, double);

double getMinPixelValue(PixelMatrix *);

double getMaxPixelValue(PixelMatrix *);

PixelMatrix *extendsBorders(PixelMatrix *, int);

PixelMatrix *extendsBordersWithZero(PixelMatrix *, int);

#endif // PIXELMATRIX_H_INCLUDED
