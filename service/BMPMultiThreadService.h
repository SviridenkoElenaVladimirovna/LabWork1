/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
added multithreading
*/
#ifndef BMPMULTITHREADSERVICE_H
#define BMPMULTITHREADSERVICE_H

#include "../model/BMPImage.h"
#include "../utils/ThreadPool.h"

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
