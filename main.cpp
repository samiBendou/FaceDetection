#include <iostream>
#include "ImageMatrix.h"

using namespace std;

int main() {
    ImageMatrix test("../img/test/blank_white.jpg", ImageMatrix::GScale);
    ImageMatrix res{test / 255};

    /*
    cout << "READ IMAGE : " << endl;
    cout << res << endl;
     */

    cout << "INTEGRAL IMAGE : " << endl;
    cout << res.intgr() << endl;
    cout << res.sumWithin(0, 0, 3, 3);

    return 0;
}