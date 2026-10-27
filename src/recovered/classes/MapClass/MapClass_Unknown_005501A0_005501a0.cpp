// bool MapClass::Unknown_005501A0(Cell const &cell) (0x005501A0)
// Runs 0x00566C30 on every zone connection within 3 of a cell that has
// +0x08 set, clearing it; when no connection is near, the connections are
// rebuilt (0x0054FDA0) and searched once more. Whether any was flagged.
#include "shared/map.hpp"
// @ref ?Unknown_005500D0@MapClass@@QAEHABVCell@@HH@Z=005500d0
// @ref ?Unknown_0054FDA0@MapClass@@QAEXXZ=0054fda0
// @ref ?Unknown_00566C30@MapClass@@QAEXPAUZoneConnectionClass@@@Z=00566c30

bool MapClass::Unknown_005501A0(Cell const &cell)
{
    int index = Unknown_005500D0(cell, 3, 0);
    if (index == -1) {
        Unknown_0054FDA0();
        index = Unknown_005500D0(cell, 3, 0);
        if (index == -1) {
            return false;
        }
    }
    bool found = false;
    while (index != -1) {
        if (ZoneConnections[index].unknown_08) {
            Unknown_00566C30(&ZoneConnections[index]);
            found = true;
            ZoneConnections[index].unknown_08 = false;
        }
        index++;
        index = Unknown_005500D0(cell, 3, index);
    }
    return found;
}
