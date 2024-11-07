/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#include "BMPReader.h"
#include <iostream>
#include <stdexcept>
#include <string>

BMPImage BMPReader::loadFromFile(const std::string& filepath) {
    std::ifstream inFile(filepath, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Failed to open file:" + filepath);
    }

    BMPHeader header;
    inFile.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    BMPInfoHeader infoHeader;
    inFile.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

    if (infoHeader.width <= 0 || infoHeader.height <= 0) {
        throw std::runtime_error(
            "Incorrect image dimensions\n"
            " width:" + std::to_string(infoHeader.width) + "\n"
            " height: " + std::to_string(infoHeader.height) + "\n");
    }

    size_t numberOfPixels = infoHeader.width * infoHeader.height * (infoHeader.bitsPerPixel / 8);
    std::cout<<"amount of memory allocated for pixels "<<numberOfPixels <<"\n";
    std::vector<uint8_t> pixels(numberOfPixels);

    inFile.read(reinterpret_cast<char*>(& pixels[0]), numberOfPixels);
    inFile.close();

    return BMPImage(header, infoHeader, pixels);
}
