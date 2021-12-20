
#include "driver.h"

// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define LED_COUNT               120

int led_count = LED_COUNT;

pixel pixels[110];

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

void run() {
		for (int i = 0; i < 110; ++i) {
			if (pixels[i].counter >= pixels[i].c->length) {
				continue;
			}
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
		}
}

void driver_init() {
	setup_handlers();

	if (ws2811_init(&ledstring) != WS2811_SUCCESS)
	{
		fprintf(stderr, "ws2811_init failed: \n");
		exit(1);
	}
}
