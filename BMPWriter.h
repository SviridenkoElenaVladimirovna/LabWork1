#ifndef BMPWRITER_H
#define BMPWRITER_H

#include <string>
#include <fstream>
#include "BMPImage.h"

class BMPWriter {
public:
    static void saveToFile(const BMPImage& image,const std::string& filepath);
};

#endif 