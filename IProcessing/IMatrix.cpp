//
// Created by Sami Dahoux on 26/10/2018.
//

#define STB_IMAGE_IMPLEMENTATION

#include "IMatrix.h"



// CONSTRUCTOR

IMatrix::IMatrix(const IMatrix &img) : NPMatrix(img),
                                                   _format(img._format),
                                                   _limited(img._limited),
                                                   _intgr(nullptr) {
    if (img._intgr != nullptr)
        _intgr.reset(new IMatrix((mat_pix_t) *(img._intgr), img._format));
}


IMatrix::IMatrix(const std::string &path, Pixel::Format format, bool limited)
        : NPMatrix(), _format(format), _intgr(nullptr) {
    read(path, format);
}

IMatrix::IMatrix(size_t width, size_t height, Pixel::Format format, bool limited) : NPMatrix(width, height),
                                                                                        _format(format),
                                                                                        _limited(limited),
                                                                                        _intgr(nullptr) {
    format == Pixel::GScale ? rgbToGs() : gsToRgb();
}

IMatrix::IMatrix(const mat_pix_t &m, bool limited) : NPMatrix(m),
                                                            _format(m(0, 0).format()),
                                                            _limited(limited),
                                                            _intgr(nullptr) {
    copy(m);
}

// FILE ACCESS

void IMatrix::read(const std::string &path, Pixel::Format format) {
    int x, y, n, channels_format = format == Pixel::GScale ? 1 : 3;
    stbi_uc *result = stbi_load(path.c_str(), &x, &y, &n, channels_format);

    assert(result != nullptr);

    // Creates a matrix with the read image, x is the length and y the width, n is the number of channels
    mat_pix_t read_mat = mat_pix_t((size_t) x, (size_t) y);
    size_t base;
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y * channels_format; j += channels_format) {
            base = (channels_format * y) * i + j;
            if (channels_format == 3)
                read_mat(i, j / channels_format) = Pixel(result[base], result[base + 1], result[base + 2], _limited);
            else
                read_mat(i, j) = Pixel(result[base], _limited);
        }
    }
    copy(read_mat);
    delete[] result;
}


void IMatrix::write(const std::string &path, Pixel::Format format) {
    // TODO : Implement writing to .png or .jpeg format via STBJ
}

// MANIPULATORS

mat_pix_t & IMatrix::intgr() const {

    mat_pix_t img(width() + 1, height() + 1), sum(width() + 1, height() + 1);

    // Computing integral image using recurrence formula
    for (size_t x = 1; x <= width(); ++x) {
        for (size_t y = 1; y <= height(); ++y) {
            sum(x, y) = sum(x, y - 1) + (*this)(x - 1, y - 1);
            img(x, y) = img(x - 1, y) + sum(x, y);
        }
    }
    _intgr.reset(new mat_pix_t(img(1, 1, width(), height())));
    return *_intgr;
}

Pixel IMatrix::sum(size_t x1, size_t y1, size_t x2, size_t y2) const {
    if (_intgr == nullptr) {
        intgr();
    }
    return (*_intgr)(x1, y1) + (*_intgr)(x2, y2) - (*_intgr)(x1, y2) - (*_intgr)(x2, y1);
}

void IMatrix::intgrCopy(const IMatrix &img) {
    if(img._intgr) {
        *_intgr = mat_pix_t(*(img._intgr));
    } else {
        _intgr.reset(nullptr);
    }
}







