#ifndef AKIMAINTERPOLATION_H
#define AKIMAINTERPOLATION_H

#include <iostream>
#include <cmath>

/**
 ** @brief Akima Interpolation algorithm
 ** @author A. BADAWY
 **/
class AkimaInterpolation
{
    private:
    public:
    

       /// @brief Getter of an interpolation
       /// @param list of float of x used in interpolation
       /// @param list of float of y used in interpolation
       /// @param float value to interpolate
       static float GetAkimaInt(float x[], float y[], float xp);
};

#endif // AKIMAINTERPOLATION_H
