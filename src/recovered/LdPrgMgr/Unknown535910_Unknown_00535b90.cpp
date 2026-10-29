// void Unknown535910::Unknown_00535B90() -- 0x00535B90
// Opens LOAD.MIX once and loads the loading-screen art.
#include "shared/unknown_globals.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/id_source.hpp"
#include "shared/cd.hpp"
// @ref ?Unknown_006f24a0@@YIXH@Z=006f24a0
// @ref ?Unknown_006f25c0@@YIXXZ=006f25c0
// @ref ??_C@_08HBA@LOAD?4MIX?$AA@=007df468
// @ref ??0?$MixFileClass@VCCFileClass@@@@QAE@PBDPBVPKey@@@Z=005952f0
// @ref ?FastKey@@3VPKey@@A=00839010

void Unknown535910::Unknown_00535B90()
{
    if (LoadMix == 0) {
        LoadMix = new MixFileClass<CCFileClass>("LOAD.MIX", &FastKey);
        if (LoadMix == 0) {
            return;
        }
    }
    if (unknown_game_mode_a3d298 == 0) {
        Unknown_006f24a0(unknown_id_source_a3d290->unknown_2239 == 0);
    } else {
        Unknown_006f25c0();
    }
}
