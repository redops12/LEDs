#include "Color.h"
#include "ws28128-rpi/ws2812-rpi.h"

using namespace std;

int main(int argc, char * argv[]) {
	ColorLine c(110, {{255,0,0}, {0,255,0}, {0,0,255}});
	NeoPixel n(120);
	n.begin();
	for (int i = 0; i < 110; ++i) {
		n.setPixelColor(i+8, c.colors_gradient[i].red, c.colors_gradient[i].green, c.colors_gradient[i].blue);
	}
	n.show();
}
