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

int main(int argc, char * argv[]) {
	setup_handlers();

	if (ws2811_init(&ledstring) != WS2811_SUCCESS)
	{
	fprintf(stderr, "ws2811_init failed: \n");
	return -1;
	}
	    
	ColorWheel c(110, {{255,0,0}, {0,255,0}, {0,0,255}});
	while (running) {
		for (int i = 0; i < 110; ++i) {

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
