#include "splineinterpolation.h"


float SplineInterpolation::GetSplineInt(float y[], float xp){
    double a0, a1, a2, a3;

    a0 = y[3]-y[2]-y[0]+y[1];
    a1 = y[0]-y[1]-a0;
    a2 = y[2] - y[0];
    a3 = y[1];

    return (a0*xp*xp*xp+a1*xp*xp+a2*xp+a3);
}
