#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <iostream>

/**
 ** @brief Point3D structure
 ** @author A. LIAUD
 **/
struct Point3D{
    /// @brief x coord
    double x;

    /// @brief y coord
    double y;

    /// @brief z coord
    double z;

    /// @brief intensity coord
    double intensity;

    /// @brief Constructor of the Point
    /// @param double x coord
    /// @param double y coord
    /// @param double z coord
    /// @param int intensity of the pixel
    Point3D(double x, double y, double z, int intensity): x(x), y(y), z(z), intensity(intensity){
    }

    /// @brief Constructor of the Point
    /// @param double x coord
    /// @param double y coord
    /// @param double z coord
    Point3D(double x, double y, double z): x(x), y(y), z(z), intensity(0){
    }

    /// @brief Default constructor of a point
    Point3D(){}

    /// @brief getter of the x coord
    /// @return double x coord
    double get_x(){return x;}

    /// @brief getter of the y coord
    /// @return double y coord
    double get_y(){return y;}

    /// @brief getter of the z coord
    /// @return double z coord
    double get_z(){return z;}

    /// @brief getter of the intensity of the pixel
    /// @return int intensity
    double get_intensity(){return intensity;}
};

/**
 ** @brief Cube class
 ** @author A. LIAUD
 **/
class Cube
{
private:
    /// @brief std::vector<int> list of point of the cube
    std::vector<int> points_state;

public:

    /// @brief default constructor
    Cube();

    /// @brief constructor of the cube
    /// @param std::vector of int value corner of the cube
    Cube(std::vector<int> points_state):points_state(points_state){};

    /// @brief Getter of the value of the square
    /// @param int isovaleur
    /// @return value of the square matching with the LUT
    int value(int isovaleur);

    /// @brief value of the face top left corner of the square
    /// @return int value
    int a(){return points_state[0];}

    /// @brief value of the face top right corner of the square
    /// @return int value
    int b(){return points_state[1];}

    /// @brief value of the face bot right corner of the square
    /// @return int value
    int c(){return points_state[2];}

    /// @brief value of the face bot left corner of the square
    /// @return int value
    int d(){return points_state[3];}

    /// @brief value of the back top left corner of the square
    /// @return int value
    int e(){return points_state[4];}

    /// @brief value of the back top right corner of the square
    /// @return int value
    int f(){return points_state[5];}

    /// @brief value of the back bot right corner of the square
    /// @return int value
    int g(){return points_state[6];}

    /// @brief value of the back bot left corner of the square
    /// @return int value
    int h(){return points_state[7];}
};

#endif // CUBE_H
