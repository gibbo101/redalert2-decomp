// void Unknown535910::Unknown_00536E20() (0x00536E20)
// Frees the owned buffers, the loading-screen art (0x006F2510, 0x006F26D0),
// LOAD.MIX and the surface.
#include "shared/unknown_globals.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/surface.hpp"
// @ref ?Unknown_Free_Art_Sets_006F2510@@YIXXZ=006f2510
// @ref ?Unknown_Free_Art_Pair_006F26D0@@YIXXZ=006f26d0

void Unknown535910::Unknown_00536E20()
{
    if (unknown_4c && unknown_40 != 0) {
        operator delete(unknown_40);
    }
    unknown_40 = 0;
    if (unknown_4d && unknown_44 != 0) {
        operator delete(unknown_44);
    }
    unknown_44 = 0;
    if (unknown_4e && unknown_48 != 0) {
        operator delete(unknown_48);
    }
    unknown_48 = 0;
    Unknown_Free_Art_Sets_006F2510();
    Unknown_Free_Art_Pair_006F26D0();
    if (LoadMix != 0) {
        delete LoadMix;
        LoadMix = 0;
    }
    delete unknown_5c;
    unknown_5c = 0;
}
