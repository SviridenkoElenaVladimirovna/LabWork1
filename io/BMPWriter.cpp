/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
added multithreading
*/

/**
 * @file BMPWriter.cpp
 * @brief Implements BMPWriter for writing BMP files.
 */

#include "../io/BMPWriter.h"
#include <iostream>

void BMPWriter::saveToFile(const BMPImage& image, const std::string& filepath) {
    std::ofstream outFile(filepath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to save file: " << filepath << std::endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&image.getHeader()), sizeof(BMPHeader));
    outFile.write(reinterpret_cast<const char*>(&image.getInfoHeader()), sizeof(BMPInfoHeader));

    const std::vector<uint8_t>& pixels = image.getPixels();
    outFile.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    outFile.close();
}
