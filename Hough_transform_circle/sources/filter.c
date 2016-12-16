#include "filter.h"

Filter *newFilter(int size){
    Filter *f = (Filter*)malloc(1 * sizeof(Filter));
    f->size = size;
    f->values = (double*)calloc(size * size, sizeof(double));
    return f;
}


void freeFilter(Filter *filter){
    free(filter->values);
    free(filter);
}


PixelMatrix *convolution(PixelMatrix *pixelMatrix, Filter *filter)
{

    PixelMatrix *outPixelMatrix = (PixelMatrix*)malloc(1 * sizeof(PixelMatrix));
    outPixelMatrix->width = pixelMatrix->width - filter->size + 1;
    outPixelMatrix->height = pixelMatrix->height - filter->size + 1;
    outPixelMatrix->maxValue = -1.0;
    outPixelMatrix->values = malloc(sizeof(double) * outPixelMatrix->width * outPixelMatrix->height);
    int x = 0;
    int i;
    int j;
    int endForI = (pixelMatrix->width * pixelMatrix->height) - (filter->size - 1) * pixelMatrix->width - (filter->size - 1);
    int endForJ = filter->size * filter->size;
    for(i = 0; i < endForI; i++)
    {
        double pixel = 0.0;
        for(j = 0; j < endForJ; j++){
            pixel += pixelMatrix->values[i] * filter->values[j];
            if(((j + 1) % filter->size) == 0){
                i += pixelMatrix->width - (filter->size - 1);
            } else{
                i++;
            }
        }
        setPixel(outPixelMatrix,x,pixel);
        x++;
        i = i - filter->size * pixelMatrix->width;
        if ((((i + (filter->size - 1)) + 1) % pixelMatrix->width) == 0){
            i += ((filter->size - 1));
        }
    }
    return outPixelMatrix;
}
