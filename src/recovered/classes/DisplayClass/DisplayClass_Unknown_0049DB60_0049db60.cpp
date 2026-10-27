// int DisplayClass::Unknown_0049DB60(void *buffer, int arg2) (0x0049DB60)
// Packs the map's description into a buffer: the theater, the map and local
// sizes, the waypoints that are set (index and X + Y * 1000), then one
// 21-byte record per cell (coordinates, tile, three bytes, overlay index and
// data, one more byte and the tag's type). Returns the bytes written.
#include "shared/display.hpp"
#include "shared/id_source.hpp"
#include "shared/tag.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Unknown_00663240@UnknownIDSource@@QBE_NH@Z=00663240
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490

int DisplayClass::Unknown_0049DB60(void *buffer, int arg2)
{
    char *out = (char *)buffer;
    *(int *)out = unknown_id_source_a3d290->Theater;
    out += 4;
    *(Rect *)out = MapSize;
    out += sizeof(Rect);
    *(Rect *)out = MapLocalSize;
    out += sizeof(Rect);
    int *waypoint_count = (int *)out;
    out += 4;
    int waypoints = 0;
    for (int waypoint = 0; waypoint < 101; waypoint++) {
        if (unknown_id_source_a3d290->Unknown_00663240(waypoint)) {
            *(int *)out = waypoint;
            out += 4;
            *(int *)out = unknown_id_source_a3d290->Get_Waypoint_Location(waypoint).Y * 1000 +
                          unknown_id_source_a3d290->Get_Waypoint_Location(waypoint).X;
            out += 4;
            waypoints++;
        }
    }
    *waypoint_count = waypoints;
    int *cell_count = (int *)out;
    out += 4;
    int cells = 0;
    Unknown_0055A550();
    CellClass *cell;
    while ((cell = Unknown_0055A490()) != 0) {
        *(Cell *)out = cell->MapCoords;
        out += 4;
        *(int *)out = cell->IsoTileIndex;
        out += 4;
        *out = cell->unknown_11a;
        out += 1;
        *out = cell->unknown_11b;
        out += 1;
        *out = cell->unknown_11c;
        out += 1;
        *(int *)out = cell->OverlayIndex;
        out += 4;
        *out = cell->OverlayData;
        out += 1;
        *out = cell->unknown_119;
        out += 1;
        int tag_class = 0;
        if (cell->unknown_3c != 0 && cell->unknown_3c->Class != 0) {
            tag_class = (int)cell->unknown_3c->Class;
        }
        *(int *)out = tag_class;
        out += 4;
        cells++;
    }
    *cell_count = cells;
    return out - (char *)buffer;
}
