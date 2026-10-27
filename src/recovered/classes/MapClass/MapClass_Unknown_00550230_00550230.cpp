// bool MapClass::Unknown_00550230(Cell const &cell) (0x00550230)
// Every zone connection within 3 of a cell that is not flagged gets +0x08
// set, 0x00566F90 run on it and its From-To path tested (0x0054F7C0);
// when no connection is near, the connections are rebuilt (0x0054FDA0)
// and searched once more. Whether any tested path failed.
#include "shared/map.hpp"
// @ref ?Unknown_005500D0@MapClass@@QAEHABVCell@@HH@Z=005500d0
// @ref ?Unknown_0054FDA0@MapClass@@QAEXXZ=0054fda0
// @ref ?Unknown_00566F90@MapClass@@QAEXPAUZoneConnectionClass@@@Z=00566f90

bool MapClass::Unknown_00550230(Cell const &cell)
{
    int index = Unknown_005500D0(cell, 3, 0);
    if (index == -1) {
        Unknown_0054FDA0();
        index = Unknown_005500D0(cell, 3, 0);
        if (index == -1) {
            return false;
        }
    }
    bool failed = false;
    while (index != -1) {
        if (!ZoneConnections[index].unknown_08) {
            ZoneConnections[index].unknown_08 = true;
            Unknown_00566F90(&ZoneConnections[index]);
            if (!Unknown_0054F7C0(ZoneConnections[index].From, ZoneConnections[index].To, 0, false, 0, false)) {
                failed = true;
            }
        }
        index++;
        index = Unknown_005500D0(cell, 3, index);
    }
    return failed;
}
