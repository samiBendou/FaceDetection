//
// Created by bendou on 20/01/19.
//

#include "WClassifier.h"

double_t WClassifier::train(const vec_t &w, const std::vector<IMatrix> &x, const std::vector<bool> &y) {
    size_t size = x.size();
    double_t error_pp = w | vec_t::ones(size), error_pn = error_pp;

    _theta = bary(w, x, y);
    for (int k = 0; k < size; ++k) {
        //Adds error on the where the prediction is false
        ((y[k] ^ (*this)(x[k])) ? error_pp : error_pn) -= w[k];
    }

    _pol = error_pp < error_pn;
    return _pol ? error_pp : error_pn;
}

double_t
WClassifier::bary(const vec_t &w, const std::vector<IMatrix> &x, const std::vector<bool> &y) const {
    double_t theta_p = 0.0, theta_n = 0.0, sum_wp = 0.0, sum_wn = 0.0;

    for (int k = 0; k < x.size(); ++k) {
        // Weights must be ordered the same way as training images
        (y[k] ? (theta_p) : (theta_n)) += w[k] * f(x[k]);
        (y[k] ? (sum_wp) : (sum_wn)) += w[k];
    }

    return 0.5 * theta_p / (sum_wp > 0 ? sum_wp : 1) + theta_n / (sum_wn > 0 ? sum_wp : 1);
}

double_t WClassifier::fnr(const std::vector<IMatrix> &x, const std::vector<bool> &y) {
    double_t fnr = 0.0;
    size_t size = x.size();
    for (int k = 0; k < size; ++k) {
        fnr += (!(*this)(x[k]) && y[k] ? 1.0 : 0.0);
    }
    fnr /= size;
    return fnr;
}

double_t WClassifier::fpr(const std::vector<IMatrix> &x, const std::vector<bool> &y) {
    double_t fpr = 0.0;
    size_t size = x.size();
    for (int k = 0; k < size; ++k) {
        fpr += ((*this)(x[k]) && !y[k] ? 1.0 : 0.0);
    }
    fpr /= size;
    return fpr;
}
