#include "pch.h"
#include "Canvas.cpp"

//Scenario: Creating a canvas
//	Given c ← canvas(10, 20)
//	Then c.width = 10
//	And c.height = 20
//	And every pixel of c is color(0, 0, 0)
TEST(CanvasTests, CanvasDimensions) {
	Canvas c(10, 20);
	Color black;
	for (unsigned i = 0; i < c.pixelColors.size(); ++i) {
		EXPECT_TRUE(c.pixelColors[i] == black);
	}
}

//Scenario: Writing pixels to a canvas
//	Given c ← canvas(10, 20)
//	And red ← color(1, 0, 0)
//	When write_pixel(c, 2, 3, red)
//	Then pixel_at(c, 2, 3) = red
TEST(CanvasTests, WriteColorPixel) {
	Canvas c(10, 20);
	Color red(1, 0, 0);
	c.write_pixel(c, 2, 3, red);
	EXPECT_TRUE(c.getPixelColor(c, 2 + c.width * 3) == red);
}