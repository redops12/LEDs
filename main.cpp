#include "Color.h"
#include "driver.h"
#include "other.c"

#include <iostream>

int main(int argc, char * argv[]) {
	driver_init();

	Color blue = {0,0, 255};
	Color white = {255, 255, 255};
	ColorWheel c1(110, {blue, white, blue, white});
	ColorWheel c2(110, {white, blue, white, blue});
	for (int i = 0; i < 110; ++i) {	
		pixels[i].c = new ColorWheel(110, {c1.colors_gradient[i], c2.colors_gradient[i]});
		pixels[i].loop = true;
	} 
	while (running) {
		cout << running << endl;
		run();
        usleep(1000000 / 150);
	}
}
