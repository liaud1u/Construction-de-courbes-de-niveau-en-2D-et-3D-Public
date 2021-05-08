#include "marchingsquare.h"
#include "marchingcube.h"

#include <dirent.h>

#define DEF 10
#define MARCHING 1
#define DEBUG false
#define SIMPLIFY false
#define MODE_INTER AKIMA_INTERPOLATION
#define CONNEXITY 8
#define CONNEXITY_3D 26


int main(int argc, char *argv[])
{
    double deb, fin, tempsOMP, temps_moyen=0;
    /*DIR *dir;
    struct dirent *ent;


    std::ofstream myfile;
    String file = "experimentation50binary1thread.csv";
    myfile.open (file);

    myfile <<  "Nombre de pixels;Temps(s);Nombre de ligne\n";

    if ((dir = opendir ("Data/kimia99/")) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
          if(ent->d_name[0]!='.'){

            String path = "Data/kimia99/"+std::string(ent->d_name);
            MarchingSquare marching(path,MARCHING,DEF, {50});

            deb = omp_get_wtime();
            marching.apply_algorithm(MODE_INTER,SIMPLIFY,CONNEXITY);
            fin = omp_get_wtime();

            tempsOMP = fin-deb;
            temps_moyen += tempsOMP;

            marching.write_file();
            myfile <<  marching.get_height()*marching.get_length() << ";" << tempsOMP << ";" << marching.get_line_amounts()[0] << "\n";

         }
      }
      closedir (dir);
    } else {
      perror ("Ouverture du dossier impossible");
      return EXIT_FAILURE;
    }


    myfile.close();*/

 
    // "Data/kimia99/diago.png"
    MarchingSquare marching("Data/Kimia99/bunny04.png",MARCHING,DEF, {25,50,100,140});


    /*for(int i = 0; i< 100; i++){
        deb = omp_get_wtime();
        marching.apply_algorithm(MODE_INTER,SIMPLIFY,CONNEXITY);
        fin = omp_get_wtime();

        tempsOMP = fin-deb;
        temps_moyen += tempsOMP;

        printf("OpenMP :\tTemps        : %f s\n", tempsOMP);
    }

    temps_moyen/=100;
    printf("OpenMP :\tTemps  moyen pour 100 éxecutions      : %f s\n", temps_moyen);
    */

    marching.apply_algorithm(MODE_INTER,SIMPLIFY,CONNEXITY);
    cv::Mat draw = marching.cv_draw(DEBUG);
    imwrite("resultat.png",draw);
    imshow("Display windows", draw);
    waitKey(0);


    /*MarchingCube cube("Data/Mesh/damiertest.txt",MARCHING,{128,255}, CONNEXITY_3D);


    double deb, fin, tempsOMP, temps_moyen=0;
    for(int i = 0; i< 100; i++){
        deb = omp_get_wtime();
        cube.apply_algorithm();
        fin = omp_get_wtime();
        tempsOMP = fin-deb;
        temps_moyen += tempsOMP;
        printf("OpenMP %d:\tTemps        : %f s\n", i, tempsOMP);
    }
    temps_moyen/=100;
    printf("OpenMP :\tTemps  moyen pour 100 éxecutions      : %f s\n", temps_moyen);


    cube.apply_algorithm();
    cube.write_file();
     */

    return 0;
}
