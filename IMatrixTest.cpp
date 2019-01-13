#include <gtest/gtest.h>
#include <IMatrix.h>

class IMatrixTest : public ::testing::Test {
};

TEST_F(IMatrixTest, Read) {

    // IMatrix loaded from local images
    IMatrix white("../img/test/blank_white.jpg", Pixel::RGB),
                black("../img/test/blank_black.jpg", Pixel::GScale),
                red("../img/test/blank_red.jpg", Pixel::RGB),
                green("../img/test/blank_green.jpg", Pixel::RGB),
                blue("../img/test/blank_blue.jpg", Pixel::RGB);

    // Expected results
    IMatrix fill_0{mat_pix_t::zeros(white.width(), white.height())},
                fill_1 = fill_0,
                fill_red = fill_0,
                fill_green = fill_0,
                fill_blue = fill_0;

    fill_1.fill(1);
    fill_red.fill(Pixel(255, 0, 0));
    fill_green.fill(Pixel(0, 255, 0));
    fill_blue.fill(Pixel(0, 0, 255));

    ASSERT_EQ(white.width(), 10);
    ASSERT_EQ(white.height(), 10);

    ASSERT_EQ(white, fill_1);
    ASSERT_EQ(black, fill_0);
    ASSERT_EQ(red, fill_red);
    ASSERT_EQ(green, fill_green);
    ASSERT_EQ(blue, fill_blue);
}

TEST_F(IMatrixTest, Integral) {
    IMatrix fill_1{mat_pix_t::zeros(10)}, expect_intgr{mat_pix_t::zeros(10)};
    fill_1.fill(1);

    for (size_t x = 0; x < 10; ++x) {
        for (size_t y = 0; y < 10; ++y) {
            expect_intgr(x, y) = x + y;
        }
    }

    ASSERT_EQ(expect_intgr, fill_1);
}

TEST_F(IMatrixTest, SumWithin) {
    IMatrix fill_1{mat_pix_t::zeros(10)};
    fill_1.fill(1);

    ASSERT_EQ(fill_1.sumWithin(0, 0, 2, 2), 4);
}