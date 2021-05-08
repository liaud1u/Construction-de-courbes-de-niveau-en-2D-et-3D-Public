#include "cube.h"

Cube::Cube()
{

}

int Cube::value(int palier){
    return (points_state[7]<palier?1:0)*128+(points_state[6]<palier?1:0)*64+(points_state[5]<palier?1:0)*32+(points_state[4]<palier?1:0)*16+(points_state[3]<palier?1:0)*8+(points_state[2]<palier?1:0)*4+(points_state[1]<palier?1:0)*2+(points_state[0]<palier?1:0);
}
