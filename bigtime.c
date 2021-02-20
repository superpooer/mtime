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
	struct Time offset;
	offset.hour = 0;
	offset.min = 0;
	offset.sec = 0;
	if(argc > 1){
		if(argc > 2)
			printhelp();
		int err = decipheroffset(&offset, argv[1]);
		switch(err){
			case 1:
				printf("invalid characters in offset input: %s\n", argv[1]);
				exit(2);
			case 2:
				printf("you broke my offset deciphering function with %s\n", argv[1]);
				exit(3);
		}
	}
	init();
	struct Time tm;
	readtime(&tm);
	addoffset(&tm, &offset);
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

int decipheroffset(struct Time *time, char *s){
	printf("in decipherinput s is = %s\n", s);
	int i = 0, pos = 0, neg = 0; //pos 0 = hour, 1 = min, 2 = sec, >2 || <0 = err
	while(1){
		printf("in while i is %i pos is %i s is %s\n", i, pos, s);
		switch(s[i]){
			case '+': case '0':
				++i;
				break;
			case '-':
				neg = 1;
				++i;
				break;
			case ':':
				++pos;
				++i;
				break;
			case '1': case '2':
			case '3': case '4':
			case '5': case '6':
			case '7': case '8':
			case '9':
				switch(pos){
					case 0:
						time->hour += (s[i] - CVT_ASC2INT);
						if((s[i+1] != 0) && (s[i+1] != ':'))
							time->hour *= 10;
						break;
					case 1:
						printf("before add time.min is %i\n", time->min);
						time->min += (s[i] - CVT_ASC2INT);
						if((s[i+1] != 0) && (s[i+1] != ':'))
							time->min *= 10;
						printf("after add time.min is %i\n", time->min);
						break;
					case 2:
						printf("before add time.sec is %i\n", time->sec);
						time->sec += (s[i] - CVT_ASC2INT);
						if(s[i+1] != 0)
							time->sec *= 10;
						printf("after add time.sec is %i\n", time->sec);
						break;
					default:
						return 2;
				}
				++i;
				break;
			case 0:
				goto end;
			default:
				return 1;
		}
	}
end:
	if(neg)
		if((time->hour >= 0) || (time->min >= 0) || (time->sec >= 0)){
			time->hour *= -1;
			time->min *= -1;
			time->sec *= -1;
		}
	printf("found EOL, returning\n");
	return 0;
}

void printhelp(){
	printf("usage: tm [offset]\n");
	printf("offset can be positive or negative in the format [-]h:m:s\n");
	exit(1);
}

void addoffset(struct Time *base, struct Time *off){
	base->hour += off->hour;
	base->min  += off->min;
	base->sec  += off->hour;
}
