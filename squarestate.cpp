#include "squarestate.h"
#include "akimainterpolation.h"
using namespace std;


std::vector<std::vector<double>> SquareState::fct_interpolation(Square square, int isolevel, int interpolation_method, int  neighboor[], int neighboor_connex[]){
    std::vector<std::vector<double>>  lines_interpolate; 

    // Check the ambigeous cases
    if (id==10){
       if(neighboor_connex[0]!=neighboor_connex[2]) // Different connex comp
       {
           lines = {{'N','O'},{'S','E'}};
       }
    }

    if(id==5){
        if(neighboor_connex[1]!=neighboor_connex[3]) // Different connex comp
        {
            lines = {{'N','E'},{'S','O'}};
        }
    }


    // For each line to draw, we interpolates point of the lines
    for(std::vector<char> l : lines){
        std::vector<double> line_interpolate;

        int pt1, pt2;

        for(char face : l){
             switch(face){
                case 'O':
                     pt1 = square.a();
                     pt2 = square.d();
                     line_interpolate.push_back(0);
                     line_interpolate.push_back(interpolation_by_method('O',pt1,pt2,neighboor[7],neighboor[2],interpolation_method,isolevel));
                    break;

                case 'S':
                     pt1 = square.d();
                     pt2 = square.c();
                     line_interpolate.push_back(interpolation_by_method('S',pt1,pt2,neighboor[5], neighboor[0],interpolation_method,isolevel));
                     line_interpolate.push_back(1);
                     break;

                case 'E':
                     pt1 = square.b();
                     pt2 = square.c();
                     line_interpolate.push_back(1);
                     line_interpolate.push_back(interpolation_by_method('E',pt1,pt2,neighboor[3],neighboor[6],interpolation_method,isolevel));
                    break;

                case 'N':
                     pt1 = square.a();
                     pt2 = square.b();
                     line_interpolate.push_back(interpolation_by_method('N',pt1,pt2,neighboor[1],neighboor[4],interpolation_method,isolevel));
                     line_interpolate.push_back(0);
                     break;
            }

        }

        lines_interpolate.push_back(line_interpolate);
    }

    return lines_interpolate;
}


float SquareState::interpolation_by_method(char pos, float pt1, float pt2,float pt3, float pt4,int interpolation_method, int isolevel){


    // Interpolation of the point matching the method wanted
    switch(interpolation_method){
            case LINEAR_INTERPOLATION:{
                    return LinearInterpolation::GetLinearInt(pt1,pt2,isolevel);

                break;
    }
            case AKIMA_INTERPOLATION:{


        float x[4] = {-1,0,1,2};
        float y[4];
        y[0] =  pt3/255.0;
        y[1] = pt1/255.0;
        y[2] = pt2/255.0;
        y[3] =  pt4/255.0;
                return AkimaInterpolation::GetAkimaInt(x,y,isolevel/255.0);
        break;
    }
            case LAGRANGE_INTERPOLATION:{
                int begin = 0;
                int end = 3;
                float x[4] = {-1,0,1,2};
                float y[4] ;


                y[0] = pt3/255.0;
                y[1] = pt1/255.0;
                y[2] = pt2/255.0;
                y[3] = pt4/255.0;

                return LagrangeInterpolation::GetLagrangeInt(x,y,begin,end,isolevel/255.0);

        }

    case SPLINE_INTERPOLATION:{


        float y[4];
        y[0] =  pt3/255.0;
        y[1] = pt1/255.0;
        y[2] = pt2/255.0;
        y[3] =  pt4/255.0;
                return SplineInterpolation::GetSplineInt(y,isolevel/255.0);
        break;
        }

    }
}
