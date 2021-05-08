#include "marchingsquare.h"


MarchingSquare::MarchingSquare(std::string image_path, int marching, int def_out, std::vector<int> isovaleurs):marching(marching), image_path(image_path), def_out(def_out), isovaleurs(isovaleurs)
{
    drawPoint = new std::vector<Point2f>[isovaleurs.size()];
    lineAmount = new int[isovaleurs.size()];


    Mat img = imread(image_path);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;

        exit(EXIT_FAILURE);
    }

    //copy of the image
    draw = img.clone();
}


void MarchingSquare::update_connex_group(int connexity, int isolevel){
    connex_comp = new int*[draw.rows];

    // Initialize map of connex components
    for(int i = 0; i<draw.rows;i++){
        connex_comp[i] = new int[draw.cols];
        for(int j = 0; j < draw.cols; j++){
            connex_comp[i][j]= 0;
        }
    }


    UnionFind equivalence_table;
    int cpt_label=1;

    // First pass
    for(int i = 0; i< draw.rows; i++){
        for(int j = 0; j <draw.cols; j ++){
            int val = draw.at<Vec3b>(i,j).val[0];
            if(val<isolevel){

                // 4 Connexity
                if(connexity == 4){

                    // Check top
                    if(i-1>=0 && connex_comp[i-1][j]!=0){

                        // Check left
                        if(j-1>0 && connex_comp[i][j-1]!=0){

                            // Both cases are not 0
                            int top_val = connex_comp[i-1][j];
                            int left_val = connex_comp[i][j-1];

                            std::vector<int> equiv = {top_val,left_val};

                            equivalence_table.add_node(top_val);
                            equivalence_table.add_node(left_val);
                            equivalence_table.union_op(equivalence_table.find_op(top_val),equivalence_table.find_op(left_val));



                            connex_comp[i][j]=top_val<left_val?left_val:top_val;
                        }  else{

                            // Top is not 0
                            connex_comp[i][j]=connex_comp[i-1][j];
                        }
                    }else{

                        if(j-1>0 && connex_comp[i][j-1]!=0){

                            // Left is not 0
                            connex_comp[i][j]=connex_comp[i][j-1];
                        }  else{

                            // Left and Top are 0 so new connex component
                            connex_comp[i][j]=cpt_label++;
                        }
                    }


                }else{
                     std::vector<int> possible_case;

                     //Top case
                     if(i-1>=0 && connex_comp[i-1][j]!=0){
                         possible_case.push_back(connex_comp[i-1][j]);
                     }

                     //Left case
                     if(j-1>=0 && connex_comp[i][j-1]!=0){
                         possible_case.push_back(connex_comp[i][j-1]);
                     }

                     //Top left case
                     if(i-1>=0 &&   j-1>=0 && connex_comp[i-1][j-1]!=0){
                         possible_case.push_back(connex_comp[i-1][j-1]);
                     }

                     //Top right case
                     if(i-1>=0 && j+1<draw.cols && connex_comp[i-1][j+1]!=0){
                         possible_case.push_back(connex_comp[i-1][j+1]);
                     }


                     // Add equivalence to table
                     if(possible_case.size()>=2){
                         for(int v : possible_case){
                             equivalence_table.add_node(v);
                         }

                         for(size_t cpt = 1; cpt < possible_case.size(); cpt++){
                             equivalence_table.union_op(equivalence_table.find_op(possible_case.at(cpt)),equivalence_table.find_op(possible_case.at(cpt-1)));
                         }
                     }

                     // Set minimum value as label for the connex component
                     if(possible_case.size() == 0)
                         connex_comp[i][j]=cpt_label++;
                     else{
                         int min = possible_case.front();

                         for(int i : possible_case){
                             min = min > i ? i : min;
                         }
                         connex_comp[i][j]=min;
                     }

                }
            }
        }
    }


    // Simplification of the map using the equivalence table
    for(int i = 0; i< draw.rows; i++){
        for(int j = 0; j <draw.cols; j ++){
             if(connex_comp[i][j]!=0){

                // If possible, we take the minimum label of the equivalence
                if(equivalence_table.contains(connex_comp[i][j])){
                    node * n = equivalence_table.find_op(connex_comp[i][j]);

                    int min = n ->data.front();


                    for(size_t i = 0; i < n->data.size(); i ++){
                        min = min> n->data.at(i)? n->data.at(i) : min;
                    }

                    connex_comp[i][j] = min;
                 }
             }
        }
    }



/*
    for(int i = 0; i< draw.rows; i++){
        for(int j = 0; j <draw.cols; j ++){
            std::cout << connex_comp[i][j] << " " ;
        }
        std::cout << "\n";
    }

    equivalence_table.print();*/




}


