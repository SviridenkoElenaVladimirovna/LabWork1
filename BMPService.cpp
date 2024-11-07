/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#include "BMPService.h"

BMPImage BMPService::rotateClockwise(BMPImage& originalImage) {
    const BMPInfoHeader originalInfoHeader = originalImage.getInfoHeader();
    const int originalWidth = originalInfoHeader.width;
    const int originalHeight = originalInfoHeader.height;

    std::vector<uint8_t> originalPixels = originalImage.getPixels();
    std::vector<uint8_t> rotatedPixels(originalPixels.size(), 0);

    for (int y = 0; y < originalHeight; ++y) {
        for (int x = 0; x < originalWidth; ++x) {
            int originalIndex = (x + y * originalWidth) * 3; 
            int rotatedIndex = ((originalWidth - 1 - x) * originalHeight + y) * 3;
            rotatedPixels[rotatedIndex] = originalPixels[originalIndex]; 
            rotatedPixels[rotatedIndex + 1] = originalPixels[originalIndex + 1]; 
            rotatedPixels[rotatedIndex + 2] = originalPixels[originalIndex + 2]; 
        }
    }

    BMPInfoHeader rotatedInfoHeader = originalInfoHeader;
    rotatedInfoHeader.width = originalHeight;
    rotatedInfoHeader.height = originalWidth;

    return BMPImage(originalImage.getHeader(), rotatedInfoHeader, rotatedPixels);
}

BMPImage BMPService::rotateCounterclockwise(BMPImage& originalImage) {
    const BMPInfoHeader originalInfoHeader = originalImage.getInfoHeader();
    const int originalWidth = originalInfoHeader.width;
    const int originalHeight = originalInfoHeader.height;

    std::vector<uint8_t> originalPixels = originalImage.getPixels();
    std::vector<uint8_t> rotatedPixels(originalPixels.size(), 0);

    for (int y = 0; y < originalHeight; ++y) {
        for (int x = 0; x < originalWidth; ++x) {
            int originalIndex = (x + y * originalWidth) * 3; 
            int rotatedIndex = (x * originalHeight + (originalHeight - 1 - y)) * 3;
            rotatedPixels[rotatedIndex] = originalPixels[originalIndex]; 
            rotatedPixels[rotatedIndex + 1] = originalPixels[originalIndex + 1]; 
            rotatedPixels[rotatedIndex + 2] = originalPixels[originalIndex + 2]; 
        }
    }

    BMPInfoHeader rotatedInfoHeader = originalInfoHeader;
    rotatedInfoHeader.width = originalHeight;
    rotatedInfoHeader.height = originalWidth;

    return BMPImage(originalImage.getHeader(), rotatedInfoHeader, rotatedPixels);
}

BMPImage BMPService::applyGaussianFilter(BMPImage& image) {
    const float kernel[3][3] = {
        {0.0625f, 0.125f, 0.0625f},
        {0.125f, 0.25f, 0.125f},
        {0.0625f, 0.125f, 0.0625f}
    };

    const BMPInfoHeader infoHeader = image.getInfoHeader();
    const std::vector<uint8_t> pixels = image.getPixels();
    std::vector<uint8_t> filteredPixels(image.getPixels());

    for (int y = 1; y < infoHeader.height - 1; ++y) {
        for (int x = 1; x < infoHeader.width - 1; ++x) {
            float blue = 0;
            float green = 0;
            float red = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int index = ((y + ky) * infoHeader.width + (x + kx)) * 3;
                    blue += pixels[index] * kernel[ky + 1][kx + 1];
                    green += pixels[index + 1] * kernel[ky + 1][kx + 1];
                    red += pixels[index + 2] * kernel[ky + 1][kx + 1];
                }
            }

            int filteredIndex = (y * infoHeader.width + x) * 3;

            filteredPixels[filteredIndex] = (blue > 255) ? 255 : (blue < 0) ? 0 : (uint8_t)blue;
            filteredPixels[filteredIndex + 1] = (green > 255) ? 255 : (green < 0) ? 0 : (uint8_t)green;
            filteredPixels[filteredIndex + 2] = (red > 255) ? 255 : (red < 0) ? 0 : (uint8_t)red;
        }
    }

    return BMPImage(image.getHeader(), infoHeader, filteredPixels);
}
