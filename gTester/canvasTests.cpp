#include "pch.h"
#include "Canvas.cpp"

// Scenario: Creating a canvas
//	Given c ← canvas(10, 20)
//	Then c.width = 10
//	And c.height = 20
//	And every pixel of c is color(0, 0, 0)
TEST(CanvasTests, CanvasDimensions) {
  Canvas c(10, 20);
  Color black;
  for (unsigned i = 0; i < sizeof(c._pixelColors); ++i) {
    EXPECT_TRUE(c._pixelColors[i] == black);
  }
}

// Scenario: Writing pixels to a canvas
//	Given c ← canvas(10, 20)
//	And red ← color(1, 0, 0)
//	When write_pixel(c, 2, 3, red)
//	Then pixel_at(c, 2, 3) = red
TEST(CanvasTests, WriteColorPixel) {
  Canvas c(10, 20);
  Color red(1, 0, 0);
  c.write_pixel(2, 3, red);
  EXPECT_TRUE(c.getPixelColor(2 + c._width * 3) == red);
}

// Scenario: Constructing the PPM header
//	Given c ← canvas(5, 3)
//	When ppm ← canvas_to_ppm(c) // Then lines 1 - 3 of ppm are
                                    //"""
                                    // P3
                                    // 5 3
                                    // 255
                                    //"""
TEST(CanvasTests, ConstructPPMHeader) {
  Canvas c(5, 3);

  EXPECT_TRUE(c.canvasToPpm(true) == "P3\n5 3\n255\n");
} // Scenario: Constructing the PPM pixel data
//	Given c ← canvas(5, 3)
//	And c1 ← color(1.5, 0, 0)
//	And c2 ← color(0, 0.5, 0)
//	And c3 ← color(-0.5, 0, 1)
//	When write_pixel(c, 0, 0, c1)
//	And write_pixel(c, 2, 1, c2)
//	And write_pixel(c, 4, 2, c3)
//	And ppm ← canvas_to_ppm(c)
//	Then lines 4 - 6 of ppm are
//	"""
//	255 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//	0 0 0 0 0 0 0 128 0 0 0 0 0 0 0
//	0 0 0 0 0 0 0 0 0 0 0 0 0 0 255
//	"""
TEST(CanvasTests, ConstructPPMPixelData) {
  Canvas c(5, 3);
  Color c1(1.5, 0, 0);
  Color c2(0, 0.5, 0);
  Color c3(-0.5, 0, 1);

  c.write_pixel(0, 0, c1);
  c.write_pixel(2, 1, c2);
  c.write_pixel(4, 2, c3);
  std::string testPPMFile =
      "P3\n5 3\n255\n"
      "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 0 0\n"
      "0 0 0 0 0 0 0 0 0 0 0 0 255\n";
  EXPECT_TRUE(c.canvasToPpm() == testPPMFile);
}

//Scenario: Splitting long lines in PPM files
//    Given c ← canvas(10, 2)
//    When every pixel of c is set to color(1, 0.8, 0.6)
//    And ppm ← canvas_to_ppm(c)
//    Then lines 4 - 7 of ppm are
//    """
//    255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
//    153 255 204 153 255 204 153 255 204 153 255 204 153
//    255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
//    153 255 204 153 255 204 153 255 204 153 255 204 153
//    """
TEST(CanvasTests, SplittingPPMLines) {
    Canvas c(10, 2);
    Color allPixels(1, 0.8, 0.6);
    for (unsigned i = 0; i < c._totalPixelCount; ++i) {
        c._pixelColors[i] = allPixels;
    }

    std::string testPPMFile =
        "P3\n10 2\n255\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255\n"
        "204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
        "255 204 153 255 204 153 255 204 153\n";
    EXPECT_TRUE(c.canvasToPpm() == testPPMFile);
}
// Scenario: PPM files are terminated by a newline character     
//Given c ← canvas(5, 3) 
//When ppm  ← canvas_to_ppm(c) 
//Then ppm ends with a newline character
TEST(CanvasTests, PPMFileNewlineEnding) {
    Canvas c(5, 3);

    std::string ppmFileStr = c.canvasToPpm();

    std::string endingTwoChars =
                     ppmFileStr.substr(ppmFileStr.length() - 1, ppmFileStr.length() - 1);

    EXPECT_TRUE(endingTwoChars == "\n");
}