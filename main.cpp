#include "Color.h"
#include "driver.h"

#include <iostream>

int main(int argc, char * argv[]) {
	// driver_init();
	Color blue;
	blue.blue = 255;
	Color white;
	white.red = 255;
	white.green = 255;
	white.blue = 255;
	ColorWheel c(110, {white, blue, white, blue});
	for (int i = 0; i < 110; ++i) {
		printf("%d %x\n", i, (c.colors_gradient[i].red << 16) + (c.colors_gradient[i].green << 8) + c.colors_gradient[i].blue);
	}
}
