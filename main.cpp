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

    BMPWriter::saveToFile(BMPService::rotateCounterclockwise(image), counterclockwiseFilepath);

    BMPWriter::saveToFile(BMPService::applyGaussianFilter(image), gaussianFilterFilepath);

    std::cout << "Images successfully processed and saved" << std::endl;
    return 0;
}
