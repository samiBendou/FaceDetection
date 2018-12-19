//
// Created by Sami Dahoux on 26/10/2018.
//

#define STB_IMAGE_IMPLEMENTATION

#include "ImageMatrix.h"

#include "stb/stb_image.h"

ImageMatrix::ImageMatrix(ul_t width, ul_t length, Pixel::Format format) : NPMatrix(width, length), _format(format),
                                                                          _intgr(nullptr) {

}

ImageMatrix::ImageMatrix(const NPMatrix &m, Pixel::Format format) : NPMatrix(m), _format(format),
                                                                    _intgr(nullptr) {

}

ImageMatrix::ImageMatrix(const std::string &path, Pixel::Format format)
        : NPMatrix(), _format(format), _intgr(nullptr) {
    read(path, format);
}

ImageMatrix::~ImageMatrix() {
    delete _intgr;
}

void ImageMatrix::read(const std::string &path, Pixel::Format format) {
    int x, y, n;
    stbi_uc *result = stbi_load(path.c_str(), &x, &y, &n, format);

    assert(result != nullptr);

    // Creates a matrix with the read image, x is the length and y the width, n is the number of channels

    vec_img_t vec_result;
    vec_result.assign(result, result + x * y * _format);
    *this = mat_img_t(vec_result, (ul_t) x, (ul_t) y * _format);
}

void ImageMatrix::write(const std::string &path, Pixel::Format format) {
    // TODO : Implement writing to .png or .jpeg format via STBJ
}

mat_img_t ImageMatrix::intgr() const {

    mat_img_t img(n(), p()), sum(n(), p());
    uc_t format_nbr_channels = (uc_t) _format;

    // Initial values setup

    img(0, 0) = this->operator()(0, 0);
    for (ul_t index = 1; index < p() / format_nbr_channels; ++index) {
        img(0, index) = img(0, index - 1) + this->operator()(0, index - 1);
        img(index, 0) = img(index - 1, 0) + this->operator()(index - 1, 0);
    }

    sum.setCol(col(0), 0);

    // Computing integral image using recurrence formula

    for (ul_t x = 1; x < n(); ++x) {
        for (ul_t y = 1; y < p() / format_nbr_channels; ++y) {
            for (char f = 0; f < format_nbr_channels; ++f) {
                sum(x, y + f) = sum(x, y - 1 + f) + this->operator()(x, y + f);
                img(x, y + f) = img(x - 1, y + f) + sum(x, y + f);
            }
        }
    }
    _intgr = new ImageMatrix(img);

    return img;
}

i_t ImageMatrix::sumWithin(ul_t x1, ul_t y1, ul_t x2, ul_t y2) {
    if (_intgr == nullptr) {
        intgr();
    }

    return (*_intgr)(x1, y1) + (*_intgr)(x2, y2) - (*_intgr)(x1, y2) - (*_intgr)(x2, y1);
}




