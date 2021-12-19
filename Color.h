#include <vector>
#include "error.h"

using namespace std;

struct Color {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
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
	void regenerate_curve(); 
};