void MarchingSquare::apply_algorithm(int interpolation_method, bool simplification, int connexity){
    int num = 0;



    //Marching square
    for(int iso : isovaleurs){


             update_connex_group(connexity,iso);

           std::vector<std::vector<Point2f>> lignes = square_interpolation(num, interpolation_method);

           refractorisation(simplification,num++,lignes);
    }
}

// donne la carré de pixel
Square MarchingSquare::get_square(int x, int y) {


    Square square;

    int a = draw.at<Vec3b>(x,y).val[0] ;
    int b = draw.at<Vec3b>(x,y+marching).val[0] ;
    int c = draw.at<Vec3b>(x+marching,y+marching).val[0] ;
    int d = draw.at<Vec3b>(x+marching,y).val[0]  ;


    //creation du square
    square  = Square(std::vector<int>{a, b , c, d});


    return square;
}

void MarchingSquare::write_file(int iso, std::vector<Point2f> ligne) {
    std::ofstream myfile;
    String file = "polyline_isolevel_" + std::to_string(iso) + ".txt";
    myfile.open (file);

    for (unsigned int i = 0; i < ligne.size(); i+=2) {
        myfile << ligne[i].x << " " << ligne[i].y << "    " << ligne[i+1].x << " " << ligne[i+1].y << "\n";
    }

    myfile.close();
}

Point2f MarchingSquare::get_vector(Point2f pt1, Point2f pt2) {
    
    return Point2f(pt1.x - pt2.x, pt1.y - pt2.y);
}

float MarchingSquare::scalar_product(Point2f vec1, Point2f vec2) {
    
    return (vec1.x * vec2.y) - (vec2.x * vec1.y);
}

std::vector<std::vector<Point2f>> MarchingSquare::tri_chemin(std::vector<std::vector<Point2f>> lignes){
    
        // Initialization
        std::vector<std::vector<Point2f>> chemins;
        std::vector<Point2f> chemin;

        bool decrement = false;
        int error = 5000;

        Point2f endpoint;

        // While list of point is not empty
        while(lignes.size()!=0 && error != 0){
            error--;

             // If last iteration have not decrement the amount of point, we need to start a new path (new polygon)
             if(!decrement){
                 chemin = std::vector<Point2f>();
                std::vector<Point2f> line = lignes.back();
                lignes.pop_back();
                chemin.push_back(line.at(0));
                endpoint = line.at(1);
                decrement=true;
             }else{

                 // Looking for the next point of the polygon
                 std::vector<Point2f> removed;
                 bool has_add = false;
                 int cpt = 0;

                 // For each line, we look if a point match with the end of the path
                 for(std::vector<Point2f> line : lignes){
                     if(!has_add){
                         cpt++;
                         if((line.at(0).x >= chemin.back().x-ERREUR && line.at(0).x <= chemin.back().x+ERREUR &&line.at(0).y >= chemin.back().y-ERREUR&&line.at(0).y <= chemin.back().y+ERREUR)){


                                 chemin.push_back(line.at(1));
                                 has_add=true;


                         }else{
                             if((line.at(1).x >= chemin.back().x-ERREUR && line.at(1).x <= chemin.back().x+ERREUR && line.at(1).y >= chemin.back().y-ERREUR&& line.at(1).y <= chemin.back().y+ERREUR)){

                              chemin.push_back(line.at(0));
                              has_add=true;

                             }
                         }
                     }
                 }

                 // If a point is added to the path, we update variable
                 decrement=has_add;

                 if(!decrement){
                     chemin.push_back(endpoint);
                     chemins.push_back(chemin);
                 }

                 lignes.erase(lignes.begin()+cpt-1);
             }

        }

        // Close all paths
        chemin.push_back(endpoint);
        chemins.push_back(chemin);


        return chemins;
}

