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


char bigclock[50][25];

int main(int argc, char **argv){
	printf("\n\n\n       sponge!\n\n");
	//init();
	//struct Time tm;
	//readtime(&tm);
	//settime(tm);
	//drawclock();
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
	bigclock[(int)WIDTH/2][(int)HEIGHT/2] = C_ORIGIN;
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


void settime(struct Time tm){
//	int mindeg = tm.min*6;
//	int hourdeg = tm.hour*30 + tm.min/2;
//	double xoff_m = round(sin(p2r*mindeg));
//	double yoff_m = round(cos(p2r*mindeg));
//	double xoff_h = round(sin(p2r*hourdeg));
//	double yoff_h = round(cos(p2r*hourdeg));
//	printf("\n%i:%i\n", tm.hour, tm.min);
//	printf("\nxoff_m = %f", xoff_m);
//	printf("\nyoff_m = %f", yoff_m);
//	printf("\nxoff_h = %f", xoff_h);
//	printf("\nyoff_h = %f", yoff_h);
//	for(int i = 0; i <= 20; ++i){
//		int abshx = (int)(xoff_h*i);
//		int abshy = (int)(yoff_h*i);
//		int absmx = (int)(xoff_m*i);
//		int absmy = (int)(yoff_m*i);
//		int hxplot = OG_X+abshx;
//		int hyplot = OG_Y-abshy;
//		int mxplot = OG_X+absmx;
//		int myplot = OG_Y-absmy;
//		if(!(sqrt(pow(abshx, 2) + pow(abshy, 2)) >= 8))
//			bigclock[hxplot][hyplot] = 'H';
//		if(!(sqrt(pow(absmx, 2) + pow(absmy, 2)) >= 10))
//			bigclock[mxplot][myplot] = 'M';
//	}
}
