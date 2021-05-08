#ifndef CUBICINTERPOLATION_H
#define CUBICINTERPOLATION_H


/**
 ** @brief Cubic Interpolation algorithm
 ** @author A. LIAUD
 **/
class SplineInterpolation
{
    private:
    public:


       /// @brief Getter of the interpolation
       /// @param list of float of x used in interpolation
       /// @param list of float of y used in interpolation
       /// @param float value to interpolate
       static float GetSplineInt(float y[], float xp);
};


#endif // CUBICINTERPOLATION_H
