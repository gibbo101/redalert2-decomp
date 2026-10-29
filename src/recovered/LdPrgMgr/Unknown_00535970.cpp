// void Unknown_00535970() -- 0x00535970
// Releases and deletes the loading progress object.
#include "shared/unknown_globals.hpp"
// @ref ?unknown_load_progress_a6e7c4@@3PAUUnknown535910@@A=00a6e7c4
// @ref ?Unknown_00536E20@Unknown535910@@QAEXXZ=00536e20

void Unknown_00535970()
{
    if (unknown_load_progress_a6e7c4 != 0) {
        unknown_load_progress_a6e7c4->Unknown_00536E20();
        delete unknown_load_progress_a6e7c4;
    }
    unknown_load_progress_a6e7c4 = 0;
}
