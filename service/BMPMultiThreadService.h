/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
*/
#ifndef BMPMULTITHREADSERVICE_H
#define BMPMULTITHREADSERVICE_H

#include "BMPImage.h"
#include "ThreadPool.h"
/**
 * @class BMPMultiThreadService
 * @brief A class for processing BMP images using multithreading.
 *
 * Realizes image rotation by 90 degrees (clockwise and counterclockwise) and
 * applying Gaussian filter with parallelization
 */
class BMPMultiThreadService {
private:
    ThreadPool* threadPool;
public:
    BMPMultiThreadService(const int numberOfThreads);
    BMPImage rotateClockwise(BMPImage& image);
    BMPImage rotateCounterclockwise(BMPImage& image);
    BMPImage applyGaussianFilter(BMPImage& image);
};

#endif