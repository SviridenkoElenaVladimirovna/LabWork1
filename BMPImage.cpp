/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#include "BMPImage.h"
#include <algorithm>

BMPImage::BMPImage() {}

BMPImage::BMPImage(BMPHeader bmpHeader, BMPInfoHeader bmpInfoHeader, std::vector<uint8_t> pixels) {
    this->bmpHeader = bmpHeader;
    this->bmpInfoHeader = bmpInfoHeader;
    this->pixels = std::move(pixels);
}
