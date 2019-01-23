#include <gtest/gtest.h>
#include <PHaar.h>

class PHaarTest : public ::testing::Test {
public:
    PHaar f{0, 0, 10, 10};
};

TEST_F(PHaarTest, FunctionOp) {

    IMatrix test_img("../img/test/blank_white.png", Pixel::GScale);
    EXPECT_EQ(f(test_img), false);

    f.type = PHaar::Type::TwoRectH;
    EXPECT_EQ(f(test_img), false);

    f.type = PHaar::Type::FourRect;
    EXPECT_EQ(f(test_img), false);
}



