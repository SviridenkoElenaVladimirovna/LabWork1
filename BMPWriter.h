/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#ifndef BMPWRITER_H
#define BMPWRITER_H

#include <string>
#include <fstream>
#include "BMPImage.h"

class BMPWriter {
public:
    static void saveToFile(const BMPImage& image,const std::string& filepath);
};

#endif 
