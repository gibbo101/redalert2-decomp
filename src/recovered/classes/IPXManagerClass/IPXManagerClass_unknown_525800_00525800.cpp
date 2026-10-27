// void IPXManagerClass::unknown_525800(int index, int id, wchar_t const *name) (0x00525800)
// Gives the index'th connection a new ID and name.
#include "shared/ipx_manager.hpp"
// @ref _wcscpy=00783689

void IPXManagerClass::unknown_525800(int index, int id, wchar_t const *name)
{
    if (index < NumConnections) {
        Connection[index]->ID = id;
        wcscpy(Connection[index]->Name, name);
    }
}
