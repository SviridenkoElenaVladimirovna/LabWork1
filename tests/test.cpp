#include <gtest/gtest.h>
#include "../model/BMPImage.h"
#include "../service/BMPService.h"
#include "../service/BMPMultiThreadService.h"
#include "../io/BMPReader.h"
#include "../io/BMPWriter.h"

bool imagesAreEqual(const BMPImage& img1, const BMPImage& img2) {
    if (img1.getInfoHeader().width != img2.getInfoHeader().width ||
        img1.getInfoHeader().height != img2.getInfoHeader().height ||
        img1.getPixels().size() != img2.getPixels().size()) {
        return false;
    }

    const auto& pixels1 = img1.getPixels();
    const auto& pixels2 = img2.getPixels();

    for (size_t i = 0; i < pixels1.size(); ++i) {
        if (pixels1[i] != pixels2[i]) {
            return false;
        }
    }
    return true;
}

class ImageProcessingTest : public ::testing::Test {
protected:
    BMPImage img;
    BMPMultiThreadService multiThreadService;

    ImageProcessingTest() : multiThreadService(2) {}

    void SetUp() override {
        img = BMPReader::loadFromFile("tests/image.bmp");
    }
};

TEST_F(ImageProcessingTest, RotateClockwise_MultiEqualsSingleThreaded) {
BMPImage single = BMPService::rotateClockwise(img);
BMPImage multi = multiThreadService.rotateClockwise(img);
ASSERT_TRUE(imagesAreEqual(single, multi));
}

TEST_F(ImageProcessingTest, RotateCounterclockwise_MultiEqualsSingleThreaded) {
BMPImage single = BMPService::rotateCounterclockwise(img);
BMPImage multi = multiThreadService.rotateCounterclockwise(img);
ASSERT_TRUE(imagesAreEqual(single, multi));
}

TEST_F(ImageProcessingTest, GaussianFilter_MultiEqualsSingleThreaded) {
BMPImage single = BMPService::applyGaussianFilter(img);
BMPImage multi = multiThreadService.applyGaussianFilter(img);
ASSERT_TRUE(imagesAreEqual(single, multi));
}
TEST_F(ImageProcessingTest, RotateClockwiseThenCounterclockwise_EqualsOriginal) {
    BMPImage rotated = BMPService::rotateClockwise(img);
    BMPImage back = BMPService::rotateCounterclockwise(rotated);
    ASSERT_TRUE(imagesAreEqual(img, back));
}

TEST_F(ImageProcessingTest, RotateClockwiseFourTimes_EqualsOriginal) {
    BMPImage rotated = img;
    for (int i = 0; i < 4; ++i) {
        rotated = BMPService::rotateClockwise(rotated);
    }
    ASSERT_TRUE(imagesAreEqual(img, rotated));
}

TEST_F(ImageProcessingTest, ApplyGaussianTwice_NotEqualToOnce) {
    BMPImage onceFiltered = BMPService::applyGaussianFilter(img);
    BMPImage twiceFiltered = BMPService::applyGaussianFilter(onceFiltered);
    ASSERT_FALSE(imagesAreEqual(onceFiltered, twiceFiltered));
}

TEST_F(ImageProcessingTest, RotateAndSaveImage) {
    BMPImage rotated = BMPService::rotateClockwise(img);
    BMPWriter::saveToFile(rotated, "tests/rotated_test.bmp");
    BMPImage loaded = BMPReader::loadFromFile("tests/rotated_test.bmp");
    ASSERT_TRUE(imagesAreEqual(rotated, loaded));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
