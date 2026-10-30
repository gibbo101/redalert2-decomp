#include "shared/coord.hpp"
int Cell::Not_Equal_0058db50(Cell const &other) const
{
    if(X==other.X && Y==other.Y)return 0;
    return 1;
}
