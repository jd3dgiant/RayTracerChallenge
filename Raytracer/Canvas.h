#pragma once

#include <Vector>
#include "Tuples.h"

class Canvas {
	public:
		Canvas(int inWidth, int inHeight) :
			width(inWidth), height(inHeight) {
			//pixelColors = new Color[inWidth * inHeight];
			pixelColors.resize(inWidth * inHeight);
		}
		
		//~Canvas()
		//{
		//	delete[] pixelColors;
		//}


		int width;
		int height;

		std::vector<Color> pixelColors;
		//Color* pixelColors;

		Color getPixelColor(Canvas& canvas, int index);

		void write_pixel(Canvas& canvas, int x, int y, Color& color);
};

