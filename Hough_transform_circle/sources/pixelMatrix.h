#ifndef PIXELMATRIX_H_INCLUDED
#define PIXELMATRIX_H_INCLUDED

typedef struct{
    double *values;
    int width;
    int heigth;
    double maxValue;
} PixelMatrix;

void setPixel(PixelMatrix *,int, double);

#endif // PIXELMATRIX_H_INCLUDED
