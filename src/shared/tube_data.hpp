// The Tube unit's own data and helper (Tube.cpp, 0x006EF000-0x006EF9EF). Include only from Tube-unit
// sources, after the vector macros and shared/tube.hpp.
#ifndef RA2_SHARED_TUBE_DATA_HPP
#define RA2_SHARED_TUBE_DATA_HPP

#include "shared/vector_class.hpp"

// The [Tubes] section name: a file-static pointer VC6 reloads per use (0x007F8628), as the Rules unit's names.
static char const * const TubeSection_Tubes = "Tubes";

// The position of a tube in the list, or -1 (the constructor and destructor expand it; written out
// because the list's own lookup stays a call).
static inline int Tube_Index(TubeClass *tube)
{
    int index = 0;
    for (;; index++) {
        if (index >= unknown_TubeClass_list_008661c8.Count()) {
            index = -1;
            break;
        }
        if (unknown_TubeClass_list_008661c8[index] == tube) {
            break;
        }
    }
    return index;
}

#endif
