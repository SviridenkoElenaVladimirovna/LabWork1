/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
added multithreading
*/
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include "../model/BMPImage.h"
#include "../service/BMPMultiThreadService.h"
#include "../io/BMPReader.h"
#include "../service/BMPService.h"
#include "../io/BMPWriter.h"

void printRealizationsComparing(
    std::vector<long> oneThreadElapsedTime,
    std::vector<long> multiThreadElapsedTime,
    int numberOfThreads) {
    std::cout << "Comparing of elapsed time in ms between one thread and multi thread realizations" << std::endl;
    std::cout << "==============================================" << std::endl;

    std::cout << "One thread" <<
            std::setw(3) << "|" << std::setw(3) <<
            numberOfThreads << " threads" <<
            std::setw(1) << "|" <<
            std::endl;

    for (int i = 0; i < oneThreadElapsedTime.size(); i++) {
        std::cout << "|" << std::setw(6) <<
                oneThreadElapsedTime.at(i) <<
                std::setw(6) << "|" << std::setw(6) <<
                multiThreadElapsedTime.at(i) <<
                std::setw(6) << "|" <<
                std::endl;
    }
    std::cout << "==============================================" << std::endl;
}

int main() {
    const std::string filepath = "image.bmp";
    const std::string clockwiseFilepath = "rotated_clockwise.bmp";
    const std::string counterclockwiseFilepath = "rotated_counterclockwise.bmp";
    const std::string gaussianFilterFilepath = "filtered_image.bmp";

    BMPImage image = BMPReader::loadFromFile(filepath);
    const int NUMBER_OF_THREADS = 2;

    auto multiThreadService = BMPMultiThreadService(NUMBER_OF_THREADS);
    std::vector<long> oneThreadElapsedTime = std::vector<long>();
    std::vector<long> multiThreadElapsedTime = std::vector<long>();

    auto begin = std::chrono::steady_clock::now();
    BMPService::rotateClockwise(image);
    auto end = std::chrono::steady_clock::now();
    oneThreadElapsedTime.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    BMPImage clockwiseRotated = multiThreadService.rotateClockwise(image);
    end = std::chrono::steady_clock::now();
    BMPWriter::saveToFile(clockwiseRotated, clockwiseFilepath);
    multiThreadElapsedTime.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    BMPService::rotateCounterclockwise(image);
    end = std::chrono::steady_clock::now();
    oneThreadElapsedTime.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    BMPImage counterclockwiseRotated = multiThreadService.rotateCounterclockwise(image);
    end = std::chrono::steady_clock::now();
    BMPWriter::saveToFile(counterclockwiseRotated, counterclockwiseFilepath);
    multiThreadElapsedTime.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    BMPService::applyGaussianFilter(image);
    end = std::chrono::steady_clock::now();
    oneThreadElapsedTime.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    begin = std::chrono::steady_clock::now();
    BMPImage gaussianFiltered = multiThreadService.applyGaussianFilter(image);
    end = std::chrono::steady_clock::now();
    BMPWriter::saveToFile(gaussianFiltered, gaussianFilterFilepath);
    multiThreadElapsedTime.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    printRealizationsComparing(oneThreadElapsedTime, multiThreadElapsedTime, NUMBER_OF_THREADS);

    std::cout << "Images successfully processed and saved" << std::endl;
    return 0;
}
