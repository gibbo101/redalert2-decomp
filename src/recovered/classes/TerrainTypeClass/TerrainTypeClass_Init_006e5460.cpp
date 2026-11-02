// static void __fastcall TerrainTypeClass::Init(int theater) (0x006E5460)
// Reloads the theater images of theater-specific terrain types when the
// theater changes (or a reload is forced), freeing owned images first.
// Assumptions: unknown_1fc is "Theater="; fullname size 512.
#include "shared/terrain_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?unknown_loaded_theater_7d88dc@@3HA=007d88dc
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref __makepath=007831f0
// @ref ??3@YAXPAX@Z=00781d3b

void __fastcall TerrainTypeClass::Init(int theater)
{
    if (unknown_a40d13 || theater != unknown_loaded_theater_7d88dc) {
        for (int index = 0; index < TerrainTypes.Count(); index++) {
            TerrainTypeClass *terrain = TerrainTypes[index];
            if (terrain->unknown_1fc) {
                char fullname[512];
                _makepath(fullname, 0, 0, terrain->ID, Theaters[theater].Suffix);
                if (terrain->unknown_a8 && terrain->unknown_a4 != 0) {
                    operator delete(terrain->unknown_a4);
                }
                terrain->unknown_a4 = 0;
                terrain->unknown_a8 = false;
                terrain->unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
            }
        }
    }
}
