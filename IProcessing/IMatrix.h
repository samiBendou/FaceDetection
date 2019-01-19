/**
 * @class          : IMatrix
 * @date           : 26/10/2018
 * @author         : samiBendou
 * @brief          : Represents an image of type .jpeg or .png.
 *                   This class is an instanciation of template NPMatrix with type Pixel. (cf. Pixel class).
 *                   The IMatrix class provide method for image processing and is especially
 *                   designed to achieve calculation of Pseudo-Haar features using image integral representation.
 *
 *                   All allong the folowing code we will use theses notations :
 *                      - x,i/y,j : Row/Col. indice for an image
 *                      - index : Compound index
 *
 * @copybrief      : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef FACEDETECTION_IMAGEMATRIX_H
#define FACEDETECTION_IMAGEMATRIX_H


#include <string>
#include <NPMatrix.h>
#include <stb_image.h>

class IMatrix : public mat_pix_t {

public:

    using mat_pix_t::operator=;


    // CONSTRUCTOR

    IMatrix(const IMatrix &img);

    /**
     *
     * @brief Construct by copy a new image matrix with given matrix m
     */
    IMatrix(const mat_pix_t &m, bool limited = false);

    /**
     *
     * @brief Construct zero image with given width and height
     */
    explicit IMatrix(size_t width = 0, size_t height = 0, Pixel::Format format = Pixel::GScale, bool limited = false);

    /**
     * @brief Construct image by reading image at path (relative path)
     */
    explicit IMatrix(const std::string &path, Pixel::Format format = Pixel::GScale, bool limited = false);

    ~IMatrix();

    // GETTERS

    inline size_t width() const {return n();}

    inline size_t height() const {return p();}


    // FILE ACCESS
    /**
     * @brief   Uses std_image.h to read an image at path location. The IMatrix object is set to the ridden image
     *          after function call.
     * @param path string of relative path of the image
     */
    void read(const std::string &path, Pixel::Format format = Pixel::GScale);

    void write(const std::string &path, Pixel::Format format = Pixel::GScale);

    // MANIPULATORS

    /**
     * @brief Computes image integral calculation. For mor details : [ref wiki]
     * @return integral image stored as an unlimited IMatrix
     */

    mat_pix_t & intgr() const;

    inline IMatrix &gsToRgb() {
        forEach(0, [](Pixel &p1, Pixel none) { p1.setRGB(p1.grey(), p1.grey(), p1.grey()); });
        return *this;
    }

    inline IMatrix &rgbToGs() {
        forEach(0, [](Pixel &p1, Pixel none) { p1.setGrey(p1.grey()); });
        return *this;
    }

    /**
     *
     * @param x1/x2 x coordinate of left upper/right lower point of rectangle
     * @param y1/y2 y coordinate of left upper/right lower point of rectangle
     * @return  value in pixel of the sum of pixels values within the rectangle ABCD where :
     *          - A : (x1, y1), -B : (x2, y1), -C : (x2, y2), -D : (x1, y2)
     *          for example sumWithin(0, 0, 3, 3) will return the sum of the pixels comprised between
     *          the point (0, 0) and (2, 2).
     */
    Pixel sumWithin(size_t x1, size_t y1, size_t x2, size_t y2);

private:

    Pixel::Format _format{};
    bool _limited{};

    mutable std::unique_ptr<mat_pix_t>_intgr{nullptr};
};

#endif //FACEDETECTION_IMAGEMATRIX_H
