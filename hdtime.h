#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

const char C_BORDER = '*';
const char C_ORIGIN = 'o';
const char C_HOURHAND = 'H';
const char C_MINHAND = 'M';

const int HEIGHT = 26;  //characters are 8x16
const int WIDTH = 50;	  //ie have width be 2*height
const int OG_Y = 13;    //math.floor(HEIGHT/2) (zero-indexed)
const int OG_X = 25;    //math.floor(WIDTH/2) (zero-indexed)

const int CVT_ASC2INT = 48;

const double PI = 3.141592653589793238462643383;
const double d2r = PI/180;
const double r2d = 180/PI;

struct Time{
	int hour;
	int min;
	int sec;
};


void init();
void drawclock();
void spawnnumbers();
void readtime(struct Time *t);
void drawnumbers();
void settime(struct Time tm);
void fancify();
void printhelp();
void addoffset(struct Time *base, struct Time *off);

int decipheroffset(struct Time *time, char *s);
