// void IsometricTileTypeClass::Load_Tiles(bool skip_iteration, bool is_random) (0x0052B2E0)
#include "shared/isometric_tile_type.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/tileset_index.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/cell.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
// @ref ?Clear_Icon@CellClass@@QBEHHH@Z=004767a0
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_tileset_a52f00@@3HA=00a52f00
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550

void __fastcall IsometricTileTypeClass::Load_Tiles(bool skip_iteration, bool is_random)
{
    CDTimerClass<SystemTimerClass> timer = 0;
    IsometricTileTypeClass *ptr;

    if (!skip_iteration) {
        Map.Unknown_0055A550();
        CellClass *cptr = Map.Unknown_0055A490();
        while (cptr != 0) {
            int type = cptr->IsoTileIndex;
            int index = 0;
            int num;
            if (type != 0xFFFF && type < IsoTileTypes.Count()) {
                ptr = IsoTileTypes[type];
                if (ptr->NumTileTypesInSet > 1) {
                    num = ptr->NumTileTypesInSet;
                    if (ptr->Is_Randomized((unsigned char)cptr->unknown_11a)) {
                        index = (cptr->unknown_140 >> 13) & 1;
                    } else {
                        num = ptr->NumTileTypesInSet;
                        index = cptr->Clear_Icon(cptr->IsoTileIndex, num);
                    }
                }
            } else {
                ptr = IsoTileTypes[unknown_tileset_a52f00];
                num = ptr->NumTileTypesInSet;
                index = cptr->Clear_Icon(unknown_tileset_a52f00, num);
            }
            ptr = ptr->Next_Tile_From_Set(index);
            ptr->UseCount++;
            cptr = Map.Unknown_0055A490();
        }
    }

    int tile_count = 0;
    int bytes = 0;
    timer = 1;
    for (int i = 0; i < IsoTileTypes.Count(); i++) {
        if (!timer) {
            Service_Game_IO_00481fb0();
            timer = 4;
        }
        ptr = IsoTileTypes[i];
        while (ptr != 0) {
            if (ptr->unknown_2c4 && strlen(ptr->Filename)) {
                if (!skip_iteration && ptr->UseCount == 0 && (!is_random || !ptr->IsRequiredForRMG)) {
                    if (ptr->unknown_a4 != 0) {
                        delete [] (unsigned char *)ptr->unknown_a4;
                        ptr->unknown_a4 = 0;
                        ptr->unknown_a8 = false;
                    }
                } else {
                    if (ptr->unknown_a4 == 0) {
                        bytes += ptr->unknown_func_52b560();
                        tile_count++;
                    }
                }
            }
            ptr = (IsometricTileTypeClass *)ptr->unknown_28c;
        }
    }
    Debug_Printf("Loaded %d isometric tiles consuming %d Kb\n", tile_count, bytes / 1024);
}
// @ref ??_C@_0CL@HLMC@Loaded?5?$CFd?5isometric?5tiles?5consum@=007df210
