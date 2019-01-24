//
// Created by bendou on 20/01/19.
//

#ifndef FACEDETECTION_WCLASSIFIER_H
#define FACEDETECTION_WCLASSIFIER_H


#include "PHaar.h"

#define W_CLASSIFIER_DEFAULT_POL (false)
#define W_CLASSIFIER_DEFAULT_THETA 0.0


class WClassifier {
public:
    WClassifier(const PHaar &f0, double_t theta0 = W_CLASSIFIER_DEFAULT_THETA, bool pol0 = W_CLASSIFIER_DEFAULT_POL) :
            f(f0), _theta(theta0), _pol(pol0) {}

    inline bool operator()(const IMatrix& img) {return _pol ? f(img) < _theta :  f(img) > _theta;}

    double_t train(const vec_t &w, const std::vector<IMatrix> &x, const std::vector<bool> &y);

    double_t bary(const vec_t &w, const std::vector<IMatrix> &x, const std::vector<bool> &y) const;

    double_t fnr(const std::vector<IMatrix> &x, const std::vector<bool> &y);

    double_t fpr(const std::vector<IMatrix> &x, const std::vector<bool> &y);

    PHaar f;

protected:

    double_t _theta;
    bool _pol;

};


#endif //FACEDETECTION_WCLASSIFIER_H
