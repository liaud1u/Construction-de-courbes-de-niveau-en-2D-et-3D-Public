#ifndef SQUARESTATE_H
#define SQUARESTATE_H

#include <vector>
#include <iostream>
#include <gmpxx.h>
#include "square.h"
#include "linearinterpolation.h"
#include "lagrangeinterpolation.h"
#include "akimainterpolation.h"
#include "bilinearinterpolation.h"
#include "splineinterpolation.h"

#define LINEAR_INTERPOLATION 0
#define BILINEAR_INTERPOLATION 1
#define LAGRANGE_INTERPOLATION 2
#define AKIMA_INTERPOLATION 3
#define SPLINE_INTERPOLATION 4


/**
 ** @brief SquareState class for the MarchingSquare algorithm
 ** @author A. LIAUD
 **/
class SquareState{
private:

    /// @brief Vector of vector of char defining the list of line to draw according to the state
    std::vector<std::vector<char>> lines;

    /// @brief id of the squarestate
    int id;

    /// @brief Interpolation of the a face using the specified method
    /// @param face to interpolation
    /// @param first value
    /// @param second value
    /// @param optionnal third value (not needed for linear interpolation)
    /// @param optionnal fourth value (not needed for linear interpolation)
    /// @param int interpolation method
    /// @param int isolevel to interpolate
    /// @return float value of the interpolation
    float interpolation_by_method(char pos, float a, float b, float pt3, float pt4, int interpolation_method, int isolevel);
public:

    /// @brief Default constructor
    SquareState(){};

    /// @brief Constructor of a void Square
    /// @brief int unique id of the state
    SquareState(int id) : id(id){};

    /// @brief Constructor of the SquareState with the vector of vector of int defining the list of line to draw
    /// @param std::vector<std::vector<char>> lines to draw
    /// @param int unique id of the state
    SquareState(std::vector<std::vector<char>> lines,int id) : lines(lines),  id(id){};

    /// @brief Print the state (for debug)
    void print() const;

    /// @brief Interpolation method
    /// @param Square square to interpolate
    /// @param int isolevel to use interpolation on
    /// @param int interpolation method to use
    /// @param array of int matching with value of neighboor corner values
    /// @param array of int matching with connex label of neighboor pixels
    /// @return vector of vector of double as line to draw to get result of the interpolation
    std::vector<std::vector<double>> fct_interpolation(Square square, int isolevel, int interpolation_method, int neighboor[], int neighboor_connex[]  );
};



#endif // SQUARESTATE_H
