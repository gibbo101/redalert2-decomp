// void Unknown_006F57E0() (0x006F57E0)
// Deletes the list at 0x00AC1344 (Prog_End calls it; the list is the one Unknown_006F79C0 rebuilds).
// @ref ?unknown_list_ac1344@@3PAUUnknownPointerList@@A=00ac1344
#include "shared/uicmnds.hpp"
#include "shared/unknown_globals.hpp"

extern UnknownPointerList *unknown_list_ac1344;

void Unknown_006F57E0()
{
    if (unknown_list_ac1344 != 0) {
        delete (DynamicVectorClass<TechnoClass *> *)unknown_list_ac1344;
        unknown_list_ac1344 = 0;
    }
}
