#include "square.h"

int Square::value(int palier){
    // Return 8 x first point state + 4 x second point state + 2 x third point state + last point state
    return (points_state[0]>=palier?1:0)*8+(points_state[1]>=palier?1:0)*4+(points_state[2]>=palier?1:0)*2+(points_state[3]>=palier?1:0);
}
