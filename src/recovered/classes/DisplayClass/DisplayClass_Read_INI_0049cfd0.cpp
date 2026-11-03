// void DisplayClass::Read_INI_0049CFD0(CCINIClass &ini) (0x0049CFD0, slot 32)
// Reads the map's sections of a scenario INI (TibSun DisplayClass::Read_INI): [Map] Size,
// Level, Fill and Theater, the theater's type data, the waypoints and home view, [CellTags],
// the IsoMapPack..5 blocks through a 640x400 staging surface, then the tiles and LocalSize.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/ccini_class.hpp"
#include "shared/id_source.hpp"
#include "shared/tag.hpp"
#include "shared/tag_type.hpp"
#include "shared/surface.hpp"
#include "shared/buffer_straw.hpp"
#include "shared/tactical.hpp"
#include "shared/session_state.hpp"
#include "shared/ms_engine.hpp"
#include "shared/tileset_index.hpp"
#include "shared/anim_type.hpp"
#include "shared/building_type_class.hpp"
#include "shared/overlay_type.hpp"
#include "shared/smudge_type.hpp"
#include "shared/terrain_type.hpp"
#include "shared/veinhole.hpp"
#include "shared/lobby.hpp"
#include "shared/unknown_globals.hpp"

void __fastcall Unknown_00529870(int theater, bool arg);
void Unknown_0052B650();
void __fastcall Unknown_0052B2E0(bool arg1, bool arg2);
extern "C" int __cdecl atoi(char const *string);

