#ifndef BMPREADER_H
#define BMPREADER_H

#include <string>
#include <fstream>
#include "BMPImage.h"

class BMPReader {
public:
    static BMPImage loadFromFile(const std::string& filepath);
};

#endif 