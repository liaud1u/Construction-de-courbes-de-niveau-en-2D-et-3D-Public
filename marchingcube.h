#ifndef _OPENMP
#define omp_get_thread_num() 0
#define omp_get_num_threads() 4
#else
#include <omp.h>
#endif

#ifndef MARCHINGCUBE_H
#define MARCHINGCUBE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <gmpxx.h>
#include "cube.h"
#include "cubestate.h"
#include "lookuptablecube.h"

#include <iostream>

#include <QApplication>
#include <QDir>

#define NUM_THREAD 2

using namespace cv;


/**
 ** @brief Marching Cube algorithm
 ** @author A. LIAUD, J. SCHERRING
 **/
class MarchingCube
{
private:

    /// @brief array of vertice for each isovalue
    int * cpt_vertice;

    /// @brief Marching Square definition
    int marching = 1;

    /// @brief Path of the source image
    std::string image_path;

    /// @brief Marching Cube LUT
    LookUpTableCube table;

    /// @brief 3D array of the current object
    int *** obj;
    
    /// @brief 3D map of the connex component
    int *** connex_comp;

    /// @brief int col, rows and depth of the object
    int col, rows, depth;

    /// @brief vector of vector of vertices (list of vertices for each isovalue)
    std::vector<std::vector<Point3D>> vertices;

    /// @brief vector of vector of faces (list of faces for each isovalue)
    std::vector<std::vector<std::vector<int>>> faces;

    /// @brief vector of int where the algorithm need to be applied
    std::vector<int> isovaleurs;
    
    /// @brief int connexity needed
    int connexity;

    /// @brief minX, minY, minZ, maxX, maxY, maxZ coordinate of the object
    int minX, minY, minZ, maxX, maxY, maxZ;

public:

    /// @brief Default constructor
    MarchingCube();

    /// @brief Constructor of the Marching Cube algorithm
    /// @param string, object path
    /// @param int marching cube definition
    /// @param vector of int isovalue where the algorithm need to be applied
    /// @param int connexity for the algorithm application
    MarchingCube(std::string image_path, int marching, std::vector<int> isovaleurs, int connexity);

    /// @brief do interpolation of all cube for the isovalue matching index in the isovalue array
    /// @param int index of the isovalue
    void cube_interpolation(int index);

    /// @brief Apply algorithm on the data
    void apply_algorithm();

    /// @brief getter of the cube at given coords
    /// @param int x coord
    /// @param int y coord
    /// @param int z coord
    Cube get_cube(int x, int y, int z);

    /// @brief write result of the execution in .off files
    void write_file();
    
    /// @brief check for all connex group connexity
    /// @param int connexity
    /// @param int isovalue
    void update_connex_group(int connexity, int isoval);

    /// @brief Destuctor
    ~MarchingCube(){
        for(int x = 0; x<col;x++){
            for(int y = 0; y<rows;y++){
                delete [] obj[x][y];
            }
            delete [] obj[x];
        }

        delete [] obj;
        delete [] cpt_vertice;
    }
};

#endif // MARCHINGCUBE_H
