/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#include "BMPMultiThreadService.h"
/**
 * @file BMPMultiThreadService.cpp
 * @brief Implementation of BMPMultiThreadService class with multithreaded processing of BMP images.
 */
BMPMultiThreadService::BMPMultiThreadService(const int numberOfThreads) {
    threadPool = new ThreadPool(numberOfThreads);
}

void clockwiseRotateFunc(
    const int y,
    const BMPInfoHeader& infoHeader,
    const std::vector<uint8_t>& originalPixels,
    std::vector<uint8_t>& rotated) {

    for (int x = 0; x < infoHeader.width; ++x) {
        int originalIndex = (x + y * infoHeader.width) * 3;
        int rotatedIndex = ((infoHeader.width - 1 - x) * infoHeader.height + y) * 3;
        rotated[rotatedIndex] = originalPixels[originalIndex];
        rotated[rotatedIndex + 1] = originalPixels[originalIndex + 1];
        rotated[rotatedIndex + 2] = originalPixels[originalIndex + 2];
    }
}

BMPImage BMPMultiThreadService::rotateClockwise(BMPImage& originalImage) {
    const BMPInfoHeader originalInfoHeader = originalImage.getInfoHeader();
    int originalWidth = originalInfoHeader.width;
    int originalHeight = originalInfoHeader.height;

    std::vector<uint8_t> originalPixels = originalImage.getPixels();
    std::vector<uint8_t> rotatedPixels(originalPixels.size(), 0);

    for (int y = 0; y < originalHeight; ++y) {
        threadPool->add_task(
            clockwiseRotateFunc,
            y,
            std::ref(originalInfoHeader),
            std::ref(originalPixels),
            std::ref(rotatedPixels)
        );
    }

    threadPool->wait_all();

    BMPInfoHeader rotatedInfoHeader = originalInfoHeader;
    rotatedInfoHeader.width = originalHeight;
    rotatedInfoHeader.height = originalWidth;

    return BMPImage(originalImage.getHeader(), rotatedInfoHeader, rotatedPixels);
}

void counterclockwiseRotateFunc(
    const int y,
    const BMPInfoHeader& infoHeader,
    const std::vector<uint8_t>& originalPixels,
    std::vector<uint8_t>& rotated) {

    for (int x = 0; x < infoHeader.width; ++x) {
        int originalIndex = (x + y * infoHeader.width) * 3;
        int rotatedIndex = (x * infoHeader.height + (infoHeader.height - 1 - y)) * 3;
        rotated[rotatedIndex] = originalPixels[originalIndex];
        rotated[rotatedIndex + 1] = originalPixels[originalIndex + 1];
        rotated[rotatedIndex + 2] = originalPixels[originalIndex + 2];
    }
}

BMPImage BMPMultiThreadService::rotateCounterclockwise(BMPImage& originalImage) {
    const BMPInfoHeader originalInfoHeader = originalImage.getInfoHeader();
    const int originalWidth = originalInfoHeader.width;
    const int originalHeight = originalInfoHeader.height;

    std::vector<uint8_t> originalPixels = originalImage.getPixels();
    std::vector<uint8_t> rotatedPixels(originalPixels.size(), 0);

    for (int y = 0; y < originalHeight; ++y) {
        threadPool->add_task(
            counterclockwiseRotateFunc,
            y,
            std::ref(originalInfoHeader),
            std::ref(originalPixels),
            std::ref(rotatedPixels)
        );
    }

    threadPool->wait_all();

    BMPInfoHeader rotatedInfoHeader = originalInfoHeader;
    rotatedInfoHeader.width = originalHeight;
    rotatedInfoHeader.height = originalWidth;

    return BMPImage(originalImage.getHeader(), rotatedInfoHeader, rotatedPixels);
}

void gaussianFilterFunc(
    const int y,
    const BMPInfoHeader& infoHeader,
    const std::vector<uint8_t>& originalPixels,
    std::vector<uint8_t>& filteredPixels) {

    const float kernel[3][3] = {
        {0.0625f, 0.125f, 0.0625f},
        {0.125f, 0.25f, 0.125f},
        {0.0625f, 0.125f, 0.0625f}
    };

    for (int x = 1; x < infoHeader.width - 1; ++x) {
        float blue = 0;
        float green = 0;
        float red = 0;

        for (int ky = -1; ky <= 1; ++ky) {
            for (int kx = -1; kx <= 1; ++kx) {
                int index = ((y + ky) * infoHeader.width + (x + kx)) * 3;
                blue += originalPixels[index] * kernel[ky + 1][kx + 1];
                green += originalPixels[index + 1] * kernel[ky + 1][kx + 1];
                red += originalPixels[index + 2] * kernel[ky + 1][kx + 1];
            }
        }

        int filteredIndex = (y * infoHeader.width + x) * 3;

        filteredPixels[filteredIndex] = (blue > 255) ? 255 : (blue < 0) ? 0 : (uint8_t)blue;
        filteredPixels[filteredIndex + 1] = (green > 255) ? 255 : (green < 0) ? 0 : (uint8_t)green;
        filteredPixels[filteredIndex + 2] = (red > 255) ? 255 : (red < 0) ? 0 : (uint8_t)red;
    }
}

BMPImage BMPMultiThreadService::applyGaussianFilter(BMPImage& image) {
    const BMPInfoHeader infoHeader = image.getInfoHeader();
    const std::vector<uint8_t> pixels = image.getPixels();
    std::vector<uint8_t> filteredPixels(image.getPixels());

    for (int y = 1; y < infoHeader.height - 1; ++y) {
        threadPool->add_task(
            gaussianFilterFunc,
            y,
            std::ref(infoHeader),
            std::ref(pixels),
            std::ref(filteredPixels)
        );
    }
    threadPool->wait_all();

    return BMPImage(image.getHeader(), infoHeader, filteredPixels);
}