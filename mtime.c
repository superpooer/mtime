#include <stdio.h>
/*
 *     ***
 *    *   *
 *    h   m   48wide for big
 *    *   *
 *     ***
 *     get tclock.c from ncurses4.2/test/
 */

typedef struct{
	int hour;
	int min;
	int sec;
} Time;

//init clock (5min accuracy version)
char    toprow[7] = " * * *\0";
char    secrow[8] = "*     *\0";
char  thirdrow[8] = "*     *\0";
char fourthrow[8] = "*     *\0";
char    botrow[7] = " * * *\0";
int pos1  = 5;
int pos2  = 6;
int pos3  = 6;
int pos4  = 6;
int pos5  = 5;
int pos6  = 3;
int pos7  = 1;
int pos8  = 0;
int pos9  = 0;
int pos10 = 0;
int pos11 = 1;
int pos12 = 3;

void writeclock(int isHour, int ang){
	char c = 'M';
	if(isHour)
		c = 'H';
	switch(ang){
		case 1:
			toprow[pos1] = c;
			break;
		case 2:
			secrow[pos2] = c;
			break;
		case 3:
			thirdrow[pos3] = c;
			break;
		case 4:
			fourthrow[pos4] = c;
			break;
		case 5:
			botrow[pos5] = c;
			break;
		case 6:
			botrow[pos6] = c;
			break;
		case 7:
			botrow[pos7] = c;
			break;
		case 8:
			fourthrow[pos8] = c;
			break;
		case 9:
			thirdrow[pos9] = c;
			break;
		case 10:
			secrow[pos10] = c;
			break;
		case 11:
			toprow[pos11] = c;
			break;
		case 12:
			toprow[pos12] = c;
			break;
	}
}

void printclock(Time *t){
	printf("\n  %i:%i", t->hour, t->min);
	printf("\n%s", toprow);
	printf("\n%s", secrow);
	printf("\n%s", thirdrow);
	printf("\n%s", fourthrow);
	printf("\n%s", botrow);
	printf("\n");
}

int minto12(int in){
	in += 2; //to make int div look like float rounding on clock
	in /= 5;
}

int hourto12(int in){
	return (in > 12) ? in-12 : in;
}

//DEBUG
void readtime(Time *t){
	t->hour = 1;
	t->min = 23;
	t->sec = 17;
}
//DEBUG

int main(int argc, char **argv){
	Time t;
	readtime(&t);
	//writeclock(1, tweakhour(t.hour, t.min)); //1 min accuracy version
	//writeclock(0, to5mac(t.min)); //1 min accuracy version
	writeclock(1, hourto12(t.hour)); //5 min accuracy version
	writeclock(0, minto12(t.min)); //5 min accuracy version
	printclock(&t);
	return 0;
}
