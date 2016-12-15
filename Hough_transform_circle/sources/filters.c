#include "filters.h"


PixelMatrix **cannyOperator(PixelMatrix *inputMatrix, double lowThreshold, double highTreshold){
    Filter *gFilter = newFilter(5);
    gFilter->values[0] = 2/159;
    gFilter->values[1] = 4/159;
    gFilter->values[2] = 5/159;
    gFilter->values[3] = 4/159;
    gFilter->values[4] = 2/159;
    gFilter->values[5] = 4/159;
    gFilter->values[6] = 9/159;
    gFilter->values[7] = 12/159;
    gFilter->values[8] = 9/159;
    gFilter->values[9] = 4/159;
    gFilter->values[10] = 5/159;
    gFilter->values[11] = 12/159;
    gFilter->values[12] = 15/159;
    gFilter->values[13] = 12/159;
    gFilter->values[14] = 5/159;
    gFilter->values[15] = 4/159;
    gFilter->values[16] = 9/159;
    gFilter->values[17] = 12/159;
    gFilter->values[18] = 9/159;
    gFilter->values[19] = 4/159;
    gFilter->values[20] = 2/159;
    gFilter->values[21] = 4/159;
    gFilter->values[22] = 5/159;
    gFilter->values[23] = 4/159;
    gFilter->values[24] = 2/159;

    PixelMatrix *inputMatrixExtended = extendsBorders(inputMatrix,2);
    return &inputMatrixExtended;
}
