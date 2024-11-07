/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#ifndef BMPREADER_H
#define BMPREADER_H

#include <string>
#include <fstream>
#include "BMPImage.h"

class BMPReader {
public:
    static BMPImage loadFromFile(const std::string& filepath);
};

#endif 
