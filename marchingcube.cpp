#include "marchingcube.h"
#include "unionfind.h"

#define RANDOM_INTENSITY true
#define MULT 1000

MarchingCube::MarchingCube()
{

}

MarchingCube::MarchingCube(std::string file_path, int marching,std::vector<int> isovaleurs, int connexity):marching(marching), image_path(file_path),isovaleurs(isovaleurs), connexity(connexity){
    std::ifstream in;
    cpt_vertice=0;
    std::vector<Point3D> input;
    srand (time(NULL));
    std::cout << file_path << "\n";

    in.open(file_path,std::ios::binary);

    if(!in.is_open()){
        std::cerr << "Impossible de charger l'objet\n";
        in.close();
    }else{
        std::string line = "";

        while(std::getline(in,line)){
            std::istringstream splited_string(line.c_str());
            std::string  x, y, z, intensity;
            splited_string >> x >> y >> z >> intensity;
            Point3D p;
            if(intensity == "")
                p = Point3D(std::stof(x),std::stof(y),std::stof(z),0);
            else
                p = Point3D(std::stof(x),std::stof(y),std::stof(z),std::stof(intensity));

            input.push_back(p);
        }

        minX = input.front().get_x();
        maxX = input.front().get_x();
        minY = input.front().get_y();
        maxY = input.front().get_y();
        minZ = input.front().get_z();
        maxZ = input.front().get_z();

        for(Point3D p : input){
            minX = std::min(minX,(int)(p.get_x()));
            minY = std::min(minY,(int)(p.get_y()));
            minZ = std::min(minZ,(int)(p.get_z()));
            maxX = std::max(maxX,(int)(p.get_x()));
            maxY = std::max(maxY,(int)(p.get_y()));
            maxZ = std::max(maxZ,(int)(p.get_z()));
        }

        col = maxX - minX +3;
        rows = maxY - minY +3;
        depth = maxZ - minZ  +3;
        
       

        obj = new int**[col];


        for(int x = 0; x<col;x++){
            obj[x] = new int*[rows];
            for(int y = 0; y<rows;y++){
                obj[x][y] = new int[depth];
                for(int z = 0; z < depth; z++){
                    obj[x][y][z] =  255;
                }
            }
        }


        for(Point3D p : input){
            //std::cout << p.get_x()-minX << " < "<< col<< " " << p.get_y()-minY << " < "<< rows<< " " << p.get_z()-minZ << " < "<< depth << "\n";
            obj[1+(int)p.get_x()-minX][1+(int)p.get_y()-minY][1+(int)p.get_z()-minZ] = RANDOM_INTENSITY? rand() % 128 :p.get_intensity();
        }




        /*for(int x = 0; x<col;x++){
            for(int y = 0; y<rows;y++){
                for(int z = 0; z < depth; z++){
                    std::cout << obj[x][y][z] << " " ;
                }
                std::cout << "\n" ;
            }
            std::cout << "Face "<<x << "\n" ;
        }*/

    }

    cpt_vertice = new int[isovaleurs.size()];

    for(int i = 0; i<isovaleurs.size(); i++){
        faces.push_back({});
        vertices.push_back({});
    }

}


void MarchingCube::apply_algorithm(){
    int num = 0;



    //Marching square
    for(int iso : isovaleurs){
          cube_interpolation(num++);

          for(int x = 0; x<col;x++){
              for(int y = 0; y<rows;y++){
                  delete [] connex_comp[x][y];
              }
              delete [] connex_comp[x];
          }

          delete [] connex_comp;
    }
}



void MarchingCube::cube_interpolation(int index){
    int isoval = isovaleurs.at(index);



    update_connex_group(connexity, isoval);
    
    int x, y, z;
    cpt_vertice[index] = 0;
    faces.at(index).clear();
    vertices.at(index).clear();


    #pragma omp parallel num_threads(NUM_THREAD)
    {

    #pragma omp for private(x,y,z)

        for(x = 0; x<col-1;x+=marching){
            for(y = 0; y<rows-1;y+=marching){
                for(z = 0; z < depth-1; z+=marching){
                    
                     int neighboor_connex[8] = {0,0,0,0,0,0,0,0};

                      Cube cube = get_cube(x,y,z);
                      int id = cube.value(isoval);
                      CubeState state = table.get(id);
                    
                    neighboor_connex[0] = connex_comp[x][y][z];
                    neighboor_connex[1] = connex_comp[x][y+marching][z];
                    neighboor_connex[2] = connex_comp[x+marching][y+marching][z];
                    neighboor_connex[3] = connex_comp[x+marching][y][z];
                    neighboor_connex[4] = connex_comp[x][y][z+marching];
                    neighboor_connex[5] = connex_comp[x+marching][y][z+marching];
                    neighboor_connex[6] = connex_comp[x][y+marching][z+marching];
                    neighboor_connex[7] = connex_comp[x+marching][y+marching][z+marching];


                      for(std::vector<Point3D> face : state.fct_interpolation(cube,id, neighboor_connex, isoval)){
                          std::vector<int> face_index;

                          for(Point3D vertice : face){
                              Point3D p(vertice.x*marching+x-minX, vertice.y*marching+y-minY, vertice.z*marching+z-minZ);

                              #pragma omp critical
                              {
                                  vertices.at(index).push_back(p);
                                  face_index.push_back(cpt_vertice[index]);
                                  cpt_vertice[index]++;
                              }
                          }


                        #pragma omp critical
                        {
                              faces.at(index).push_back(face_index);
                         }
                      }
                }
            }
        }
    }
}



