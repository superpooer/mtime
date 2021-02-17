/*
 * big analogue clock to show time nice and clear
 * 30 deg per hour (360/12)
 * we wont bother with non-12 hour clocks yet
 *
 * todo:
 * make border faint (escape code)
 * generalise for any clock size
 *
*/
#include "hdtime.h"


char bigclock[50][26];

int main(int argc, char **argv){
	init();
	struct Time tm;
	readtime(&tm);
	settime(tm);
	fancify();
	drawclock();
	return 0;
}

void init(){
	for(int x = 0; x <= WIDTH; ++x){			//going from top left
		for(int y = 0; y <= HEIGHT; ++y){
			bigclock[x][y] = ' ';
			if((x == 0) || (x == WIDTH) || (y == 0) || (y == WIDTH))
				bigclock[x][y] = C_BORDER;
		}
	}
	spawnnumbers();
}

void readtime(struct Time *t){
	time_t rawtime;
	struct tm *timef;
	time(&rawtime);
	timef = localtime(&rawtime);
	t->hour = timef->tm_hour;
	t->min  = timef->tm_min;
	t->sec  = timef->tm_sec;
}

void spawnnumbers(){
	bigclock[WIDTH-3][OG_Y]   = '3';
	bigclock[OG_X][HEIGHT-2]  = '6';
	bigclock[3][OG_Y]         = '9';
	bigclock[OG_X][2]         = 'C';

	bigclock[OG_X+11][OG_Y-9] = '1';
	bigclock[OG_X+18][OG_Y-5] = '2';
	bigclock[OG_X+18][OG_Y+5] = '4';
	bigclock[OG_X+11][OG_Y+9] = '5';
	bigclock[OG_X-11][OG_Y+9] = '7';
	bigclock[OG_X-18][OG_Y+5] = '8';
	bigclock[OG_X-18][OG_Y-5] = 'A';
	bigclock[OG_X-11][OG_Y-9] = 'B';
}

void drawclock(){
	for(int y = 0; y <= HEIGHT; ++y){
		for(int x = 0; x <= WIDTH; ++x){			//going from top left
			printf("%c", bigclock[x][y]);
		}
		printf("\n");
	}
}

double abs(double d){
	if(d > 0)
		return d;
	else return d*-1;
}

void fancify(){
	bigclock[(int)WIDTH/2][(int)HEIGHT/2] = C_ORIGIN;
}

void settime(struct Time tm){
	double minrad = ((double)(tm.min*6)) * d2r;
	double hourrad = ((double)(tm.hour*30)) * d2r;
	double mino = (double)tm.min;
	mino *= d2r;
	mino /= 2;
	hourrad += mino;
	double hs, hc, hts, htc, ms, mc, mts, mtc;
	hs = sin(hourrad);
	hc = cos(hourrad);
	ms = sin(minrad);
	mc = cos(minrad);
	for(int p = 0; p <= 20; ++p){			//mins
		mts = ms * p;
		mtc = mc * p/2;
		bigclock[OG_X+(int)mts][OG_Y-(int)mtc] = 'M'; // y goes top to bottom
	}
	for(int p = 0; p <= 16; ++p){			//hours
		hts = hs * p;
		htc = hc * p/2;
		bigclock[OG_X+(int)hts][OG_Y-(int)htc] = 'H'; // y goes top to bottom
	}
}
