#include "Canvas.h"
#include <math.h>
#include <iterator>
#include "pch.h"

Color Canvas::getPixelColor(int index) const {
  return _pixelColors[index];
}

void Canvas::write_pixel(int x, int y, Color& color) {
  // checking to be sure that written pixel is within range
  if ((x < 0 || x >= _width) || (y < 0 || y >= _height)) {
    return;
  }
  int pixelIndex = x + _width * y;
  _pixelColors[pixelIndex] = color;
}

std::string Canvas::canvasToPpmHeader() {
  return "P3\n" + std::to_string(_width) + " " + std::to_string(_height) + "\n" +
      std::to_string(BITCOLORMAX) + "\n";
}

std::string Canvas::canvasToPpm(bool headerOnly) {
  std::string ppmHeader = canvasToPpmHeader();
  if (headerOnly) {
    return ppmHeader;
  }

  std::string ppmBodyStr = "";
  int ppmLineLength = 0;

  for (unsigned i = 0; i < _totalPixelCount; ++i) {
    addColorValueToPPMOutput(ppmLineLength, _pixelColors[i].r(), ppmBodyStr);
    addColorValueToPPMOutput(ppmLineLength, _pixelColors[i].g(), ppmBodyStr);
    addColorValueToPPMOutput(ppmLineLength, _pixelColors[i].b(), ppmBodyStr);
  }
  return ppmHeader + ppmBodyStr + "\n";
}

void Canvas::addColorValueToPPMOutput(
    int& ppmLineLength,
    float pixelChannelVal,
    std::string& ppmBodyStr) {
  int channelValue = convertColorFloatToInt(pixelChannelVal);
  channelValue = clampChannelValue(channelValue);
  std::string channelValStr =
      std::to_string(channelValue); // adding space to the end to separate entries

  int channelValLen = channelValStr.length();

  if (ppmLineLength + channelValLen > MAXPPMLINELENGTH) {
    ppmBodyStr += "\n";
    ppmLineLength = 0;
  }
  if (ppmLineLength != 0) {
    ppmBodyStr += " ";
  }
  ppmBodyStr += channelValStr;
  ppmLineLength += channelValLen + 1;
}

int Canvas::convertColorFloatToInt(float inputVal) {
  return (int)std::ceil((inputVal * BITCOLORMAX));
}

int Canvas::clampChannelValue(int inputVal) const {
  if (inputVal < 0) {
    return 0;
  } else if (inputVal > BITCOLORMAX) {
    return BITCOLORMAX;
  } else {
    return inputVal;
  }
}

void Canvas::saveToDisk(const char* filePath) {
  std::string ppm = canvasToPpm();

  std::ofstream ppmFile(filePath);
  if (ppmFile.is_open()) {
    ppmFile << ppm;

    ppmFile.close();
  }
}
