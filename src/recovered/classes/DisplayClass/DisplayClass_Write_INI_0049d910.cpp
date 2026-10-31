// void DisplayClass::Write_INI_0049D910(CCINIClass &ini) (0x0049D910)
// Writes the map's sections of a scenario INI (TibSun DisplayClass::Write_INI): [Map] Theater,
// Size and LocalSize, the waypoints, [CellTags] (one entry x + y * 1000 per tagged cell) and the
// IsoMapPack5 block packed through the surface 0x00839958's memory (IsoMapPack..4 are cleared).
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/ccini_class.hpp"
#include "shared/id_source.hpp"
#include "shared/tag.hpp"
#include "shared/tag_type.hpp"
#include "shared/surface.hpp"
#include "shared/buffer_pipe.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref _?NAME@?1??Write_INI_0049D910@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e844
// @ref ??_C@_09OOBE@LocalSize?$AA@=007d5e14
// @ref ??_C@_04BBDK@Size?$AA@=007d5e28
// @ref ??_C@_07OHHF@Theater?$AA@=007cf004
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_03DIFO@Map?$AA@=007d5c9c
// @ref ??_C@_08CFMK@CellTags?$AA@=007d5c90
// @ref ??_C@_0L@IADI@IsoMapPack?$AA@=007d5cd0
// @ref ??_C@_0M@LMDO@IsoMapPack2?$AA@=007d5cc4
// @ref ??_C@_0M@BGKJ@IsoMapPack3?$AA@=007d5cb8
// @ref ??_C@_0M@EDEM@IsoMapPack4?$AA@=007d5cac
// @ref ??_C@_0M@OJNL@IsoMapPack5?$AA@=007d5ca0
// @ref _?CELLTRIG@?1??Write_INI_0049D910@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e848
// @ref _?MAPPACK1@?M@??Write_INI_0049D910@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e84c
// @ref _?MAPPACK2@?M@??Write_INI_0049D910@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e850
// @ref _?MAPPACK3@?M@??Write_INI_0049D910@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e854
// @ref _?MAPPACK4@?M@??Write_INI_0049D910@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e858
// @ref _?MAPPACK5@?M@??Write_INI_0049D910@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e85c

void DisplayClass::Write_INI_0049D910(CCINIClass &ini)
{
    char entry[20];

    static char const * const NAME = "Map";
    ini.Clear(NAME);
    ini.Put_TheaterType(NAME, "Theater", (TheaterType)unknown_id_source_a3d290->Theater);
    ini.Put_Rect(NAME, "Size", (INIRect const &)MapSize);
    ini.Put_Rect(NAME, "LocalSize", (INIRect const &)MapLocalSize);

    unknown_id_source_a3d290->Write_Waypoints(ini);

    static char const * const CELLTRIG = "CellTags";
    ini.Clear(CELLTRIG);
    for (int y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            if ((*this)[Cell(x, y)].unknown_3c != 0) {
                TagClass *tp = (*this)[Cell(x, y)].unknown_3c;
                if (tp != 0 && tp->Class != 0) {
                    wsprintfA(entry, "%d", x + (y * 1000));
                    ini.Put_String(CELLTRIG, entry, tp->Class->ID);
                }
            }
        }
    }

    static char const * const MAPPACK1 = "IsoMapPack";
    static char const * const MAPPACK2 = "IsoMapPack2";
    static char const * const MAPPACK3 = "IsoMapPack3";
    static char const * const MAPPACK4 = "IsoMapPack4";
    static char const * const MAPPACK5 = "IsoMapPack5";
    BufferPipe bpipe(unknown_surface_839958->Lock(), unknown_surface_839958->Get_Height() * unknown_surface_839958->Get_Width() * unknown_surface_839958->Bytes_Per_Pixel());
    int len = Map.Unknown_0054DB10(bpipe);
    ini.Clear(MAPPACK1);
    ini.Clear(MAPPACK2);
    ini.Clear(MAPPACK3);
    ini.Clear(MAPPACK4);
    ini.Clear(MAPPACK5);
    if (len > 0) {
        ini.Put_UUBlock(MAPPACK5, unknown_surface_839958->Lock(), len);
        unknown_surface_839958->Unlock();
    }
    unknown_surface_839958->Unlock();
}
