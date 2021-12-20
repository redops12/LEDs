#include <vector>
#include "error.h"

using namespace std;
#ifndef COLOR
#define COLOR

struct Color {
	unsigned char green = 0;
	unsigned char red = 0;
	unsigned char blue = 0;
} typedef Color;

Color linear(Color c1, Color c2, int length, int pos);

class ColorLine {
public:
	vector<Color> colors_fixed;
	int length;
	vector<Color> colors_gradient;

	ColorLine(int length, vector<Color> in_colors_fixed);

	virtual	void regenerate_curve(); 

	void add_color(Color c, int pos = -1); 

	void delete_color(int pos = -1);
};

class ColorWheel : public ColorLine {
public:	
	ColorWheel(int length, vector<Color> in_colors_fixed);

	void regenerate_curve(); 
};

#endif
