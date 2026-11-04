// CellClass::CellClass() (0x00470F10): an empty cell at the zero cell: no
// tile (0xFFFF), overlay or smudge (-1), the per-house counters and +0xAC
// cleared (two element loops: VC6 turns each into lea edi / mov ecx / rep stosd,
// a memset call schedules mov ecx first), levels and flags reset (the +0x12C
// and +0x140 bitfields clear in the member-init order); then registers its ID.
#include "shared/cell.hpp"

CellClass::CellClass() :
    MapCoords(unknown_geometry_k),
    FoggedObjects(0),
    unknown_2c(0),
    unknown_30(0),
    unknown_34(0),
    IsoTileIndex(0xFFFF),
    unknown_3c(0),
    unknown_40(0),
    OverlayIndex(-1),
    SmudgeIndex(-1),
    unknown_4c(0),
    unknown_50(-1),
    unknown_54(-1),
    unknown_58(-1),
    unknown_5c(-1),
    unknown_60(-1),
    unknown_64(-1),
    unknown_68(Rect(0, 0, 0, 0)),
    unknown_78(0),
    unknown_dc(0),
    unknown_e0(0),
    OccupierPtr(0),
    AltOccupierPtr(0),
    unknown_ec(0),
    unknown_f0(0),
    unknown_f8(0),
    unknown_fc(0),
    unknown_100(0),
    unknown_104(0x10000),
    unknown_108(0),
    unknown_10a(1000),
    unknown_10c(1000),
    unknown_10e(1000),
    unknown_110(1000),
    unknown_112(1000),
    unknown_114(1000),
    unknown_116(-1),
    unknown_118(0xFF),
    unknown_119(0),
    unknown_11a(0),
    unknown_11b(0),
    unknown_11c(0),
    unknown_11d(0),
    OverlayData(0),
    SmudgeData(0),
    unknown_120(-2),
    unknown_121(-2),
    unknown_122(0),
    Flags_12c(0),
    unknown_130(1),
    unknown_134(0),
    unknown_138(false),
    unknown_13c(0),
    Flags_140(0)
{
    int index;
    for (index = 0; index < 24; index++) {
        unknown_7c[index] = 0;
    }
    for (index = 0; index < 12; index++) {
        unknown_ac[index] = 0;
    }
    Create_ID();
    unknown_124 = 0;
    unknown_128 = 0;
}

