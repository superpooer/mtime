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
char    toprow[4] = " ***";
char    secrow[5] = "*   *";
char  thirdrow[5] = "*   *";
char fourthrow[5] = "*   *";
char    botrow[4] = " ***";

void writeclock(int isHour, int ang){
	char c = 'M';
	if(isHour)
		c = 'H';
	switch(ang){
		case 1:
			toprow[3] = c;
			break;
		case 2:
			secrow[4] = c;
			break;
		case 3:
			thirdrow[4] = c;
			break;
		case 4:
			fourthrow[4] = c;
			break;
		case 5:
			botrow[3] = c;
			break;
		case 6:
			botrow[2] = c;
			break;
		case 7:
			botrow[1] = c;
			break;
		case 8:
			fourthrow[0] = c;
			break;
		case 9:
			thirdrow[0] = c;
			break;
		case 10:
			secrow[0] = c;
			break;
		case 11:
			toprow[1] = c;
			break;
		case 12:
			toprow[2] = c;
			break;
	}
}

void printclock(){
	printf("\n%s", toprow);
	printf("\n%s", secrow);
	printf("\n%s", thirdrow);
	printf("\n%s", fourthrow);
	printf("\n%s", botrow);
}

int to5mac(int in){
	in /= 12;
	return in*12;
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
	writeclock(1, t.hour); //5 min accuracy version
	writeclock(0, to5mac(t.min)); //5 min accuracy version
	printclock();
	return 0;
}
