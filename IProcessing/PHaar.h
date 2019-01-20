//
// Created by bendou on 20/01/19.
//

#ifndef FACEDETECTION_PHAARFEATURE_H
#define FACEDETECTION_PHAARFEATURE_H

#include <IMatrix.h>

#define P_HAAR_FEATURE_DEFAULT_SIZE 24


class PHaar {

public:

    enum Type {
        TwoRectW, TwoRectH, ThreeRect, FourRect
    };

    PHaar(
            size_t x,
            size_t y,
            size_t w = P_HAAR_FEATURE_DEFAULT_SIZE,
            size_t h = P_HAAR_FEATURE_DEFAULT_SIZE,
            Type type = TwoRectW) :

            x(x), y(y), w(w), h(h), type(type) {}

    Pixel operator()(const IMatrix &img) const;

    size_t x, y, w, h;
    Type type;

};


#endif //FACEDETECTION_PHAARFEATURE_H
