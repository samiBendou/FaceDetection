#include <gtest/gtest.h>
#include <IMatrix.h>

class IMatrixTest : public ::testing::Test {
};

TEST_F(IMatrixTest, Read) {

    // IMatrix loaded from local images
    IMatrix white("../img/test/blank_white.png", Pixel::RGB),
            black("../img/test/blank_black.png", Pixel::GScale),
            red("../img/test/blank_red.png", Pixel::RGB);

    // Expected results
    IMatrix fill_0{mat_pix_t::zeros(white.width(), white.height())},
            fill_255 = fill_0,
            fill_red = fill_0;

    fill_255.fill(Pixel(255, 255, 255));
    fill_red.fill(Pixel(255, 0, 0));



    ASSERT_EQ(white.width(), 10);
    ASSERT_EQ(white.height(), 10);

    std::cout << white << std::endl << fill_255;

    EXPECT_EQ(white, fill_255);
    EXPECT_EQ(black, fill_0);

    std::cout << red << std::endl << fill_red;

    EXPECT_EQ(red, fill_red);
}

TEST_F(IMatrixTest, Integral) {
    IMatrix fill_1{mat_pix_t::zeros(10)}, expect_intgr{mat_pix_t::zeros(10)};
    fill_1.fill(1);

    // Known integral image
    for (size_t x = 1; x <= 10; ++x) {
        for (size_t y = 1; y <= 10; ++y) {
            expect_intgr(x - 1, y - 1) = x * y;
        }
    }

    ASSERT_EQ(expect_intgr, fill_1.intgr());
}

TEST_F(IMatrixTest, SumWithin) {
    IMatrix fill_1{mat_pix_t::zeros(10)};
    fill_1.fill(1);

    ASSERT_EQ(fill_1.sumWithin(0, 0, 1, 1), 4);
}