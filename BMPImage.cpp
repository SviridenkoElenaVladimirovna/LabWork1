#include "BMPImage.h"
#include <algorithm>

BMPImage::BMPImage() {}

BMPImage::BMPImage(BMPHeader bmpHeader, BMPInfoHeader bmpInfoHeader, std::vector<uint8_t> pixels) {
    this->bmpHeader = bmpHeader;
    this->bmpInfoHeader = bmpInfoHeader;
    this->pixels = std::move(pixels);
}
