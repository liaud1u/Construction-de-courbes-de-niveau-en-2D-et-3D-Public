#ifndef CUBESTATE_H
#define CUBESTATE_H


#include <vector>
#include <iostream>
#include <gmpxx.h>
#include "cube.h"
#include "linearinterpolation.h"

/**
 ** @brief Cube state class
 ** @author A. LIAUD
 **/
class CubeState
{
private:

    /// @brief vector of vector of int representing faces
    std::vector<std::vector<int>> faces;

    /// @brief return value of interpolation of two value with isolevel
    /// @param float pt1 value
    /// @param float pt2 value
    /// @param int isolevel for interpolation
    /// @return float interpolation value
    float interpolation(  float pt1, float pt2, int isolevel);

    /// @param int id of the state
    int id;

public:

    /// @brief Default constructor
    CubeState(){};

    /// @brief Constructor with id
    /// @param int id of the case
    CubeState(int id) : id(id){};

    /// @brief Constructor of the case
    /// @param vector of vector of int representing faces
    /// @param int id of the case
    CubeState(std::vector<std::vector<int>> faces,int id) : faces(faces),  id(id){};

    /// @brief Constructor of the case
    /// @param vector of vector of int representing faces
    CubeState(std::vector<std::vector<int>> faces) : faces(faces){};

    /// @brief interpolate the cube to march with cube values
    /// @param Cube cube to interpolate
    /// @param int id case
    /// @param int [] neighboor of the cube
    /// @param int isolevel to interpolate
    /// @return vector of vector of point
    std::vector<std::vector<Point3D>> fct_interpolation(Cube cube, int id, int neighboor_connex[], int isolevel);

    /// @brief setter of the id of the case
    /// @param int id of the case
    void setId(int id){this->id=id;}
};

#endif // CUBESTATE_H
