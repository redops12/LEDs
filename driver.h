
#include "Color.h"

#include <thread>
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

#ifndef DRIVER
#define DRIVER

void run();
void driver_init(); 

#endif
