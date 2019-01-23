//
// Created by Sami Dahoux on 2019-01-23.
//

#include <gtest/gtest.h>
#include <WClassifier.h>

#define FACE_TRAINING_SET_SIZE 50

using namespace std;

class WClassifierTest : public ::testing::Test {

    void setUp() {

    }

public:
    vector<IMatrix> training_set{FACE_TRAINING_SET_SIZE};
    vector<bool> training_labels{};
    WClassifier h{PHaar(300, 100, 200, 400, PHaar::Type::TwoRectH)};
};

TEST_F(WClassifierTest, Train) {

    stringstream path{};
    string sufix{".jpg"}, prefix{"../img/faces/image_"};

    for (size_t k = 1; k <= FACE_TRAINING_SET_SIZE; ++k) {
        path.str("");
        path << prefix << (k % 10000) / 1000 << (k % 1000) / 100 << (k % 100) / 10 << k % 10 << sufix;
        training_set[k - 1] = IMatrix(path.str());
        training_labels.push_back(true);
    }
    cout << FACE_TRAINING_SET_SIZE << " images successfully loaded" << endl;

    vec_t w{vec_t::scalar(1.0 / FACE_TRAINING_SET_SIZE, FACE_TRAINING_SET_SIZE)};
    h.train(w, training_set, training_labels);
    ASSERT_LE(h.fnr(training_set, training_labels), 0.5);
}
