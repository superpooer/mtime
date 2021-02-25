#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

const char C_BORDER = '*';
const char C_ORIGIN = 'o';
const char C_HOURHAND = '.';
const char C_MINHAND = '#';

const int HEIGHT = 26;  //characters are 8x16
const int WIDTH = 50;	  //ie have width be 2*height
const int OG_Y = 13;    //math.floor(HEIGHT/2) (zero-indexed)
const int OG_X = 25;    //math.floor(WIDTH/2) (zero-indexed)
const int MARKER_RAD_X = 22; //(HEIGHT/2) - 3
const int MARKER_RAD_Y = 11; //(WIDTH/2) - 2
const int MIN_LEN = 20;  //MARKER_RAD_Y * 9/10   hand lengths
const int HOUR_LEN = 16; //MARKER_RAD_Y * 2/3   hand lengths

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
