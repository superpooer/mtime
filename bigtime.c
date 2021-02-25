/*
 * big analogue clock to show time nice and clear
 * 30 deg per hour (360/12)
 * we wont bother with non-12 hour clocks yet
 *
 * todo:
 * make border faint and add colours with escape codes
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

char i2cc(int i){
	return (i > 9) ? i+55 : i+48;
}

void spawnnumbers(){
	double id, sid, cid;
	for(int i = 1; i <= 12; ++i){
		id = (double)i;
		id *= (360/12);
		id *= d2r;
		sid = sin(id);
		cid = cos(id);
		sid *= MARKER_RAD_X;
		cid *= MARKER_RAD_Y;
		bigclock[OG_X+(int)sid][OG_Y-(int)cid] = i2cc(i); // y goes top to bottom
	}
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
	for(int p = 0; p <= MIN_LEN; ++p){			//mins
		mts = ms * p;
		mtc = mc * p/2;
		bigclock[OG_X+(int)mts][OG_Y-(int)mtc] = C_MINHAND; // y goes top to bottom
	}
	for(int p = 0; p <= HOUR_LEN; ++p){			//hours
		hts = hs * p;
		htc = hc * p/2;
		bigclock[OG_X+(int)hts][OG_Y-(int)htc] = C_HOURHAND; // y goes top to bottom
	}
}

int decipheroffset(struct Time *time, char *s){
	int i = 0, pos = 0, neg = 0; //pos 0 = hour, 1 = min, 2 = sec, >2 || <0 = err
	while(1){
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
						time->hour += (s[i] - 48);
						if((s[i+1] != 0) && (s[i+1] != ':'))
							time->hour *= 10;
						break;
					case 1:
						time->min += (s[i] - 48);
						if((s[i+1] != 0) && (s[i+1] != ':'))
							time->min *= 10;
						break;
					case 2:
						time->sec += (s[i] - 48);
						if(s[i+1] != 0)
							time->sec *= 10;
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
