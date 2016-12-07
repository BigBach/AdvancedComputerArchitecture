#include <stdio.h>
#include <stdlib.h>
#include "./../sources/imageUtilities.h"
#include "./../sources/codeblocks_environment.h"

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

    freePGM(&imgIn);
    freePGM(&imgOut);

    return 0;
}
