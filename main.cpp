#include "Color.h"

#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
#include <getopt.h>

#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"
#include "version.h"
#include "other.c"

#include "ws2811.h"

#ifdef __cplusplus
}
#endif



// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define LED_COUNT               120

int led_count = LED_COUNT;

using namespace std;

ws2811_t ledstring =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
    {
        [0] =
        {
            .gpionum = GPIO_PIN,
            .invert = 0,
            .count = LED_COUNT,
            .strip_type = STRIP_TYPE,
            .brightness = 255,
        },
        [1] =
        {
            .gpionum = 0,
            .invert = 0,
            .count = 0,
            .brightness = 0,
        },
    },
};

class pixel {
public:
	ColorLine *c = new ColorLine(1, {{0,0,0}});
	bool loop = true;
	unsigned int counter = 0;
};

pixel pixels[110];

int main(int argc, char * argv[]) {
	setup_handlers();

	if (ws2811_init(&ledstring) != WS2811_SUCCESS)
	{
	fprintf(stderr, "ws2811_init failed: \n");
	return -1;
	}
	    
	Color blue = {0,0, 255};
	Color white = {255, 255, 255};
	ColorWheel c1(110, {blue, white, blue, white});
	ColorWheel c2(110, {white, blue, white, blue});
	for (int i = 0; i < 110; ++i) {	
		pixels[i].c = new ColorWheel(110, {c1.colors_gradient[i], c2.colors_gradient[i]});
		pixels[i].loop = true;
	} 

	ColorWheel c(110, {{255,0,0}, {0,255,0}, {0,0,255}});
	while (running) {
		for (int i = 0; i < 110; ++i) {
			//printf("%d %x\n", i, (c.colors_gradient[i].red << 16) + (c.colors_gradient[i].green << 8) + c.colors_gradient[i].blue);
			//ledstring.channel[0].leds[i+8] = (c.colors_gradient[i].red << 16) + (c.colors_gradient[i].green << 8) + c.colors_gradient[i].blue;
			ledstring.channel[0].leds[i+8] = (pixels[i].c->colors_gradient[pixels[i].counter].red << 16) + (pixels[i].c->colors_gradient[pixels[i].counter].green << 8) + pixels[i].c->colors_gradient[pixels[i].counter].blue;
			pixels[i].counter++;
			if (pixels[i].counter == pixels[i].c->length) {
				if (pixels[i].loop) {
					pixels[i].counter = 0;
				} 
			}
		}

		if (ws2811_render(&ledstring) != WS2811_SUCCESS)
		{
		    fprintf(stderr, "ws2811_render failed: \n");
		    break;
		}
        	usleep(1000000 / 15);
	}
}
