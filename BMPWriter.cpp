/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#include "BMPWriter.h"
#include <iostream>

void BMPWriter::saveToFile(const BMPImage &image, const std::string &filepath) {
    std::ofstream outFile(filepath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to save file: " << filepath << std::endl;
        return;
    }

    outFile.write((const char*)&(image.getHeader()), sizeof(BMPHeader));
    outFile.write((const char*)&(image.getInfoHeader()), sizeof(BMPInfoHeader));

    const std::vector<uint8_t>& pixels = image.getPixels();
    outFile.write((const char*)(pixels.data()), pixels.size());
    outFile.close();
}
