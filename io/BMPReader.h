/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
added multithreading
*/

/**
 * @file BMPReader.h
 * @brief Declares the BMPReader class for loading BMP images from a file.
 */

#ifndef BMPREADER_H
#define BMPREADER_H

#include <string>
#include <fstream>
#include "../model/BMPImage.h"

/**
 * @class BMPReader
 * @brief A utility class to read BMP images from binary files.
 */
class BMPReader {
public:
    /**
     * @brief Loads a BMP image from the specified file.
     * @param filepath Path to the BMP file.
     * @return BMPImage object containing header, info, and pixel data.
     * @throws std::runtime_error If file cannot be opened or image dimensions are invalid.
     */
    static BMPImage loadFromFile(const std::string& filepath);
};

#endif
