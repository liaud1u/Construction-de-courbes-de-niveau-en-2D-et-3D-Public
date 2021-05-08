#ifndef BILINEARINTERPOLATION_H
#define BILINEARINTERPOLATION_H

/**
 ** @brief Bilinear Interpolation algorithm
 ** @author A. BADAWY, J. SCHERRING
 **/
class BilinearInterpolation
{


private:
public:

    /// @brief Getter of the bilinear interpolation
    /// @param float x1 for interpolation
    /// @param float y1 for interpolation
    /// @param float x2 for interpolation
    /// @param float y2 for interpolation
    /// @param float x for interpolation
    /// @param float y for interpolation
    /// @param float q11 for interpolation
    /// @param float q12 for interpolation
    /// @param float q21 for interpolation
    /// @param float q22 for interpolation
    static float GetBiLinearInt(float x1,float y1,float x2,float y2,float x,float y,float q11, float q12, float q21, float q22);

};


#endif // BILINEARINTERPOLATION_H
