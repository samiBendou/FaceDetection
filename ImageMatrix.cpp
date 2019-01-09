//
// Created by Sami Dahoux on 26/10/2018.
//

#define STB_IMAGE_IMPLEMENTATION

#include "ImageMatrix.h"

#include "stb/stb_image.h"

// CONSTRUCTOR

ImageMatrix::ImageMatrix(const ImageMatrix &img) : NPMatrix(img),
                                                   _format(img._format),
                                                   _limited(img._limited),
                                                   _intgr(nullptr) {
    if (img._intgr != nullptr)
        _intgr = new ImageMatrix((mat_pix_t) *(img._intgr), img._format);
}


ImageMatrix::ImageMatrix(const std::string &path, Pixel::Format format, bool limited)
        : NPMatrix(), _format(format), _intgr(nullptr) {
    read(path, format);
}

ImageMatrix::ImageMatrix(ul_t width, ul_t height, Pixel::Format format, bool limited) : NPMatrix(width, height),
                                                                                        _format(format),
                                                                                        _limited(limited),
                                                                                        _intgr(nullptr) {
    format == Pixel::GScale ? rgbToGs() : gsToRgb();
}

ImageMatrix::ImageMatrix(const NPMatrix &m, bool limited) : NPMatrix(m),
                                                            _format(m(0, 0).format()),
                                                            _limited(limited),
                                                            _intgr(nullptr) {
    conformFormatTo(m);
}

ImageMatrix::~ImageMatrix() {
    delete _intgr;
}

// GETTERS

ul_t ImageMatrix::width() const {
    return n();
}

ul_t ImageMatrix::height() const {
    return p();
}

// FILE ACCESS

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

// MANIPULATORS

ImageMatrix ImageMatrix::intgr() const {

    ImageMatrix img(width(), height(), _format), sum(width(), height(), _format);

    // Initial values setup
    for (ul_t index = 1; index < height(); ++index) {
        img(0, index) = img(0, index - 1) + (*this)(0, index - 1);
        img(index, 0) = img(index - 1, 0) + (*this)(index - 1, 0);
    }

    sum.setCol(col(0), 0);

    // Computing integral image using recurrence formula
    for (ul_t x = 1; x < width(); ++x) {
        for (ul_t y = 1; y < height(); ++y) {
            sum(x, y) = sum(x, y - 1) + (*this)(x, y);
            img(x, y) = img(x - 1, y) + sum(x, y);
        }
    }
    _intgr = new ImageMatrix(img, _format);
    return *_intgr;
}

ImageMatrix &ImageMatrix::gsToRgb() {
    int grey;
    for (ul_t x = 0; x < width(); ++x) {
        for (ul_t y = 0; y < height(); ++y) {
            grey = (*this)(x, y).greyScale();
            (*this)(x, y).setRGB(grey, grey, grey);
        }
    }
    return *this;
}

ImageMatrix &ImageMatrix::conformFormatTo(const mat_pix_t &img) {
    for (ul_t x = 0; x < width(); ++x) {
        for (ul_t y = 0; y < height(); ++y) {
            (*this)(x, y).conformFormatTo(img(0, 0));
        }
    }
    return *this;
}

ImageMatrix &ImageMatrix::rgbToGs() {
    for (ul_t x = 0; x < width(); ++x) {
        for (ul_t y = 0; y < height(); ++y) {
            (*this)(x, y).setGreyScale((*this)(x, y).greyScale());
        }
    }
    return *this;
}

Pixel ImageMatrix::sumWithin(ul_t x1, ul_t y1, ul_t x2, ul_t y2) {
    if (_intgr == nullptr) {
        intgr();
    }

    return (*_intgr)(x1, y1) + (*_intgr)(x2, y2) - (*_intgr)(x1, y2) - (*_intgr)(x2, y1);
}







