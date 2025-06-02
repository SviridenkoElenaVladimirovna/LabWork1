/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
added multithreading
*/

/**
 * @file BMPWriter.h
 * @brief Declares the BMPWriter class for saving BMP images.
 */

#ifndef BMPWRITER_H
#define BMPWRITER_H

#include <string>
#include <fstream>
#include "../model/BMPImage.h"

/**
 * @class BMPWriter
 * @brief A utility class to write BMP images to binary files.
 */
class BMPWriter {
public:
    /**
     * @brief Saves a BMP image to the specified file.
     * @param image The image to save.
     * @param filepath Output file path.
     */
    static void saveToFile(const BMPImage& image, const std::string& filepath);
};

#endif
