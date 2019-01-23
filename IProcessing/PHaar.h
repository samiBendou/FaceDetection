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
            size_t x0,
            size_t y0,
            size_t w0 = P_HAAR_FEATURE_DEFAULT_SIZE,
            size_t h0 = P_HAAR_FEATURE_DEFAULT_SIZE,
            Type type0 = TwoRectW) :

            x(x0), y(y0), w(w0), h(h0), type(type0) {}

    inline PHaar& move(size_t hx, size_t hy) {x += hx; y += hy; return *this;}

    inline PHaar& scale(size_t sw, size_t sy) {w *= sw; h *= sy; return *this;}

    double_t operator()(const IMatrix &img) const;

    size_t x, y, w, h;
    Type type;

};


#endif //FACEDETECTION_PHAARFEATURE_H
