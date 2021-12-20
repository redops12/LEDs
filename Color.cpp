#include "Color.h"
#include <iostream>

using namespace std;

Color linear(Color c1, Color c2, int length, int pos) {
	Color out;
	out.red = pos*(c2.red - c1.red)/length + c1.red;
	out.blue = pos*(c2.blue - c1.blue)/length + c1.blue;
	out.green = pos*(c2.green - c1.green)/length + c1.green;
	return out;
}

ColorLine::ColorLine(int length, vector<Color> in_colors_fixed): length(length), colors_fixed(in_colors_fixed) {
	regenerate_curve();
}	

void ColorLine::regenerate_curve() {
	int dist = length/(colors_fixed.size()-1);
	colors_gradient.resize(length);
	int end;
	for (int i = 0; i < colors_fixed.size() - 1; ++i) {
		for (int j = 0; j < dist; ++j) {
			colors_gradient[i * dist + j] = linear(colors_fixed[i], colors_fixed[i + 1], dist, j);
			end = i *dist + j;
		}
	}
	if (end != length) {
		for (int i = end; i < length; ++i)
			colors_gradient[i] = colors_gradient[end];
	}
}


void ColorLine::add_color(Color c, int pos) {
	if (pos < -1 || pos > colors_fixed.size()) {
		throw ColorException("set color at nonexistant location");	
	}
	if (pos	== -1) {
		colors_fixed.push_back(c);
	}
	else {
		colors_fixed.insert(colors_fixed.begin() + pos, c);
	}
	regenerate_curve();
}

void ColorLine::delete_color(int pos) {
	if (pos < -1 || pos >= colors_fixed.size()) {
		throw ColorException("delete nonexistant color");	
	}
	if (pos == -1) {
		colors_fixed.pop_back();
	}
	else {
		colors_fixed.erase(colors_fixed.begin() + pos);
	}
	regenerate_curve();
}

void ColorWheel::regenerate_curve() {
	cout << "test" << endl;
	int dist = length/colors_fixed.size();
	colors_gradient.resize(length);
	for (int i = 0; i < colors_fixed.size(); ++i) {
		for (int j = 0; j < dist; ++j) {	
			colors_gradient[i * dist + j] = linear(colors_fixed[i],  colors_fixed[(i == colors_fixed.size() - 1) ? 0 : i + 1], dist, j);
		}
	}
	if (end != length) {
		for (int i = end; i < length; ++i)
			colors_gradient[i] = colors_gradient[end];
	}
}

ColorWheel::ColorWheel(int length, vector<Color> in_colors_fixed): ColorLine(length, in_colors_fixed) {
	regenerate_curve();
}
