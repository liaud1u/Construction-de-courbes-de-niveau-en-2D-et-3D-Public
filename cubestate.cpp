#include "cubestate.h"



std::vector<std::vector<Point3D>> CubeState::fct_interpolation(Cube cube, int id, int neighboor_connex[], int isolevel){
    std::vector<std::vector<Point3D>> res;

    if (neighboor_connex[0] == neighboor_connex[2]) {
    switch (id) {
        case 85: {
                faces = { {6,  7,  5},  {5,  7,  4},  {4,  0,  5},  {0,  1,  5},  {1,  0,  2},  {2,  0,  3},  {3,  7,  2},  {7,  6,  2}};

        }
            break;
            
        case 195: {
            std::cout << id << std::endl;
            faces = {{3, 11, 7}, {3, 7, 8}, {9, 8, 7}, {5, 9, 7}, {9, 5, 10}, {9, 10, 1}, {3, 1, 10}, {11, 3, 10}};
        }
            break;
            
        case 105: {
            if (neighboor_connex[0] == neighboor_connex[5] && neighboor_connex[0] == neighboor_connex[7]) {
            faces = {{2,  11, 10},  {11, 6, 10}, {6,  11,  4}, {4,  11,  8},  {8,  0,  4},  {0,  9,  4},  {9,  0, 10},  {10, 0,  2}};
            }
        }
            break;
            
        case 150: {
            std::cout << id << std::endl;
            faces = { {2,  11, 10}, {10, 11,  6},  {6,  4, 10},  {4,  9, 10},  {9,  4,  0},  {0,  4,  8}, {8,  11,  0},  {11, 2,  0}};
            
        }
            break;
            
        case 170: {
            std::cout << id << std::endl;
            faces = {{ 6,  7,  5},  {7,  4,  5},  {4,  7,  0},  {0,  7,  3},  {3,  2,  0},  {2,  1,  0},  {1,  2,  5},  {5,  2,  6 }};
            
        }
            break;
            
        case 60: {
            std::cout << id << std::endl;
            faces = {{  8,  7,  3}, {7,  11,  3},  {11, 7, 10},  {10, 7,  5},  {5,  9, 10},  {9,  1, 10},  {1,  9,  3},  {3,  9,  8 }};
            
        }
            break;
        
        case 65: {
            if (neighboor_connex[0] == neighboor_connex[7]) {
            faces = {{  5,  8,  0},  {8,  5,  6},  {6,  3,  8},  {3,  6, 10},  {10, 0,  3}, {0,  10,  5 }};
            }
        }
            break;
            
        case 130: {
            std::cout << id << std::endl;
            faces = {{  6,  9,  1},  {9,  6,  7},  {7,  0,  9},  {0,  7, 11},  {11, 1,  0}, {1,  11,  6 }};
        }
            break;
            
        case 20: {
            std::cout << id << std::endl;
            faces = {{ 7,  10,  2},  {10, 7,  4},  {4,  1, 10},  {1,  4,  8},  {8,  2,  1},  {2,  8,  7 }};
        }
            break;
            
        case 40: {
            std::cout << id << std::endl;
            faces = {{ 4,  11,  3},  {11, 4,  5},  {5,  2, 11},  {2,  5,  9},  {9,  3,  2},  {3,  9,  4 }};
        }
            break;
            
        case 215: {
            std::cout << id << std::endl;
            faces = {{  4,  3, 11},  {11, 5,  4}, {5,  11,  2},  {2,  9,  5},  {9,  2,  3},  {3,  4,  9 }};
        }
            break;
            
        case 235: {
            if (neighboor_connex[0] == neighboor_connex[1] && neighboor_connex[0] == neighboor_connex[3] && neighboor_connex[0] == neighboor_connex[5] &&  neighboor_connex[1] == neighboor_connex[6] && neighboor_connex[1] == neighboor_connex[7]) {
            faces = {{  7,  2, 10}, {10, 4,  7}, {4,  10,  1}, {1,  8,  2}, {8,  1,  4},  {2,  7,  8 }};
            }
        }
            break;
            
        case 125: {
            if (neighboor_connex[0] == neighboor_connex[2] && neighboor_connex[0] == neighboor_connex[4] && neighboor_connex[0] == neighboor_connex[5] && neighboor_connex[1] == neighboor_connex[7] && neighboor_connex[0] == neighboor_connex[1]) {
            faces = {{  6,  1,  9},  {9,  7,  6},  {7,  9,  0}, {0,  11,  7},  {11, 0,  1},  {1,  6, 11 }};
            }
        }
            break;
            
        case 190: {
            std::cout << id << std::endl;
            faces = {{  5,  0,  8},  {8,  6,  5},  {6,  8,  3}, {3,  10,  6},  {10, 3,  0},  {0,  5, 10 }};
        }
            break;
            
        default:
            break;
    }
    }
    
    
    for(std::vector<int> face : faces){
        std::vector<Point3D> res_face;
        for(int point : face){

            Point3D p(0,0,0);
            switch(point){
                case 0:
                     p = Point3D(interpolation(cube.a(),cube.b(),isolevel),0,0);
                     break;
                case 1:
                     p = Point3D(1,interpolation(cube.b(),cube.c(),isolevel),0);
                     break;
                case 2:
                     p = Point3D(interpolation(cube.d(),cube.c(),isolevel),1,0);
                     break;
                case 3:
                     p = Point3D(0,interpolation(cube.a(),cube.d(),isolevel),0);
                     break;
                case 4:
                     p = Point3D(interpolation(cube.e(),cube.f(),isolevel),0,1);
                     break;
                case 5:
                     p = Point3D(1,interpolation(cube.f(),cube.g(),isolevel),1);
                     break;
                case 6:
                     p = Point3D(interpolation(cube.h(),cube.g(),isolevel),1,1);
                     break;
                case 7:
                     p = Point3D(0,interpolation(cube.e(),cube.h(),isolevel),1);
                     break;
                case 8:
                     p = Point3D(0,0,interpolation(cube.a(),cube.e(),isolevel));
                     break;
                case 9:
                     p = Point3D(1,0,interpolation(cube.b(),cube.f(),isolevel));
                     break;
                case 10:
                     p = Point3D(1,1,interpolation(cube.c(),cube.g(),isolevel));
                     break;
                case 11:
                     p = Point3D(0,1,interpolation(cube.d(),cube.h(),isolevel));
                     break;
            }


            res_face.push_back(p);
        }

        res.push_back(res_face);
    }

    return res;
}


float CubeState::interpolation(float pt1, float pt2, int isolevel){

    /*
    if ( std::abs(isolevel/255.0 - pt1/255.0) < 0.00001 ) return 0;
    if ( std::abs(isolevel/255.0 - pt2/255.0) < 0.00001 ) return 1;
    if ( std::abs(pt1/255.0 - pt2/255.0) < 0.00001 ) return 0;
    double c = (isolevel/255.0 - pt1/255.0) / (pt2/255.0 - pt1/255.0);
    */

    /*double c =  va + (isolevel - da) *((vb - va) / (db - da));*/

    //printf("%f %f %f %f\n",c, isolevel/255.0, pt1/255.0,pt2/255.0);

    return LinearInterpolation::GetLinearInt(pt1,pt2,isolevel);
}
