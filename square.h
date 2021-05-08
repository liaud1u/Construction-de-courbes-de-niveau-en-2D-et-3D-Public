#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <iostream>

/**
 ** @brief Square class for the MarchingSquare algorithm
 ** @author A. LIAUD
 **/
class Square
{
private:

    /// @brief Vector of the state (0 or 1) of points defining a square
    std::vector<int> points_state;

public:

    /// @brief Default constructor
    Square(){};

    /// @brief Constructor of a square with the vector of state of points defining the square
    /// @param std::vector<int> points_state vector of state of points defining the square
    Square(std::vector<int> points_state):points_state(points_state){};

    /// @brief Getter of the value of the square
    /// @param int isovaleur
    /// @return value of the square matching with the LUT
    int value(int isovaleur);

    /// @brief value of the top left corner of the square
    /// @return int value
    int a(){return points_state[0];}

    /// @brief value of the top right corner of the square
    /// @return int value
    int b(){return points_state[1];}

    /// @brief value of the bot right corner of the square
    /// @return int value
    int c(){return points_state[2];}

    /// @brief value of the bot left corner of the square
    /// @return int value
    int d(){return points_state[3];}
};

#endif // SQUARE_H
