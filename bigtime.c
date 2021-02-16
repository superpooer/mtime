#include <stdio.h>
#include <time.h>
#include "hdtime.h"

char bigclock[50][25];

int main(int argc, char **argv){
	init();
	drawclock();
	return 0;
}

void init(){
	for(int x = 0; x <= WIDTH; ++x){			//going from top left
		for(int y = 0; y <= HEIGHT; ++y){
			while((x == 0) || (x == WIDTH) || (y == 0) || (y == WIDTH))
				bigclock[x][y] = C_BORDER;
		}
	}
	bigclock[(int)WIDTH/2][(int)HEIGHT/2] = C_ORIGIN;
}
