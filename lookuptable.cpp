#include "lookuptable.h"

LookupTable::LookupTable()
{
    // Initializing the SquareState array
    table = new SquareState[16];

    // Adding SquareState matching the good index
    table[0] = VOID;
    table[1] = BOTTOM_LEFT_CORNER;
    table[2] = BOTTOM_RIGHT_CORNER;
    table[3] = BOTTOM_SIDE;
    table[4] = TOP_RIGHT_CORNER;
    table[5] = TOP_RIGHT_TO_BOT_LEFT;
    table[6] = RIGHT_SIDE;
    table[7] = TOP_LEFT_CORNER_VOID;
    table[8] = TOP_LEFT_CORNER;
    table[9] = LEFT_SIDE;
    table[10] = TOP_LEFT_TO_BOT_RIGHT;
    table[11] = TOP_RIGHT_CORNER_VOID;
    table[12] = TOP_SIDE;
    table[13] = BOTTOM_RIGHT_CORNER_VOID;
    table[14] = BOTTOM_LEFT_CORNER_VOID;
    table[15] = FULL;

}


SquareState LookupTable::get(int index){
    return table[index];
}
