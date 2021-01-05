#include <stdio.h>
/*
 *     ***
 *    *   *
 *    h   m   48wide for big
 *    *   *
 *     ***
 *     get tclock.c from ncurses4.2/test/
 */
int main(int argc, char **argv){
	initclock();
	Time t;
	readtime(&t);
	writeclock(1, tweakhour(t.hour, t.min));
	writeclock(0, t.min);
	printclock();
	return 0;
}