Cube MarchingCube::get_cube(int x, int y, int z) {


    Cube cube;

    int a = obj[x][y][z] ;
    int b = obj[x+marching][y][z] ;
    int c = obj[x+marching][y+marching][z] ;
    int d = obj[x][y+marching][z]  ;
    int e = obj[x][y][z+marching];
    int f = obj[x+marching][y][z+marching];
    int g = obj[x+marching][y+marching][z+marching];
    int h = obj[x][y+marching][z+marching];


    cube  = Cube(std::vector<int>{a, b , c, d,e,f,g,h});


    return cube;
}

void MarchingCube::update_connex_group(int connexity, int isoval) {
    
    connex_comp = new int**[col];
    
    //Initialize map of connex components
    for (int x = 0; x < col; x++) {
        connex_comp[x] = new int*[rows];
        for(int y = 0; y <rows; y ++){
            connex_comp[x][y] = new int[depth];
            for (int z = 0; z < depth; z++) {
                connex_comp[x][y][z] = 0;
            }
        }
    }
    
    UnionFind equivalence_table;
    int cpt_label = 1;
    
    //First pass
    for (int x = 0; x < col; x++) {
        for (int y = 0; y < rows; y++) {
            for (int z = 0; z < depth; z++) {
                
                int val = obj[x][y][z];
                if (val < isoval) {
                   // std::cout << val << std::endl;
                    
                if (connexity == 6) {
                    
                    //check left
                    if (x-1 >= 0 && connex_comp[x-1][y][z] != 0) {
                        int left_val =connex_comp[x-1][y][z];
                        
                        //check top
                        if (y-1 >= 0 && connex_comp[x][y-1][z] != 0) {
                            int top_val = connex_comp[x][y-1][z];
                            
                            //check front
                            if (z-1 >= 0 && connex_comp[x][y][z-1] != 0) {
                                
                                int front_val = connex_comp[x][y][z-1];
                                
                                std::vector<int> equiv = {top_val,left_val, front_val};
                                
                                equivalence_table.add_node(top_val);
                                equivalence_table.add_node(left_val);
                                equivalence_table.add_node(front_val);
                                equivalence_table.union_op(equivalence_table.find_op(top_val),equivalence_table.find_op(left_val));
                                equivalence_table.union_op(equivalence_table.find_op(top_val),equivalence_table.find_op(front_val));
                                equivalence_table.union_op(equivalence_table.find_op(left_val),equivalence_table.find_op(front_val));
                                
                                if (left_val < top_val && left_val < front_val) {
                                    connex_comp[x][y][z] = left_val;
                                    
                                } else if (top_val < left_val && top_val < front_val) {
                                    connex_comp[x][y][z] = top_val;
                                    
                                } else {
                                    connex_comp[x][y][z] = front_val;
                                }
                            
                                //front is 0
                            } else {
                                
                                std::vector<int> equiv = {top_val,left_val};
                                
                                equivalence_table.add_node(top_val);
                                equivalence_table.add_node(left_val);
                                equivalence_table.union_op(equivalence_table.find_op(top_val),equivalence_table.find_op(left_val));

                                connex_comp[x][y][z]=top_val<left_val?left_val:top_val;
                            }
                            
                           //top is 0
                        } else {
                            //check front
                            if (z-1 >= 0 && connex_comp[x][y][z-1] != 0) {
                                
                                int front_val = connex_comp[x][y][z-1];
                                std::vector<int> equiv = {front_val,left_val};
                                
                                equivalence_table.add_node(front_val);
                                equivalence_table.add_node(left_val);
                                equivalence_table.union_op(equivalence_table.find_op(front_val),equivalence_table.find_op(left_val));
                                
                                connex_comp[x][y][z]=front_val<left_val?left_val:front_val;
                                
                            } else {
                                connex_comp[x][y][z] = left_val;
                            }
                        }
                       //left is 0
                    } else {
                        
                        //check top
                        if (y-1 >= 0 && connex_comp[x][y-1][z] != 0) {
                            int top_val = connex_comp[x][y-1][z];
                            
                            if (z-1 >= 0 && connex_comp[x][y][z-1] != 0) {
                                
                                int front_val = connex_comp[x][y][z-1];
                                std::vector<int> equiv = {front_val,top_val};
                                
                                equivalence_table.add_node(front_val);
                                equivalence_table.add_node(top_val);
                                equivalence_table.union_op(equivalence_table.find_op(front_val),equivalence_table.find_op(top_val));
                                
                                connex_comp[x][y][z]=front_val<top_val?top_val:front_val;
                                
                            } else {
                                connex_comp[x][y][z] = top_val;
                            }
                            //top is 0
                        } else {
                            
                            if (z-1 >= 0 && connex_comp[x][y][z-1] != 0) {
                                
                                int front_val = connex_comp[x][y][z-1];
                                connex_comp[x][y][z] = front_val;
                            } else {
                                connex_comp[x][y][z] = cpt_label++;
                            }
                        }
                    }
                    
                } else if (connexity == 18 || connexity == 26) {
                    std::vector<int> possible_case;
                    
                    //left
                    if (x-1 >= 0 && connex_comp[x-1][y][z] !=0) {
                        possible_case.push_back(connex_comp[x-1][y][z]);
                    }
                    
                    //top
                    if (y-1 >= 0 && connex_comp[x][y-1][z] !=0) {
                        possible_case.push_back(connex_comp[x][y-1][z]);
                    }
                    
                    //front
                    if (z-1 >= 0 && connex_comp[x][y][z-1] !=0) {
                        possible_case.push_back(connex_comp[x][y][z-1]);
                    }
                    
                    //top_left
                    if (x-1 >=0 && y-1 >= 0 && connex_comp[x-1][y-1][z] != 0) {
                        possible_case.push_back(connex_comp[x-1][y-1][z]);
                    }
                    
                    //top_right
                    if (x+1 < col && y-1 >= 0 && connex_comp[x+1][y-1][z] != 0) {
                        possible_case.push_back(connex_comp[x+1][y-1][z]);
                    }
                    
                    //left_front
                    if (x-1 >=0 && z-1 >= 0 && connex_comp[x-1][y][z-1] != 0) {
                        possible_case.push_back(connex_comp[x-1][y][z-1]);
                    }
                    
                    //right_front
                    if (x+1 < col && z-1 >= 0 && connex_comp[x+1][y][z-1] != 0) {
                        possible_case.push_back(connex_comp[x+1][y][z-1]);
                    }
                    
                    //top_front
                    if (y-1 >=0 && z-1 >= 0 && connex_comp[x][y-1][z-1] != 0) {
                        possible_case.push_back(connex_comp[x][y-1][z-1]);
                    }
                    
                    if (connexity == 26) {
                        
                        //top_left_front
                        if (x-1 >=0 && y-1 >= 0 && z-1 >= 0 && connex_comp[x-1][y-1][z-1] != 0) {
                            possible_case.push_back(connex_comp[x-1][y-1][z]);
                        }
                        
                        //top_right_front
                        if (x+1 < col && y-1 >= 0 && z-1 >= 0 && connex_comp[x+1][y-1][z-1] != 0) {
                            possible_case.push_back(connex_comp[x+1][y-1][z]);
                        }
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
                        connex_comp[x][y][z]=cpt_label++;
                    else{
                        int min = possible_case.front();

                        for(int i : possible_case){
                            min = min > i ? i : min;
                        }
                        connex_comp[x][y][z]=min;
                    }
                }
                }
            }
        }
    }
    
    // Simplification of the map using the equivalence table
    for(int x = 0; x < col; x++){
        for(int y = 0; y <rows; y ++){
            for (int z =0; z < depth; z++) {
                if(connex_comp[x][y][z] !=0){

                    // If possible, we take the minimum label of the equivalence
                    if(equivalence_table.contains(connex_comp[x][y][z])){
                        node * n = equivalence_table.find_op(connex_comp[x][y][z]);

                        int min = n ->data.front();


                        for(size_t i = 0; i < n->data.size(); i ++){
                            min = min> n->data.at(i)? n->data.at(i) : min;
                        }

                        connex_comp[x][y][z] = min;
                    }
                }
            }
        }
    }
    
   /*for (int k = 0; k < depth; k++) {
    for(int j = 0; j < rows; j ++){
        for(int i = 0; i< col; i++){
                
                 std::cout << connex_comp[i][j][k] << " " ;
            }
            
            std::cout << "\n";
        }
        std::cout << "\n";
    }*/

    //    equivalence_table.print();
}



void MarchingCube::write_file(){
    int index_iso = 0;

    for(int iso : isovaleurs){
        std::ofstream myfile;
        String file = "output_marchingcube"+std::to_string(iso)+".off";
        myfile.open (file);
        myfile << "OFF\n";
        myfile << vertices.at(index_iso).size() << " " << faces.at(index_iso).size() << " " << "0\n";
        for (Point3D ver : vertices.at(index_iso)) {
            myfile << ver.get_x()*MULT << " "<< ver.get_y()*MULT << " " << ver.get_z()*MULT << "\n";
        }

        for(std::vector<int> face : faces.at(index_iso)){
            myfile << "3";
            for(int index : face)
                myfile << " "<< index ;
            myfile << "\n";
        }

        index_iso++;
        myfile.close();
    }

}
