#ifndef LAGRANGEINTERPOLATION_H
#define LAGRANGEINTERPOLATION_H

#include <iostream>
#include <cmath>

/**
 ** @brief Lagrange Interpolation algorithm
 ** @author A. BADAWY, A.LIAUD
 **/
class LagrangeInterpolation
{
public:

    /// @brief Default constructor
    LagrangeInterpolation();

    /// @brief Getter of the lagrange interpolation
    /// @param list of all the x-coordinates for the interpolation
    /// @param list of all values at the x-coordinates
    /// @param xp the x-coordinates to interpolate
    /// @return float value of the interpolation
    static float GetLagrangeInt(float x[], float y[],int begin, int end, float xp);
};

#endif // LAGRANGEINTERPOLATION_H
