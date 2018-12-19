#include <iostream>
#include "ImageMatrix.h"

using namespace std;

int main() {
    ImageMatrix test("../img/test/blank_white.jpg", Pixel::GScale);
    ImageMatrix res{test / 255};

    /*
    cout << "READ IMAGE : " << endl;
    cout << res << endl;
     */

    /*
    cout << "INTEGRAL IMAGE : " << endl;
    cout << res.intgr() << endl;
    cout << res.sumWithin(0, 0, 2, 2);
    */

    Pixel p{1};
    cout << p << endl << (6 * p + 3 * p) / (3 * p) << endl;

    return 0;
}