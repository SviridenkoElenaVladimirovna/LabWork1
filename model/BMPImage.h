/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
added multithreading
*/
#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include <vector>
#include "../model/BMPHeader.h"
#include "../model/BMPInfoHeader.h"

class BMPImage {
private:
    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;
    std::vector<uint8_t> pixels;

public:
    BMPImage();
    BMPImage(BMPHeader bmpHeader, BMPInfoHeader bmpInfoHeader, std::vector<uint8_t> pixels);

    const BMPHeader& getHeader() const { return bmpHeader; }
    const BMPInfoHeader& getInfoHeader() const { return bmpInfoHeader; }
    const std::vector<uint8_t>& getPixels() const { return pixels; }
};

#endif
