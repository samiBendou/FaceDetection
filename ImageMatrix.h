/**
 * @class          : ImageMatrix
 * @date           : 26/10/2018
 * @author         : samiBendou
 * @description    : An ImageMatrix inherits from NPMatrix. It's an instanciation of NPMatrix with type Pixel.
 *                   ImageMatrix objects represents an image of type .jpeg or .png with a given color scale
 *                   (cf. Pixel class). All allong the folowing code we will use theses notations :
 *                      - x,i/y,j : Row/Col. indice for an image
 *                      - index : Compound index
 *                   The ImageMatrix class provide method for image processing and is especially
 *                   designed to achieve calculation of Pseudo-Haar characteristics using image integral representation.
 *
 *                   The class uses package NAlgebra and STB image.
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef FACEDETECTION_IMAGEMATRIX_H
#define FACEDETECTION_IMAGEMATRIX_H


#include <string>
#include <NPMatrix.h>

class ImageMatrix : public mat_pix_t {

public:

    using mat_pix_t::operator=;


    explicit ImageMatrix(ul_t width = 0, ul_t length = 0, Pixel::Format format = Pixel::GScale, bool limited = false);

    ImageMatrix(const NPMatrix &m, Pixel::Format format = Pixel::GScale, bool limited = false);

    ~ImageMatrix();

    explicit ImageMatrix(const std::string &path, Pixel::Format format = Pixel::GScale, bool limited = false);

    void read(const std::string &path, Pixel::Format format = Pixel::GScale);

    void write(const std::string &path, Pixel::Format format = Pixel::GScale);

    ImageMatrix intgr() const;

    Pixel sumWithin(ul_t x1, ul_t y1, ul_t x2, ul_t y2);

private:

    Pixel::Format _format;
    bool _limited;

    mutable mat_pix_t *_intgr = nullptr;
};

#endif //FACEDETECTION_IMAGEMATRIX_H
