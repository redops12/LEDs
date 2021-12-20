
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

#include "ws2811.h"
#ifndef OTHER
#define OTHER

static uint8_t running = 1;

static void ctrl_c_handler(int signum)
{
	(void)(signum);
    running = 0;
    printf("terminated\n");
}

static void setup_handlers(void)
{
    struct sigaction sa;
    sa.sa_handler = ctrl_c_handler,

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}
#endif
