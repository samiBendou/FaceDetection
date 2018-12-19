//
// Created by Sami Dahoux on 26/10/2018.
//

#ifndef FACEDETECTION_IMAGEMATRIX_H
#define FACEDETECTION_IMAGEMATRIX_H


#include <string>
#include <NPMatrix.h>


typedef NPMatrix<i_t> mat_img_t;
typedef NVector<i_t> vec_img_t;

class ImageMatrix : public mat_img_t {

public:

    using mat_img_t::operator=;

    enum Format {
        GScale = 1, RGB = 3, Default = 1
    };

    ImageMatrix(ul_t width = 0, ul_t length = 0, Format format = Default);

    ImageMatrix(const NPMatrix &m, Format format = Default);

    ~ImageMatrix();

    explicit ImageMatrix(const std::string &path, Format format = GScale);

    void read(const std::string &path, Format format = Default);

    void write(const std::string &path, Format format = Default);

    mat_img_t intgr() const;

    i_t sumWithin(ul_t x1, ul_t y1, ul_t x2, ul_t y2);


private:

    Format _format = Default;

    mutable mat_img_t *_intgr = nullptr;
};

#endif //FACEDETECTION_IMAGEMATRIX_H