std::vector<std::vector<Point2f>> MarchingSquare::simplify(std::vector<std::vector<Point2f>> polygones){
    std::vector<std::vector<Point2f>> res;

    // For each polygons we simplify them
    for(std::vector<Point2f> polygone : polygones){

        unsigned long index = 1;
        std::vector<Point2f> sous_res;

        sous_res.push_back(polygone.front());

        while(index < polygone.size()-1){

            // Scalar product to check if three points are on the same line
            Point2f precedent = polygone.at((index-1)%polygone.size());
            Point2f actuel = polygone.at(index);
            Point2f suivant = polygone.at((index+1)%polygone.size());


            Point2f AB = get_vector(precedent, actuel);
            Point2f BC = get_vector(actuel, suivant);
           
            // If not, we need to add the point to the final list of pont
            if(scalar_product(AB, BC) != 0.0){
                sous_res.push_back(actuel);
            }

            index++;

        }

        sous_res.push_back(polygone.back());
        res.push_back(sous_res);

    }

    return res;
}

void MarchingSquare::write_file(){

    //Ecriture des fichiers
    for (unsigned int j = 0; j < isovaleurs.size(); j++) {
        write_file(isovaleurs[j], drawPoint[j]);
    }
}

std::vector<std::vector<Point2f>> MarchingSquare::square_interpolation(int index, int interpolation_method){

    int iso = isovaleurs.at(index);

    std::vector<std::vector<Point2f>> lignes;
    int y , x;

        //parcours de l'image
    #pragma omp parallel num_threads(NUM_THREAD)
    {

    #pragma omp for private(x,y)
    for (x = 0; x < draw.rows - marching  ; x += marching) {
        for (y= 0; y < draw.cols - marching ; y += marching) {

            //printf("Processus %d parmi %d %d/%d %d/%d\n", omp_get_thread_num(), omp_get_num_threads(),x,draw.rows - marching-1 ,y,draw.cols - marching-1);

            Square square = get_square(x, y);
            SquareState state = table.get(square.value(iso));

            // We get all neighboor corner for interpolation
            int neighboor[8] = {255,255,255,255,255,255,255,255};

            // We also get connex component label of the neighboor pixels
            int neighboor_connex[4] = {0,0,0,0};

            if(x-1>=0){
                Square rightSquare = get_square(x-1,y);
                neighboor[0] = rightSquare.d();
                neighboor[1]= rightSquare.a();
            }

            if(y-1>=0){
                Square topSquare = get_square(x,y-1);
                neighboor[2]= topSquare.a();
                neighboor[3] = topSquare.b();
            }

            if(x+1<draw.rows-marching){
                Square leftSquare = get_square(x+1,y);
                neighboor[4]= leftSquare.b();
                neighboor[5] = leftSquare.c();
            }

            if(y+1<draw.cols-marching){
                Square topSquare = get_square(x,y+1);
                neighboor[6]= topSquare.c();
                neighboor[7] = topSquare.d();
            }

            neighboor_connex[0] = connex_comp[x][y];
            neighboor_connex[1] = connex_comp[x][y+marching];
            neighboor_connex[2] = connex_comp[x+marching][y+marching];
            neighboor_connex[3] = connex_comp[x+marching][y];

            //Next, we interpolate and add lines to draw to the final point list
            for(std::vector<double> ligne : state.fct_interpolation(square, iso, interpolation_method, neighboor, neighboor_connex)){


                Point2f pt1(y + ligne.at(0)*marching, x +ligne.at(1)*marching);
                Point2f pt2(y +ligne.at(2)*marching, x +ligne.at(3)*marching);

                if(pt1.x != pt2.x || pt1.y != pt2.y){
                    std::vector<Point2f> new_line;
                    new_line.push_back(pt1);
                    new_line.push_back(pt2);


                    #pragma omp critical
                    {
                        lignes.push_back(new_line);
                     }


                   }

                }

            }
         }
    }


    return lignes;
}

