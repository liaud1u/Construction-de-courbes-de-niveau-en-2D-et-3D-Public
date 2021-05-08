#include "bilinearinterpolation.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;



float BilinearInterpolation::GetBiLinearInt(float x1,float y1,float x2,float y2,float x,float y,float q11, float q12, float q21, float q22) {
    float x2x1, y2y1, x2x, y2y, yy1, xx1, p;
    x2x1 = x2 - x1;
    y2y1 = y2 - y1;
    x2x = x2 - x;
    y2y = y2 - y;
    yy1 = y - y1;
    xx1 = x - x1;
    p = 1.0 / (x2x1 * y2y1) * (
                q11 * x2x * y2y +
                q21 * xx1 * y2y +
                q12 * x2x * yy1 +
                q22 * xx1 * yy1);
    return p;
}
