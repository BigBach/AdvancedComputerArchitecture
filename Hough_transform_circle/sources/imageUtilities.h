#ifndef _IMAGEUTILITY
#define _IMAGEUTILITY
//---------------------------------------------------------//
//------------------ Standard includes --------------------//
//---------------------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int width;
	int height;
	int max_val;
	int* pixels;
} Pgm;

//---------------------------------------------------------//
//------------ Input/Output Functions for PGM -------------//
//---------------------------------------------------------//
void skipComments(char*, FILE*);
Pgm* newPGM(int, int, int);
Pgm* readPGM(char*);
int writePGM(Pgm*, char*);
void resetPGM(Pgm*);
void freePGM(Pgm*);

//---------------------------------------------------------//
//----------------- Basic Functions for PGM ---------------//
//---------------------------------------------------------//
int invertPGM(Pgm*, Pgm*);
int hflipPGM(Pgm*, Pgm*);
int copyPGM(Pgm*, Pgm*);
int* histogramPGM(Pgm*);

#endif
