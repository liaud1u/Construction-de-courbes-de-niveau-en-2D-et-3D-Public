#ifndef _OPENMP
#define omp_get_thread_num() 0
#define omp_get_num_threads() 4
#else
#include <omp.h>
#endif

#ifndef MARCHINGSQUARE_H
#define MARCHINGSQUARE_H

#include "lookuptable.h"
#include "square.h"
#include "squarestate.h"
#include "unionfind.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <gmpxx.h>


#include <iostream>

#include <QApplication>
#include <QDir>

#define NUM_THREAD 1

/**
 ** @brief MarchingSquare class to apply MarchingSquare algorithm
 ** @author A. LIAUD, J. SCHRRING
 **/

#define ERREUR  0.00001

using namespace cv;

class MarchingSquare
{
private:

    /// @brief Lookuptable used
    LookupTable table;

    /// @brief Marching Square definition
    int marching = 1;

    /// @brief Path of the source image
    std::string image_path;

    /// @brief MarchingSquare algorithm result
    Mat draw;

    /// @brief Output definition (for OpenCV drawing)
    int def_out = 10;

    /// @brief Vector of isovalue where we will apply algorithm
    std::vector<int> isovaleurs;

    /// @brief Vector of vertex to draw in order to get the result of the algorithm
    std::vector<Point2f> * drawPoint;

    /// @brief Array of int matching amount of line to draw for each isovalue
    int * lineAmount;

    /// @brief map of the connex component
    int ** connex_comp;

    /// @brief Method that draw lines with opencv
    /// @param std::vector<Point2f> lines to draw
    /// @param int isovalue of the set of point
    void draw_lines_OpenCV( std::vector<Point2f> ligne, int iso);

    /// @brief Method that write lines in file
    /// @param int isovalue of the set of point
    /// @param std::vector<Point2f> lines to write
    void write_file(int iso, std::vector<Point2f> ligne);

    /// @brief Simplify set of polygons
    /// @param vector of vector of Point2f to simplify
    /// @return list of all polygones simplified
    std::vector<std::vector<Point2f>> simplify(std::vector<std::vector<Point2f>> polygones);
    
    /// @brief get vector from two points
    /// @param pt1 Point2f
    /// @param pt2 Point2f
    /// @return point2f vector
    Point2f get_vector(Point2f pt1, Point2f pt2);
    
    /// @brief scalar product
    /// @param vec1 Point2f
    /// @param vec2 Point2f
    /// @return float scalar product of the vector
    float scalar_product(Point2f vec1, Point2f vec2);
    
    /// @brief Sort path in order to get continuous polygons
    /// @param vector of vector of Point2f to sort
    /// @return vector of vector of Point2f as a path of point matching with polygons
    std::vector<std::vector<Point2f>> tri_chemin(std::vector<std::vector<Point2f>> lignes);

    /// @brief Refractor output of the algorithm
    /// @param bool simplification needed
    /// @param index of the current isovalue
    /// @param vector of vector of Point2f to refractor
    void refractorisation(bool simplification, int index, std::vector<std::vector<Point2f>> ligne);

    /// @brief Apply the LUT and interpolation to all square corresponding to isovalue at index
    /// @param int index of the isovalue to use
    /// @param int interpolation_method to use
    /// @return vector of vector of point2f matching with the lines to draw to get the result of the algorithm
    std::vector<std::vector<Point2f>> square_interpolation(int index, int interpolation_method);


public:

    /// @brief Default consturctor
    /// @param string source image path
    /// @param int marching definition
    /// @param int scale of the output printed with opencv
    /// @param vector of isovalue
    MarchingSquare(std::string image_path, int marching, int def_out, std::vector<int> isovaleurs);

    /// @brief Get the square at the coordinates
    /// @param int x coord
    /// @param int y coord
    /// @return square at the specified coord
    Square get_square(int x, int y);

    /// @brief Apply the MS algorithm
    /// @param int interpolation method to use
    /// @param simplification needed
    /// @param connexity 4 or 8 connexity
    void apply_algorithm(int interpolation_method, bool simplify, int connexity);

    /// @brief Write the result in a file
    void write_file();

    /// @brief draw the result with opencv
    /// @param bool debug, add grid to resulting image
    /// @return Mat to draw
    Mat cv_draw(bool debug);

    /// @brief check for all connex group
    /// @param int connexity
    /// @param int isolevel
    void update_connex_group(int connexity, int isolevel);

    /// @brief getter of the length of the image
    /// @return amount of col
    int get_length(){return draw.cols;};

    /// @brief getter of the height of the image
    /// @return int amonunt of row
    int get_height(){return draw.rows;};

    /// @brief getter of the amount of line to draw for each isovalue
    /// @return int array, amount of line to draw for each isovalue
    int * get_line_amounts(){return lineAmount;}

    /// @brief Destructor
    ~MarchingSquare(){

        delete [] drawPoint;
        delete [] lineAmount;
        delete [] connex_comp;
    }
};

#endif // MARCHINGSQUARE_H
