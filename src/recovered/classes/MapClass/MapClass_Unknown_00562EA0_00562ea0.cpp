// void MapClass::Unknown_00562EA0() (0x00562EA0)
// Frees the zone data for Prog_End (TibSun Shutdown): the twelve unknown_18
// blocks, the unknown_14 hash table, and per subzone level the tracking
// vector (cleared) and the connection hash table; then the four global
// resets the destructor also calls.
#include "shared/map.hpp"
// @ref ?Unknown_006EA130@@YIXXZ=006ea130

void MapClass::Unknown_00562EA0()
{
    int index;
    for (index = 0; index < 12; index++) {
        if (unknown_18[index] != 0) {
            delete unknown_18[index];
            unknown_18[index] = 0;
        }
    }

    if (unknown_14 != 0) {
        delete unknown_14;
        unknown_14 = 0;
    }

    for (index = 0; index < 3; index++) {
        SubzoneTracking[index].Clear();
        if (unknown_7c[index] != 0) {
            delete unknown_7c[index];
            unknown_7c[index] = 0;
        }
    }

    Unknown_00710B50();
    Unknown_00711C70();
    Unknown_006E9670();
    Unknown_006EA130();
}
