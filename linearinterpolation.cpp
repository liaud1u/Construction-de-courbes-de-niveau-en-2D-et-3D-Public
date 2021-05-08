#include "linearinterpolation.h"
#include <iostream>
using namespace std;


float LinearInterpolation::GetLinearInt(float x1,float x2,float X){
    return (float)((X-x1)/(x2-x1));
}
