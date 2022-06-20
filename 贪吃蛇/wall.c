#include "wall.h"

void initWall() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
				printf("*");
			}
			else {
				printf(" ");
			}
		}
		if (i == 5) printf("\tÌ°³ÔÉß");
		if (i == 7) printf("\tÉÏ£ºw");
		if (i == 8) printf("\tÏÂ£ºs");
		if (i == 9) printf("\t×ó£ºa");
		if (i == 10) printf("\tÓÒ£ºd");
		printf("\n");
	}
}