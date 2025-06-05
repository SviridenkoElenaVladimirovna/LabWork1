/*
Sviridenko Elena st130482@student.spbu.ru
Loads and processes a BMP raster image, rotates the image 90 clockwise and counterclockwise, applies a Gaussian filter to the image
added multithreading
*/

/**
 * @file BMPHeader.h
 * @brief Defines the BMP file header structure.
 */

#ifndef BMPHEADER_H
#define BMPHEADER_H

#include <cstdint>

#pragma pack(push, 1)
/**
 * @struct BMPHeader
 * @brief A structure describing the main header of a BMP file.
 */
struct BMPHeader {
    char id[2];
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t offset;
};
#pragma pack(pop)

#endif
