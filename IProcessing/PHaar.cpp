//
// Created by bendou on 20/01/19.
//

#include "PHaar.h"

double_t PHaar::operator()(const IMatrix &img) const {
    Pixel f;
    switch (type) {
        case TwoRectW:
            f = img.sum(x, y, x + w / 2 - 1, y + h - 1) -
                img.sum(x + w / 2, y, x + w - 1, y + h - 1);
            break;
        case TwoRectH:
            f = img.sum(x, y + h / 2 - 1, x + w - 1, y + h - 1) -
                img.sum(x, y, x + w - 1, y + h / 2);
            break;
        case ThreeRect:
            f = img.sum(x, y, x + w / 3 - 1, y + h - 1) -
                img.sum(x + w / 3, y, x + 2 * w / 3 - 1, y + h - 1) +
                img.sum(x + 2 * w / 3, y, x + w - 1, y + h - 1);
            break;
        case FourRect:
            f = img.sum(x, y, x + w / 2 - 1, y + h / 2 - 1) -
                img.sum(x + w / 2, y, x + w - 1, y + h / 2 - 1) -
                img.sum(x, y + h / 2, x + w / 2 - 1, y + h - 1) +
                img.sum(x + w / 2, y + h / 2, x + w - 1, y + h - 1);
            break;
    }

    return f.grey();
}