
#ifndef BMPINFOHEADER_H
#define BMPINFOHEADER_H
#include <cstdint>

#pragma pack(push, 1)
struct  BMPInfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t dataSize;
    int32_t hResolution;
    int32_t vResolution;
    uint32_t colors;
    uint32_t importantColors;
};
#pragma pack(pop)

#endif
