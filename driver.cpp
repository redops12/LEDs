#include <thread>

#include "driver.h"

void run() {
	Color blue;
	blue.blue = 255;
	Color white;
	white.red = 255;
	white.green = 255;
	white.blue = 255;
	ColorWheel c(110, {white, blue, white, blue});
	while (running) {
		for (int i = 0; i < 110; ++i) {
			printf("%d %x\n", i, (c.colors_gradient[i].red << 16) + (c.colors_gradient[i].green << 8) + c.colors_gradient[i].blue);
			ledstring.channel[0].leds[i+8] = (c.colors_gradient[i].red << 16) + (c.colors_gradient[i].green << 8) + c.colors_gradient[i].blue;
		}

		if (ws2811_render(&ledstring) != WS2811_SUCCESS)
		{
		    fprintf(stderr, "ws2811_render failed: \n");
		    break;
		}
        	usleep(1000000 / 15);
	}
}

void driver_init() {
	setup_handlers();

	if (ws2811_init(&ledstring) != WS2811_SUCCESS)
	{
		fprintf(stderr, "ws2811_init failed: \n");
		exit(1);
	}
	thread t(run);
}
