#include "pch.h"
#include "Canvas.h"


Color Canvas::getPixelColor(Canvas & canvas, int index) {
	return canvas.pixelColors[index];
}

void Canvas::write_pixel(Canvas& canvas, int x, int y, Color& color) {
	int pixelIndex = x + canvas.width * y;
	canvas.pixelColors[pixelIndex] = color;
}
