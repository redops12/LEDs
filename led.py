import time, math
from neopixel import *
from random import *

# LED strip configuration:
LED_COUNT      = 120      # Number of LED pixels.
LED_PIN        = 18      # GPIO pin connected to the pixels (must support PWM!).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 5       # DMA channel to use for generating signal (try 5)
LED_BRIGHTNESS = 255     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)

strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS)

strip.begin() 
i = 0
while (True):
        print(i)
        strip.setPixelColor(i % 110 + 8,Color((int) (128*math.sin((4*i)/100)+127),(int) (128*math.sin((4*i+200)/100)+127),(int) (128*math.sin((i*4+400)/100)+127)))
        strip.show()
        time.sleep(.03)
        i = i +1
