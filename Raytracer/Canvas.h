#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Tuples.h"

class Canvas {
    public:
		Canvas(int inWidth, int inHeight)
		: _width(inWidth), _height(inHeight), _totalPixelCount(inWidth * inHeight){
			_pixelColors = new Color[inWidth * inHeight];
		}

		~Canvas() {
			delete[] _pixelColors;
		}

		const int BITCOLORMAX = 255;
        const int MAXPPMLINELENGTH = 68; // true value is 70 but if this threshold is crossed then '\n' is added instead bringing the length to 70

        int _totalPixelCount;

		int _width;
		int _height;

		Color *_pixelColors;

		Color getPixelColor(int index) const;

		void write_pixel(int x, int y, Color &color);

		std::string canvasToPpm(bool headerOnly = false);

        void saveToDisk(const char* filePath);

    private:
		std::string canvasToPpmHeader();

        void addColorValueToPPMOutput(int &ppmLineLength, float pixelChannelVal, std::string& ppmBodyStr);

        int convertColorFloatToInt(float inputVal);

		int clampChannelValue(int inputVal) const;
};
