#include <math.h>
#include "akimainterpolation.h"

/* pi(x) = ai+bi(x-xi)+ci(x-xi)^2+di(x-xi)^3
 * x[] = valeurs de x
 * y[] = valeurs de y
 * xp = point d'interpolation */


float AkimaInterpolation::GetAkimaInt(float x[], float y[],float xp){

    float a, b; //a & b = Coefficients d'Akima
    float yp; // yp = point interpolé
    int i , iv = 4; //nb de points
    float xm[iv+4], z[iv+1];

    x[0]=2.0*x[1]-x[2];

    //Calculer les coefficients a et b
    for (i=1; i<iv; i++){
        //Shift i to i+2
        //
        xm[i+2]=(y[i+1]-y[i])/(x[i+1]-x[i]);
    }
      xm[iv+2]=2.0*xm[iv+1]-xm[iv];
      xm[iv+3]=2.0*xm[iv+2]-xm[iv+1];
      xm[2]=2.0*xm[3]-xm[4];
      xm[1]=2.0*xm[2]-xm[3];

      //b = (xi+1 - xi)
      for (i=1; i<iv+1; i++){
          a=fabs(xm[i+3]-xm[i+2]);
          b=fabs(xm[i+1]-xm[i]);

        if (a+b!=0){
            z[i]=(a*xm[i+1]+b*xm[i+2])/(a+b);
        }
        z[i]=(xm[i+2]+xm[i+1])/2.0;
      }

      i=1;

      while (xp>x[i]){
          i++;
      }
      i--;

      //Debut de l'interpolation
      b=x[i+1]-x[i];
      a=xp-x[i];
      //ci = 3((yi-1 - yi)/(xi+1 - xi)) - ti+1 - 2ti / b
      yp=y[i]+z[i]*a+(3.0*xm[i+2]-2.0*z[i]-z[i+1])*a*a/b;
      //di = ti+1 + ti +2((yi-1 - yi)/(xi+1 - xi)) / b^2
      yp=yp+(z[i]+z[i+1]-2.0*xm[i+2])*a*a*a/(b*b);

    return yp;
}
