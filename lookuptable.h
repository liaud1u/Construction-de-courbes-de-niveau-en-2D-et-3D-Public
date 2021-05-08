#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H
#include "squarestate.h"

/**
 ** @brief LookupTable class to get SquareState of the MarchingSquare algorithm
 ** @author A. LIAUD
 **/

class LookupTable
{
private:

    /// @brief Array of all state
    SquareState * table;

public:

    /// @brief SquareState matching all corner to 0
    const SquareState VOID = SquareState(0);

    /// @brief SquareState matching all corner to 1
    const SquareState FULL = SquareState(15);

    /// @brief SquareState matching only the bottom left corner to 1
    const SquareState BOTTOM_LEFT_CORNER = SquareState({{'O','S'}},1);

    /// @brief SquareState matching only the bottom right corner to 1
    const SquareState BOTTOM_RIGHT_CORNER = SquareState({{'E','S'}},2);

    /// @brief SquareState matching only the top left corner to 1
    const SquareState TOP_LEFT_CORNER =  SquareState({{'N','O'}},8);

    /// @brief SquareState matching only the top right corner to 1
    const SquareState TOP_RIGHT_CORNER = SquareState({{'N','E'}},4);

    /// @brief SquareState matching only the top corners to 1
    const SquareState TOP_SIDE =  SquareState({{'E','O'}},12);

    /// @brief SquareState matching only the bottom corners to 1
    const SquareState BOTTOM_SIDE =  SquareState({{'E','O'}},3);

    /// @brief SquareState matching only the right corners to 1
    const SquareState RIGHT_SIDE =  SquareState({{'N','S'}},6);

    /// @brief SquareState matching only the left corners to 1
    const SquareState LEFT_SIDE =  SquareState({{'N','S'}},9);

    /// @brief SquareState matching only the bottom left corners to 0
    const SquareState BOTTOM_LEFT_CORNER_VOID = SquareState({{'O','S'}},14);

    /// @brief SquareState matching only the bottom right corners to 0
    const SquareState BOTTOM_RIGHT_CORNER_VOID =  SquareState({{'E','S'}},13);

    /// @brief SquareState matching only the top left corners to 0
    const SquareState TOP_LEFT_CORNER_VOID =  SquareState({{'N','O'}},7);

    /// @brief SquareState matching only the top right corners to 0
    const SquareState TOP_RIGHT_CORNER_VOID =  SquareState({{'N','E'}},11);

    /// @brief SquareState matching only the top right and bottom left corner to 1
    const SquareState TOP_RIGHT_TO_BOT_LEFT =  SquareState({{'N','O'},{'S','E'}},5);

    /// @brief SquareState matching only the top left and bottom right corner to 1
    const SquareState TOP_LEFT_TO_BOT_RIGHT =  SquareState({{'N','E'},{'S','O'}},10);

    /// @brief Default constructor
    LookupTable();

    /// @brief Getter of SquareState matching to a given index
    /// @param int index of the SquareState we want
    /// @return SquareState matching to the index given
    SquareState get(int index);

    /// @brief Destructor of the table
    ~LookupTable(){
        delete [] table;
    }
};

#endif // LOOKUPTABLE_H
