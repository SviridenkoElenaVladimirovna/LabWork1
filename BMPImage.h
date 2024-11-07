#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include <vector>
#include "BMPHeader.h"
#include "BMPInfoHeader.h"

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