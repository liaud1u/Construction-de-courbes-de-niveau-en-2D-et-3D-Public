#ifndef LINEARINTERPOLATION_H
#define LINEARINTERPOLATION_H

/**
 ** @brief Linear Interpolation algorithm
 ** @author A. BADAWY
 **/
class LinearInterpolation
{

public:

    /// @brief Get the linear interpolation of two values using a coefficient X
    /// @param first value
    /// @param second value
    /// @param X to applicate the formula (X*x1 + (1-X)*x2)
    /// @return float value of the interpolation
    static float GetLinearInt(float x1,float x2,float X);


};


#endif // LINEARINTERPOLATION_H
