
#ifndef BMPHEADER_H
#define BMPHEADER_H

#include <cstdint>

#pragma pack(push, 1)
struct  BMPHeader {
    char id[2];
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t offset;
};
#pragma pack(pop)

#endif
