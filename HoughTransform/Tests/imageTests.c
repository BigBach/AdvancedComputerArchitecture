#include <stdio.h>
#include <stdlib.h>
#include "./../imageUtilities.h"

int main(int argc, char** argv) {

	Pgm *imgIn = readPGM("image1.pgm");

	if(imgIn == NULL) {
		exit(2);
	}

	Pgm* imgOut = newPGM(imgIn->width, imgIn->height, imgIn->max_val);

	// copy the image
	copyPGM(imgIn, imgOut);
	writePGM(imgOut, "copy.pgm");

	// flip the image
	resetPGM(imgOut);
	hflipPGM(imgIn, imgOut);
	writePGM(imgOut, "flip.pgm");

	// invert the image
	resetPGM(imgOut);
	invertPGM(imgIn, imgOut);
	writePGM(imgOut, "invert.pgm");

	freePGM(&imgIn);
	freePGM(&imgOut);

	return 0;
}
