// MapClass::MapClass(NoInitClass const &noinit) (0x00547A60)
// Hypothesis: the restore-in-place constructor. The base screen keeps its
// state (vtable only) but the members are rebuilt empty and the hash-table
// pointers and per-frame state cleared.
#include "shared/map.hpp"

MapClass::MapClass(NoInitClass const &noinit) : GScreenClass(noinit), unknown_10(false), unknown_14(0), Cells(noinit)
{
    for (int clear = 0; clear < 12; clear++) {
        unknown_18[clear] = 0;
    }
    memset(unknown_7c, 0, sizeof(unknown_7c));
    for (int index = 0; index < 3; index++) {
        SubzoneTracking[index].Clear();
        unknown_7c[index] = 0;
    }
    unknown_14 = 0;
}
