#include "Color.h"
#include "driver.h"
#include "other.c"

#include <iostream>

int main(int argc, char * argv[]) {
	driver_init();
	while (running) {
		cout << running << endl;
		run();
        	usleep(1000000 / 15);
	}
}