void DisplayClass::Read_INI_0049CFD0(CCINIClass &ini)
{
    char const * const name = "Map";

    INIRect defsize;
    defsize.X = 1;
    defsize.Y = 1;
    defsize.Width = 50;
    defsize.Height = 50;
    INIRect rect = ini.Get_Rect(name, "Size", defsize);

    unknown_slot24();

    unknown_slot28((Rect const *)&rect, true, false, true);

    int cell_height = ini.Get_Int(name, "Level", 0);

    char fill[32];
    int ittype = unknown_tileset_a52f00;
    ini.Get_String(name, "Fill", "Clear", fill, sizeof(fill));
    if (Compare_Narrow_00781f20(fill, "Water") == 0) {
        ittype = unknown_tileset_a52580;
    }

    Unknown_0055A550();
    CellClass *cptr = Unknown_0055A490();
    while (cptr != 0) {
        cptr->IsoTileIndex = ittype;
        cptr->unknown_11a = 0;
        cptr->unknown_11b += cell_height;
        cptr = Unknown_0055A490();
    }

    unknown_id_source_a3d290->Theater = ini.Get_TheaterType(name, "Theater", (TheaterType)0);

    Init(unknown_id_source_a3d290->Theater);

    unknown_session_a3d298.Loading_Progress_00672160(63);
    unknown_481fb0();

    long uniqueid = unknown_id_source_a3d290->UniqueID;
    TerrainTypeClass::Init(unknown_id_source_a3d290->Theater);
    if (unknown_id_source_a3d290->Theater != unknown_loaded_theater_7d88dc) {
        Unknown_00529870(unknown_id_source_a3d290->Theater, true);
    } else {
        Unknown_0052B650();
    }
    unknown_id_source_a3d290->UniqueID = uniqueid + 10000;
    OverlayTypeClass::Init(unknown_id_source_a3d290->Theater);
    BuildingTypeClass::Init(unknown_id_source_a3d290->Theater);
    AnimTypeClass::Init(unknown_id_source_a3d290->Theater);
    SmudgeTypeClass::Init(unknown_id_source_a3d290->Theater);
    VeinholeMonsterClass::Load_Shape(unknown_id_source_a3d290->Theater);

    unknown_session_a3d298.Loading_Progress_00672160(65);
    unknown_481fb0();

    unknown_id_source_a3d290->Read_Waypoints(ini);

    if (!unknown_id_source_a3d290->Unknown_00663240(unknown_id_source_a3d290->HomeCell)) {
        unknown_id_source_a3d290->Set_Waypoint_Location(unknown_id_source_a3d290->HomeCell,
            Cell((MapSize.Width + MapSize.Height) / 2, (MapSize.Width + MapSize.Height) / 2));
    }

    Cell homecell = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_id_source_a3d290->Variables[0].Value ? unknown_id_source_a3d290->AltHomeCell : unknown_id_source_a3d290->HomeCell);
    unknown_id_source_a3d290->Views[0] = unknown_id_source_a3d290->Views[1] = unknown_id_source_a3d290->Views[2] = unknown_id_source_a3d290->Views[3] = homecell;
    CoordStruct homecoord;
    homecoord.X = homecell.X * 256 + 128;
    homecoord.Y = homecell.Y * 256 + 128;
    homecoord.Z = 0;
    unknown_tactical_83996c->Unknown_006A66B0(homecoord);

    char const * const celltags = "CellTags";
    int len = ini.Entry_Count(celltags);
    for (int index = 0; index < len; index++) {
        char const *cellentry = ini.Get_Entry(celltags, index);
        TagTypeClass *tp;
        Cell cell;

        char buffer[128];
        if (ini.Get_String(celltags, cellentry, "", buffer, sizeof(buffer))) {
            tp = TagTypeClass::Find_Or_Make(buffer);
        } else {
            tp = 0;
        }

        int val = atoi(cellentry);

        if (unknown_ini_format_a40d24 >= 4) {
            cell = Cell(val % 1000, val / 1000);
        } else {
            cell = Cell(val % 128, val / 128);
        }

        if (tp != 0 && !(*this)[cell].unknown_3c) {
            TagClass *tt = TagClass::Find_Or_Make(tp);
            if (tt) {
                tt->Set_Cell(cell);
                (*this)[cell].Set_unknown_3c(tt);
                unknown_1158.Add(cell);
            }
        }
    }
    unknown_session_a3d298.Loading_Progress_00672160(67);
    unknown_481fb0();

    BSurface staging_buffer(640, 400, 2);

    int size = staging_buffer.Get_Width() * staging_buffer.Get_Height() * staging_buffer.Bytes_Per_Pixel();

    static char const * const ISOMAPPACK1 = "IsoMapPack";
    len = ini.Get_UUBlock(ISOMAPPACK1, staging_buffer.Lock(), size);
    if (len > 0) {
        BufferStraw bstraw(staging_buffer.Lock(), len);
        Map.Unknown_0054DCC0(bstraw);
        staging_buffer.Unlock();
    }
    staging_buffer.Unlock();

    static char const * const ISOMAPPACK2 = "IsoMapPack2";
    len = ini.Get_UUBlock(ISOMAPPACK2, staging_buffer.Lock(), size);
    if (len > 0) {
        BufferStraw bstraw(staging_buffer.Lock(), len);
        Map.Unknown_0054DEA0(bstraw);
        staging_buffer.Unlock();
    }
    staging_buffer.Unlock();

    static char const * const ISOMAPPACK3 = "IsoMapPack3";
    len = ini.Get_UUBlock(ISOMAPPACK3, staging_buffer.Lock(), size);
    if (len > 0) {
        BufferStraw bstraw(staging_buffer.Lock(), len);
        Map.Unknown_0054DFC0(bstraw);
        staging_buffer.Unlock();
    }
    staging_buffer.Unlock();

    static char const * const ISOMAPPACK4 = "IsoMapPack4";
    len = ini.Get_UUBlock(ISOMAPPACK4, staging_buffer.Lock(), size);
    if (len > 0) {
        BufferStraw bstraw(staging_buffer.Lock(), len);
        Map.Unknown_0054E0C0(bstraw);
        staging_buffer.Unlock();
    }
    staging_buffer.Unlock();

    static char const * const ISOMAPPACK5 = "IsoMapPack5";
    len = ini.Get_UUBlock(ISOMAPPACK5, staging_buffer.Lock(), size);
    if (len > 0) {
        BufferStraw bstraw(staging_buffer.Lock(), len);
        Map.Unknown_0054E1E0(bstraw);
        staging_buffer.Unlock();
    }
    staging_buffer.Unlock();

    unknown_session_a3d298.Loading_Progress_00672160(68);
    unknown_481fb0();

    Unknown_0052B2E0(unknown_flag_a40d13 || unknown_flag_a40d05, unknown_id_source_a3d290->unknown_223b);

    unknown_session_a3d298.Loading_Progress_00672160(69);
    unknown_481fb0();

    (INIRect &)MapLocalSize = ini.Get_Rect(name, "LocalSize", (INIRect const &)MapSize);
    Map.Unknown_00630840(MapLocalSize);
    Map.Unknown_0056A8A0();

    unknown_loaded_theater_7d88dc = unknown_id_source_a3d290->Theater;
}
// @ref ?Unknown_00630840@RadarClass@@QAEXABVRect@@@Z=00630840
// @ref ??_C@_04BHHI@Fill?$AA@=007d5e20
// @ref ??_C@_05BHDE@Clear?$AA@=007d3a6c
// @ref ??_C@_05CGKI@Water?$AA@=007d1ab8
// @ref _?ISOMAPPACK1@?CB@??Read_INI_0049CFD0@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e830
// @ref _?ISOMAPPACK2@?CE@??Read_INI_0049CFD0@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e834
// @ref _?ISOMAPPACK3@?CH@??Read_INI_0049CFD0@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e838
// @ref _?ISOMAPPACK4@?CK@??Read_INI_0049CFD0@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e83c
// @ref _?ISOMAPPACK5@?CN@??Read_INI_0049CFD0@DisplayClass@@QAEXAAVCCINIClass@@@Z@4QBDB=0079e840
// @ref ??0Surface@@QAE@HH@Z=0049ed90
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1Straw@@UAE@XZ=0069b010
// @ref ??_7BSurface@@6B@=0079aef8
// @ref ??_7XSurface@@6B@=0079af8c
// @ref ??_7BufferStraw@@6B@=0079e9e8
// @ref ??_7Straw@@6B@=0079e9f8
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_03DIFO@Map?$AA@=007d5c9c
// @ref ??_C@_04BBDK@Size?$AA@=007d5e28
// @ref ??_C@_05PGGH@Level?$AA@=007d1374
// @ref ??_C@_07OHHF@Theater?$AA@=007cf004
// @ref ??_C@_08CFMK@CellTags?$AA@=007d5c90
// @ref ??_C@_09OOBE@LocalSize?$AA@=007d5e14
// @ref ??_C@_0L@IADI@IsoMapPack?$AA@=007d5cd0
// @ref ??_C@_0M@LMDO@IsoMapPack2?$AA@=007d5cc4
// @ref ??_C@_0M@BGKJ@IsoMapPack3?$AA@=007d5cb8
// @ref ??_C@_0M@EDEM@IsoMapPack4?$AA@=007d5cac
// @ref ??_C@_0M@OJNL@IsoMapPack5?$AA@=007d5ca0
