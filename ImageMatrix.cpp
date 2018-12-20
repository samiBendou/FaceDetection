//
// Created by Sami Dahoux on 26/10/2018.
//

#define STB_IMAGE_IMPLEMENTATION

#include "ImageMatrix.h"

#include "stb/stb_image.h"

ImageMatrix::ImageMatrix(ul_t width, ul_t length, Pixel::Format format, bool limited) : NPMatrix(width, length),
                                                                                        _format(format),
                                                                                        _limited(limited),
                                                                                        _intgr(nullptr) {

}

ImageMatrix::ImageMatrix(const NPMatrix &m, Pixel::Format format, bool limited) : NPMatrix(m),
                                                                                  _format(format), _limited(limited),
                                                                                  _intgr(nullptr) {

}

ImageMatrix::ImageMatrix(const std::string &path, Pixel::Format format, bool limited)
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
    *this = mat_pix_t((ul_t) x, (ul_t) y);
    ul_t base;
    for (ul_t i = 0; i < x; ++i) {
        for (ul_t j = 0; j < y * _format; j += _format) {
            base = (_format * y) * i + j;
            if (_format == Pixel::RGB)
                (*this)(i, j / _format) = Pixel(result[base], result[base + 1], result[base + 2], _limited);
            else
                (*this)(i, j) = Pixel(result[base], _limited);
        }
    }
}

void ImageMatrix::write(const std::string &path, Pixel::Format format) {
    // TODO : Implement writing to .png or .jpeg format via STBJ
}

ImageMatrix ImageMatrix::intgr() const {

    ImageMatrix img(n(), p()), sum(n(), p());

    // Initial values setup
    img(0, 0) = (*this)(0, 0);
    for (ul_t index = 1; index < p(); ++index) {
        img(0, index) = img(0, index - 1) + (*this)(0, index - 1);
        img(index, 0) = img(index - 1, 0) + (*this)(index - 1, 0);
    }

    sum.setCol(col(0), 0);

    // Computing integral image using recurrence formula
    for (ul_t x = 1; x < n(); ++x) {
        for (ul_t y = 1; y < p(); ++y) {
            sum(x, y) = sum(x, y - 1) + (*this)(x, y);
            img(x, y) = img(x - 1, y) + sum(x, y);
        }
    }
    _intgr = new ImageMatrix(img);

    return img;
}

Pixel ImageMatrix::sumWithin(ul_t x1, ul_t y1, ul_t x2, ul_t y2) {
    if (_intgr == nullptr) {
        intgr();
    }

    return (*_intgr)(x1, y1) + (*_intgr)(x2, y2) - (*_intgr)(x1, y2) - (*_intgr)(x2, y1);
}




