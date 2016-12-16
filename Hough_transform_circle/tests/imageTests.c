#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./../sources/imageUtilities.h"
#include "./../sources/codeblocks_environment.h"
#include "./../sources/filter.h"
#include "./../sources/filterOperators.h"
#include <cv.h>
#include <highgui.h>
#include <time.h>

#define DEBUG printf("%s (%d): %s\n", __FILE__, __LINE__, __func__)


#ifdef CASONA

int main(int argc, char** argv)
{
    double *matrix = (double*)calloc(90000,sizeof(double));
    double tempo;
    clock_t inizio, fine;
    int i,j;

    inizio = clock();
    for(i = 0; i < 300; i++)
    {
        for(j = 0; j < 300; j++)
        {
            printf("%.2f",matrix[j * 300 + i]);
        }
    }
    fine = clock();
    tempo = (double)(fine - inizio)/(double) CLOCKS_PER_SEC;
    printf("%.2f", tempo);
}


#endif // CASONA

#ifdef CASETTINA

#include <cv.h>
#include <highgui.h>

int main(int argc, char** argv)
{
    IplImage* img = 0;
    img=cvLoadImage("./tests/image1.pgm", 1);
}


#endif // CASETTINA

int main(int argc, char** argv)
{

#ifdef CODEBLOCKS_ENVIRONMENT
    Pgm *imgIn = readPGM("./tests/image1.pgm");
#else
    Pgm *imgIn = readPGM("./image1.pgm");
#endif // CODEBLOCKS_ENVIRONMENT

    if(imgIn == NULL)
    {
        exit(2);
    }

    Pgm* imgOut = newPGM(imgIn->width, imgIn->height, imgIn->max_val);

    // copy the image
    copyPGM(imgIn, imgOut);
#ifdef CODEBLOCKS_ENVIRONMENT
    writePGM(imgOut, "./tests/copy.pgm");
#else
    writePGM(imgOut, "./copy.pgm");
#endif // CODEBLOCKS_ENVIRONMENT


    // flip the image
    resetPGM(imgOut);
    hflipPGM(imgIn, imgOut);
#ifdef CODEBLOCKS_ENVIRONMENT
    writePGM(imgOut, "./tests/flip.pgm");
#else
    writePGM(imgOut, "./flip.pgm");
#endif // CODEBLOCKS_ENVIRONMENT

    // invert the image
    resetPGM(imgOut);
    invertPGM(imgIn, imgOut);
#ifdef CODEBLOCKS_ENVIRONMENT
    writePGM(imgOut, "./tests/invert.pgm");
#else
    writePGM(imgOut, "./invert.pgm");
#endif // CODEBLOCKS_ENVIRONMENT

    freePGM(imgIn);
    freePGM(imgOut);


    //Convolution test
    Filter *filter = newFilter(3);
    filter->values[0] = -1;
    filter->values[1] = 0;
    filter->values[2] = 1;
    filter->values[3] = -sqrt(2);
    filter->values[4] = 0;
    filter->values[5] = sqrt(2);
    filter->values[6] = -1;
    filter->values[7] = 0;
    filter->values[8] = 1;

#ifdef CODEBLOCKS_ENVIRONMENT
    Pgm *inputPgm = readPGM("./tests/plettro.pgm");
#else
    Pgm *inputPgm = readPGM("./plettro.pgm");
#endif // CODEBLOCKS_ENVIRONMENT

    PixelMatrix *inputPMatrix = newPixelMatrix(inputPgm->width,inputPgm->height,inputPgm->max_val);
    int i;
    for(i = 0; i < (inputPMatrix->width*inputPMatrix->height); i++)
    {
        inputPMatrix->values[i] = (double)inputPgm->pixels[i];
    }

    PixelMatrix *pMatrix = convolution(inputPMatrix,filter);
    double oldMinValue = getMinPixelValue(pMatrix);
    double oldMaxValue = getMaxPixelValue(pMatrix);
    rescalePixels(pMatrix,oldMinValue,oldMaxValue,0.0,255.0);



    CvMat *out = cvCreateMat(pMatrix->height, pMatrix->width,CV_8UC3);
    int j, x;
    x = 0;
    for(i = 0; i < pMatrix->height; i++)
    {
        for(j = 0; j < pMatrix->width; j++)
        {
            x = i * pMatrix->width + j;
            CvScalar *scalar = (CvScalar*)malloc(1 * sizeof(CvScalar));
            scalar->val[0] = pMatrix->values[x];
            scalar->val[1] = pMatrix->values[x];
            scalar->val[2] = pMatrix->values[x];
            cvSet2D(out, i, j, *scalar);
        }
    }

    cvNamedWindow( "Display window", CV_WINDOW_AUTOSIZE );// Create a window for display.
    cvShowImage( "Display window", out );

    cvWaitKey(0);

    freeFilter(filter);
    freePGM(inputPgm);

    PixelMatrix *extendedInputMatrix = cannyOperator(inputPMatrix,100.0,180.0);
    DEBUG;
    CvMat *outExtended = cvCreateMat(extendedInputMatrix->height, extendedInputMatrix->width,CV_8UC3);
    DEBUG;
    x = 0;
    for(i = 0; i < extendedInputMatrix->height; i++)
    {
        for(j = 0; j < extendedInputMatrix->width; j++)
        {
            x = i * extendedInputMatrix->width + j;
            CvScalar *scalar = (CvScalar*)malloc(1 * sizeof(CvScalar));
            scalar->val[0] = extendedInputMatrix->values[x];
            scalar->val[1] = extendedInputMatrix->values[x];
            scalar->val[2] = extendedInputMatrix->values[x];
            cvSet2D(outExtended, i, j, *scalar);
        }
    }

    cvNamedWindow( "Display window", CV_WINDOW_AUTOSIZE );// Create a window for display.
    cvShowImage( "Display window", outExtended );

    cvWaitKey(0);


    freePixelMatrix(inputPMatrix);
    freePixelMatrix(extendedInputMatrix);

    return 0;
}



