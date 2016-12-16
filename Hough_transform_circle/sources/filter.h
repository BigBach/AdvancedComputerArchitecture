#ifndef CONVOLUTION_H_INCLUDED
#define CONVOLUTION_H_INCLUDED
#include "./pixelMatrix.h"
#include <stdlib.h>

typedef struct{
    double *values;
    int size;
} Filter;

Filter *newFilter(int);

void freeFilter(Filter *);

PixelMatrix *convolution(PixelMatrix *, Filter *);


#endif // CONVOLUTION_H_INCLUDED


