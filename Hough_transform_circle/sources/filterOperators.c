#include "filter.h"
#include "filterOperators.h"

PixelMatrix *cannyOperator(PixelMatrix *inputMatrix, double lowThreshold, double highTreshold)
{
    //1) Apply Gaussian to smooth the image in order to remove the noise
    Filter *gFilter = newFilter(5);
    gFilter->values[0] = (double)2/(double)159;
    gFilter->values[1] = (double)4/(double)159;
    gFilter->values[2] = (double)5/(double)159;
    gFilter->values[3] = (double)4/(double)159;
    gFilter->values[4] = (double)2/(double)159;
    gFilter->values[5] = (double)4/(double)159;
    gFilter->values[6] = (double)9/(double)159;
    gFilter->values[7] = (double)12/(double)159;
    gFilter->values[8] = (double)9/(double)159;
    gFilter->values[9] = (double)4/(double)159;
    gFilter->values[10] = (double)5/(double)159;
    gFilter->values[11] = (double)12/(double)159;
    gFilter->values[12] = (double)15/(double)159;
    gFilter->values[13] = (double)12/(double)159;
    gFilter->values[14] = (double)5/(double)159;
    gFilter->values[15] = (double)4/(double)159;
    gFilter->values[16] = (double)9/(double)159;
    gFilter->values[17] = (double)12/(double)159;
    gFilter->values[18] = (double)9/(double)159;
    gFilter->values[19] = (double)4/(double)159;
    gFilter->values[20] = (double)2/(double)159;
    gFilter->values[21] = (double)4/(double)159;
    gFilter->values[22] = (double)5/(double)159;
    gFilter->values[23] = (double)4/(double)159;
    gFilter->values[24] = (double)2/(double)159;

    PixelMatrix *inputMatrixExtended = convolution(extendsBorders(inputMatrix,2),gFilter);
    rescalePixels(inputMatrixExtended,getMinPixelValue(inputMatrixExtended),getMaxPixelValue(inputMatrixExtended),0.0,255.0);

    //2) Find the intensity gradients of the image
    Filter *iHFilter = newFilter(3);
    iHFilter->values[0] = -1;
    iHFilter->values[1] = 0;
    iHFilter->values[2] = 1;
    iHFilter->values[3] = (double)-sqrt(2);
    iHFilter->values[4] = 0;
    iHFilter->values[5] = (double)sqrt(2);
    iHFilter->values[6] = -1;
    iHFilter->values[7] = 0;
    iHFilter->values[8] = 1;
    Filter *iVFilter = newFilter(3);
    iVFilter->values[0] = -1;
    iVFilter->values[1] = -(double)sqrt(2);
    iVFilter->values[2] = -1;
    iVFilter->values[3] = 0;
    iVFilter->values[4] = 0;
    iVFilter->values[5] = 0;
    iVFilter->values[6] = 1;
    iVFilter->values[7] = (double)sqrt(2);
    iVFilter->values[8] = 1;
    PixelMatrix *inputMatrixExtendedTwo = extendsBorders(inputMatrixExtended,1);
    PixelMatrix *hMatrix = convolution(inputMatrixExtendedTwo,iHFilter);
    PixelMatrix *vMatrix = convolution(inputMatrixExtendedTwo,iVFilter);
    PixelMatrix *moduleMatrix = newPixelMatrix(hMatrix->width,hMatrix->height, PXM_NO_MAX_VALUE);
    int i;
    for(i = 0; i < moduleMatrix->width * moduleMatrix->height; i++)
    {
        moduleMatrix->values[i] = sqrt(pow(hMatrix->values[i],2) + pow(vMatrix->values[i],2));
    }
    PixelMatrix *phaseMatrix = newPixelMatrix(hMatrix->width,hMatrix->height, PXM_NO_MAX_VALUE);
    double theta,th1,th2,th3,th4,th5,th6,th7,th8;
    th1 = (double)M_PI_4 / (double)2;
    th2 = M_PI_4 + ((double)M_PI_4 / (double)2);
    th3 = M_PI_2 + ((double)M_PI_4 / (double)2);
    th4 = M_PI - ((double)M_PI_4 / (double)2);
    th5 = M_PI + ((double)M_PI_4 / (double)2);
    th6 = M_PI + M_PI_2 - ((double)M_PI_4 / (double)2);
    th7 = M_PI + M_PI_2 + ((double)M_PI_4 / (double)2);
    th8 = 2 * M_PI - ((double)M_PI_4 / (double)2);
    for(i = 0; i < phaseMatrix->width * phaseMatrix->height; i++)
    {
        theta = atan2(vMatrix->values[i],hMatrix->values[i]);
        if (theta < 0)
        {
            theta += 2 * M_PI;
        }
        if ((theta >= th1)&&(theta < th2))
        {
            theta = M_PI_4;
        }
        if ((theta >= th2)&&(theta < th3))
        {
            theta = M_PI_2;
        }
        if ((theta >= th3)&&(theta < th4))
        {
            theta = M_PI_2 + M_PI_4;
        }
        if ((theta >= th4)&&(theta < th5))
        {
            theta = 0.0;
        }
        if ((theta >= th5)&&(theta < th6))
        {
            theta = M_PI_4;
        }
        if ((theta >= th6)&&(theta < th7))
        {
            theta = M_PI_2;
        }
        if ((theta >= th7)&&(theta < th8))
        {
            theta = M_PI_2 + M_PI_4;
        }
        if (((theta >= th8)&&(theta < 2*M_PI)) || ((theta >= 0) && (theta < th1)))
        {
            theta = 0.0;
        }
        phaseMatrix->values[i] = theta;
    }

    //3) Apply non-maximum soppression to get rid of spurious response to edge detection
    int j, xPrev, xSucc, yPrev, ySucc, cIsMax;
    double phaseValue, moduleValue, minValue;
    minValue = getMinPixelValue(moduleMatrix);
    for(i = 0; i < moduleMatrix->height; i++)
    {
        for(j = 0; j < moduleMatrix->width; j++)
        {
            cIsMax = 1;
            moduleValue = moduleMatrix->values[i * moduleMatrix->width + j];
            phaseValue = phaseMatrix->values[i * phaseMatrix->width + j];
            if (phaseValue == 0.0)
            {
                xPrev = j - 1;
                yPrev = i;
                xSucc = j + 1;
                ySucc = i;
                if ((xPrev >= 0))
                {
                    if(moduleValue <= moduleMatrix->values[yPrev * moduleMatrix->width + xPrev])
                    {
                        cIsMax = 0;
                    }
                }
                if ((xSucc < phaseMatrix->width))
                {
                    if(moduleValue <= moduleMatrix->values[ySucc * moduleMatrix->width + xSucc])
                    {
                        cIsMax = 0;
                    }
                }
            }
            else if (phaseValue == M_PI_4)
            {
                xPrev = j - 1;
                yPrev = i + 1;
                xSucc = j + 1;
                ySucc = i - 1;
                if ((xPrev >= 0) && (yPrev < phaseMatrix->height))
                {
                    if(moduleValue <= moduleMatrix->values[yPrev * moduleMatrix->width + xPrev])
                    {
                        cIsMax = 0;
                    }
                }
                if ((xSucc < phaseMatrix->width) && (ySucc >= 0))
                {
                    if(moduleValue <= moduleMatrix->values[ySucc * moduleMatrix->width + xSucc])
                    {
                        cIsMax = 0;
                    }
                }
            }
            else if (phaseValue == M_PI_2)
            {
                xPrev = j;
                yPrev = i - 1;
                xSucc = j;
                ySucc = i + 1;
                if ((yPrev >= 0))
                {
                    if(moduleValue <= moduleMatrix->values[yPrev * moduleMatrix->width + xPrev])
                    {
                        cIsMax = 0;
                    }
                }
                if ((ySucc < phaseMatrix->height))
                {
                    if(moduleValue <= moduleMatrix->values[ySucc * moduleMatrix->width + xSucc])
                    {
                        cIsMax = 0;
                    }
                }
            }
            else if (phaseValue == M_PI_2 + M_PI_4)
            {
                xPrev = j - 1;
                yPrev = i - 1;
                xSucc = j + 1;
                ySucc = i + 1;
                if ((xPrev >= 0) && (yPrev >= 0))
                {
                    if(moduleValue <= moduleMatrix->values[yPrev * moduleMatrix->width + xPrev])
                    {
                        cIsMax = 0;
                    }
                }
                if ((xSucc < phaseMatrix->width) && (ySucc < phaseMatrix->height))
                {
                    if(moduleValue <= moduleMatrix->values[ySucc * moduleMatrix->width + xSucc])
                    {
                        cIsMax = 0;
                    }
                }
            }
            if (!cIsMax)
            {
                moduleMatrix->values[i * moduleMatrix->width + j] = minValue;
            }
        }
    }
    rescalePixels(moduleMatrix,getMinPixelValue(moduleMatrix),getMaxPixelValue(moduleMatrix),0.0,255.0);

    //Apply double threshold and track edges by hysteresis to determine potential edges
    for(i = 0; i < moduleMatrix->height; i++)
    {
        for(j = 0; j < moduleMatrix->width; j++)
        {
            moduleValue = moduleMatrix->values[i * moduleMatrix->width + j];
            if (moduleValue <= lowThreshold)
            {
                moduleMatrix->values[i * moduleMatrix->width + j] = 0.0;
            }
            else
            {
                if (moduleValue > highTreshold)
                {
                    moduleMatrix->values[i * moduleMatrix->width + j] = FO_STRONG_PIXEL;
                }
                else
                {
                    moduleMatrix->values[i * moduleMatrix->width + j] = FO_WEAK_PIXEL;
                }
            }
        }
    }
    int isStrong;
    for(i = 0; i < moduleMatrix->height; i++)
    {
        for(j = 0; j < moduleMatrix->width; j++)
        {
            isStrong = 0;
            moduleValue = moduleMatrix->values[i * moduleMatrix->width + j];
            if (moduleValue == FO_WEAK_PIXEL)
            {
                if ((i - 1) >= 0)
                {
                    if (moduleMatrix->values[(i-1)*moduleMatrix->width + j] == FO_STRONG_PIXEL)
                    {
                        isStrong = 1;
                    }
                }
                if ((i + 1) < moduleMatrix->height)
                {
                    if (moduleMatrix->values[(i+1)*moduleMatrix->width + j] == FO_STRONG_PIXEL)
                    {
                        isStrong = 1;
                    }
                }
                if ((j - 1) >= 0)
                {
                    if (moduleMatrix->values[i*moduleMatrix->width + j - 1] == FO_STRONG_PIXEL)
                    {
                        isStrong = 1;
                    }
                }
                if ((j + 1) >= 0)
                {
                    if (moduleMatrix->values[i*moduleMatrix->width + j + 1] == FO_STRONG_PIXEL)
                    {
                        isStrong = 1;
                    }
                }
                if (isStrong){
                    moduleMatrix->values[i*moduleMatrix->width + j] = FO_STRONG_PIXEL;
                }
            }
        }
    }

    return moduleMatrix;

}
