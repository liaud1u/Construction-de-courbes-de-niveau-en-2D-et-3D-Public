#include "unionfind.h"

UnionFind::UnionFind(){}

void UnionFind::union_op(node * id1, node * id2){
   // If the two nodes are not the same
   if(id1->id != id2->id){

        // We get all the data of the second node
        std::vector<int> data2 = id2->data;

        // We add all the data to the first
        for(int i : data2){
            id1->data.push_back(i);
        }


        int index = 0;

        // We remove the second node
        for(node n : data){
            if(n.id==id2->id){
                data.erase(data.begin()+index);
                return;
            }
            index++;
        }
    }

}

node * UnionFind::find_op(int element){
    // For each node we check if data of the node contain element, if yes, we return the node
    for(node &group : data){
        for(int i : group.data){
            if(i==element){
                return &group;
            }
        }
    }
}

void UnionFind::add_node(int value){
    // If the structure does not contains the value, we add it in a new node
    if(!contains(value))
         data.push_back(node(cpt++,value));
}

void UnionFind::print(){
    for(node n : data){
        std::cout << n.id << " " << n.data.size() << ": ";
        for(int i : n.data){
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

bool UnionFind::contains(int value){
    // For each node we check if data contains value
    for(node &group : data){
        for(int i : group.data){
            if(i==value){
                return true;
            }
        }
    }
    return false;
}
