
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
	Color blue;
	blue.blue = 255;
	Color white;
	white.red = 255;
	white.green = 255;
	white.blue = 255;
	ColorWheel c(110, {white, blue, white, blue});
		for (int i = 0; i < 110; ++i) {
			//printf("%d %x\n", i, (c.colors_gradient[i].red << 16) + (c.colors_gradient[i].green << 8) + c.colors_gradient[i].blue);
			ledstring.channel[0].leds[i+8] = (c.colors_gradient[i].red << 16) + (c.colors_gradient[i].green << 8) + c.colors_gradient[i].blue;
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
