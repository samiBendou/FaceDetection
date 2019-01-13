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
#include <stb_image.h>

class ImageMatrix : public mat_pix_t {

public:

    using mat_pix_t::operator=;


    // CONSTRUCTOR

    ImageMatrix(const ImageMatrix &img);

    /**
     *
     * @brief Construct by copy a new image matrix with given matrix m
     */
    ImageMatrix(const NPMatrix &m, bool limited = false);

    /**
     *
     * @brief Construct zero image with given width and height
     */
    explicit ImageMatrix(ul_t width = 0, ul_t height = 0, Pixel::Format format = Pixel::GScale, bool limited = false);

    /**
     * @brief Construct image by reading image at path (relative path)
     */
    explicit ImageMatrix(const std::string &path, Pixel::Format format = Pixel::GScale, bool limited = false);

    ~ImageMatrix();

    // GETTERS

    ul_t width() const;

    ul_t height() const;


    // FILE ACCESS
    /**
     * @brief   Uses std_image.h to read an image at path location. The ImageMatrix object is set to the ridden image
     *          after function call.
     * @param path string of relative path of the image
     */
    void read(const std::string &path, Pixel::Format format = Pixel::GScale);

    void write(const std::string &path, Pixel::Format format = Pixel::GScale);

    // MANIPULATORS

    /**
     * @brief Computes image integral calculation. For mor details : [ref wiki]
     * @return integral image stored as an unlimited ImageMatrix
     */

    ImageMatrix intgr() const;

    ImageMatrix &gsToRgb();

    ImageMatrix &rgbToGs();

    ImageMatrix &conformFormatTo(const mat_pix_t &img);


    /**
     *
     * @param x1/x2 x coordinate of left upper/right lower point of rectangle
     * @param y1/y2 y coordinate of left upper/right lower point of rectangle
     * @return  value in pixel of the sum of pixels values within the rectangle ABCD where :
     *          - A : (x1, y1), -B : (x2, y1), -C : (x2, y2), -D : (x1, y2)
     *          for example sumWithin(0, 0, 3, 3) will return the sum of the pixels comprised between
     *          the point (0, 0) and (2, 2).
     */
    Pixel sumWithin(ul_t x1, ul_t y1, ul_t x2, ul_t y2);

private:

    Pixel::Format _format;
    bool _limited;

    mutable mat_pix_t *_intgr = nullptr;
};

#endif //FACEDETECTION_IMAGEMATRIX_H
