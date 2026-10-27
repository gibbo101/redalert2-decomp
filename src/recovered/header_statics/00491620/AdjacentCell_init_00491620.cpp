#include "shared/coord.hpp"
extern Cell const AdjacentCell[8];
Cell const AdjacentCell[8] = {
 Cell(0,-1),Cell(1,-1),Cell(1,0),Cell(1,1),
 Cell(0,1),Cell(-1,1),Cell(-1,0),Cell(-1,-1)
};
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
