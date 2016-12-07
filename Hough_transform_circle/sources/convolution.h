#ifndef CONVOLUTION_H_INCLUDED
#define CONVOLUTION_H_INCLUDED

typedef struct{
    int *values;
    int size;
} Filter;

PixelMatrix *convolution(int *, Filter *);

#endif // CONVOLUTION_H_INCLUDED


