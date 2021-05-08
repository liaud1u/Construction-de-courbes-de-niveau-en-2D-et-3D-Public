#include "lagrangeinterpolation.h"

float LagrangeInterpolation::GetLagrangeInt(float x[], float y[],int begin, int end, float xp)
{

    float yp = 0;
    for (int i=begin;i<=end;i++){
        std::cout<< y[i] << " -> " << x[i]<< " ";
        float p = y[i];
        for (int j=begin;j<=end;j++){
            if(i!=j){
                p = p * (xp - x[j])/(x[i] - x[j]);
            }
        }
        yp += p;
    }

    std::cout << yp<<" for isolevel "<<xp<< "\n";


    return yp;
}
