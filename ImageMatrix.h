/**
 * @class          : ImageMatrix
 * @date           : 26/10/2018
 * @author         : samiBendou
 * @description    : An ImageMatrix inherits from NPMatrix. It's an instanciation of NPMatrix with type Pixel.
 *                   ImageMatrix objects represents an image of type .jpeg or .png with a given color scale
 *                   (cf. Pixel class). All allong the folowing code we will use theses notations :
 *                      - x/y : Row/Col. indice for an image
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


typedef NPMatrix<i_t> mat_img_t;
typedef NVector<i_t> vec_img_t;

class ImageMatrix : public mat_img_t {

public:

    using mat_img_t::operator=;


    ImageMatrix(ul_t width = 0, ul_t length = 0, Pixel::Format format = Pixel::GScale);

    ImageMatrix(const NPMatrix &m, Pixel::Format format = Pixel::GScale);

    ~ImageMatrix();

    explicit ImageMatrix(const std::string &path, Pixel::Format format = Pixel::GScale);

    void read(const std::string &path, Pixel::Format format = Pixel::GScale);

    void write(const std::string &path, Pixel::Format format = Pixel::GScale);

    mat_img_t intgr() const;

    i_t sumWithin(ul_t x1, ul_t y1, ul_t x2, ul_t y2);


private:

    Pixel::Format _format = Pixel::GScale;

    mutable mat_img_t *_intgr = nullptr;
};

#endif //FACEDETECTION_IMAGEMATRIX_H
