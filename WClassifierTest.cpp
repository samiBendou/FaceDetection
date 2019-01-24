//
// Created by Sami Dahoux on 2019-01-23.
//

#include <gtest/gtest.h>
#include <WClassifier.h>

#define FACE_TRAINING_SET_SIZE 50
#define NON_FACE_TRAINING_SET_SIZE 50

using namespace std;

class WClassifierTest : public ::testing::Test {

    void setUp() {

    }

public:
    const size_t n = NON_FACE_TRAINING_SET_SIZE, p = FACE_TRAINING_SET_SIZE;
    vector<IMatrix> training_set{n  + p};
    vector<bool> training_labels{};
    WClassifier h{PHaar(300, 100, 200, 400, PHaar::Type::TwoRectH)};
};

TEST_F(WClassifierTest, Train) {

    stringstream path{};
    string sufix{".jpg"}, prefix_face{"../img/faces/image_"}, prefix_non_face{"../img/cars_brad_bg/image_"};

    for (size_t k = 1; k <= p; ++k) {
        path.str("");
        path << prefix_face << (k % 10000) / 1000 << (k % 1000) / 100 << (k % 100) / 10 << k % 10 << sufix;
        training_set[k - 1] = IMatrix(path.str());
        training_labels.push_back(true);
    }

    for (size_t k = 1; k <= n; ++k) {
        path.str("");
        path << prefix_non_face << (k % 10000) / 1000 << (k % 1000) / 100 << (k % 100) / 10 << k % 10 << sufix;
        training_set[k + p - 1] = IMatrix(path.str());
        training_labels.push_back(false);
    }

    vec_t w{vec_t::ones(n + p)};
    w(0, p - 1) /= p;
    w(p, n + p - 1) /= n;
    h.train(w, training_set, training_labels);

    ASSERT_LE(h.fnr(training_set, training_labels), 0.5);
    ASSERT_LE(h.fpr(training_set, training_labels), 0.5);
}
