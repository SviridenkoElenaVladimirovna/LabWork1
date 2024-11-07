/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#include <iostream>
#include "BMPImage.h"
#include "BMPReader.h"
#include "BMPService.h"
#include "BMPWriter.h"

int main() {
    const std::string filepath = "/home/vboxuser/Desktop/image.bmp";
    const std::string clockwiseFilepath = "/home/vboxuser/Desktop/rotated_clockwise.bmp";
    const std::string counterclockwiseFilepath = "/home/vboxuser/Desktop/rotated_counterclockwise.bmp";
    const std::string gaussianFilterFilepath = "/home/vboxuser/Desktop/filtered_image.bmp";

    BMPImage image = BMPReader::loadFromFile(filepath);

    BMPWriter::saveToFile(BMPService::rotateClockwise(image), clockwiseFilepath);

    BMPImage rotatedImage = BMPService::rotateCounterclockwise(image);

    BMPWriter::saveToFile(rotatedImage, counterclockwiseFilepath);
    
    BMPWriter::saveToFile(BMPService::applyGaussianFilter(rotatedImage), gaussianFilterFilepath);

    std::cout << "Images successfully processed and saved" << std::endl;
    return 0;
}
