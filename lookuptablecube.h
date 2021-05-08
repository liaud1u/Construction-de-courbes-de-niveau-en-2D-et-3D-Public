#ifndef LOOKUPTABLECUBE_H
#define LOOKUPTABLECUBE_H

#include "cubestate.h"

/**
 ** @brief LookupTable class to get CubeState of the MarchingCube algorithm
 ** @author A. LIAUD
 **/
class LookUpTableCube
{
private:

    /// @brief Array of all state
    CubeState * table;

public:

    /// @brief Default constructor
    LookUpTableCube();

    /// @brief getter of the state in the LUT
    /// @param int index
    /// @return CubeState of the LUT
    CubeState get(int index);

    /// @brief Destructor of the LUT
    ~LookUpTableCube(){
        delete [] table;
    }
};

#endif // LOOKUPTABLECUBE_H
