#ifndef FILTERS_H_INCLUDED
#define FILTERS_H_INCLUDED
#define FO_STRONG_PIXEL 255
#define FO_WEAK_PIXEL 254
#include "filter.h"
#include <math.h>

PixelMatrix *cannyOperator(PixelMatrix *, double, double);



#endif // FILTERS_H_INCLUDED
