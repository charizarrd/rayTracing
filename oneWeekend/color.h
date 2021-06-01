#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "utilities.h"

#include <iostream>

void writeColor(std::ostream &out, Color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

void writeColor(std::ostream &out, Color pixelColor, int samplesPerPixel) {
	double r = pixelColor.x();
	double g = pixelColor.y();
	double b = pixelColor.z();


	// Divide by number of samples -- pixelColor should be total sum of this number of color values
    auto scale = 1.0 / samplesPerPixel;
    // Doing /= here loses precision :(
    // Also gamma correction here where gamma = 2
	r = sqrt(r * scale);
	g = sqrt(g * scale);
	b = sqrt(b * scale);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255 * clamp(b, 0.0, 0.999)) << '\n';

}

#endif