void MarchingSquare::refractorisation(bool simplification, int index, std::vector<std::vector<Point2f>> lignes){
    int iso = isovaleurs.at(index);


     std::vector<std::vector<Point2f>> chemins;

     // We sort the list of lines to draw
     chemins =  tri_chemin(lignes);
     int line_amount = 0;
     int line_amount_simplify = 0;

     for(std::vector<Point2f> polygone : chemins)
         line_amount+=polygone.size();

     // Then simplify it
     if(simplification) chemins = simplify(chemins);

     for(std::vector<Point2f> polygone : chemins)
         line_amount_simplify+=polygone.size();

     // For each point we add a line to draw
     for(std::vector<Point2f> polygone : chemins){

         Point2f previous = polygone.back();
         Point2f previous_save = polygone.back();

         polygone.pop_back();

         for(Point2f p : polygone){

             if(previous!=p ){
                 drawPoint[index].push_back(p);
                 drawPoint[index].push_back(previous);

                  previous=p;
             }
         }


         drawPoint[index].push_back(previous_save);
         drawPoint[index].push_back(previous);
      }

     lineAmount[index] = line_amount;

      if(!simplification){
         std::vector<Point2f> points;
         for(std::vector<Point2f> p : lignes){
             points.push_back(p.front());
             points.push_back(p.back());
         }


         drawPoint[index]=points;
     }

     std::cout << "Isovaleur "<<iso<<": "<< line_amount<<" lignes avant simplification, "<<line_amount_simplify<<" lignes après simplification. ("<<line_amount-line_amount_simplify<<" lignes économisées)\n";

}

Mat MarchingSquare::cv_draw(bool debug){
    //Visual
    resize(draw, draw, Size(), def_out, def_out, INTER_NEAREST);
    for (unsigned int j = 0; j < isovaleurs.size(); j++) {
         draw_lines_OpenCV(drawPoint[j], isovaleurs[j]);

         // If debug mode, we draw a grid
         if(debug){
             for (double x = 0.5*def_out; x < draw.rows *def_out*marching ; x+=def_out*marching) {
                 for (double y = 0.5*def_out; y < draw.cols*def_out*marching ; y+=def_out*marching) {

                    Point2f pt1(y, x );
                    Point2f pt2(y,x+def_out*marching);
                    Point2f pt3(y+def_out*marching,x+def_out*marching);
                    Point2f pt4(y+def_out*marching,x);

                    line(draw, pt1, pt2, Scalar(0,255,0));
                    line(draw, pt2, pt3, Scalar(0,255,0));
                    line(draw, pt3, pt4, Scalar(0,255,0));
                    line(draw, pt4, pt1, Scalar(0,255,0));


                 }
             }
         }

    }
    return draw;
}

void MarchingSquare::draw_lines_OpenCV( std::vector<Point2f> ligne, int iso) {

    // Draw lines on a OpenCV Mat for drawing it on the screen
    for (unsigned int i = 0; i < ligne.size(); i+=2) {
        int p1x = ligne[i].x *def_out+ def_out*0.5;
        int p1y = ligne[i].y *def_out+ def_out*0.5;

        int p2x = ligne[i+1].x *def_out+ def_out*0.5;
        int p2y = ligne[i+1].y *def_out+ def_out*0.5;

        line(draw, Point(p1x, p1y), Point(p2x, p2y), Scalar(iso,255,255-iso));
    }
}
