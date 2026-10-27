// void DisplayClass::Unknown_0049DCD0(void *buffer) (0x0049DCD0)
// Unpacks what 0x0049DB60 packed: the theater, the map and local sizes, the
// waypoints and the cells' tile, bytes and overlay.
#include "shared/display.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Set_Waypoint_Location@UnknownIDSource@@QAEXHVCell@@@Z=00663400
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490

void DisplayClass::Unknown_0049DCD0(void *buffer)
{
    char *in = (char *)buffer;
    unknown_id_source_a3d290->Theater = *(int *)in;
    in += 4;
    MapSize = *(Rect *)in;
    in += sizeof(Rect);
    MapLocalSize = *(Rect *)in;
    in += sizeof(Rect);
    int waypoints = *(int *)in;
    in += 4;
    for (int count = waypoints; count > 0; count--) {
        int waypoint = *(int *)in;
        in += 4;
        int packed = *(int *)in;
        in += 4;
        Cell cell;
        cell.X = packed % 1000;
        cell.Y = packed / 1000;
        unknown_id_source_a3d290->Set_Waypoint_Location(waypoint, cell);
    }
    in += 4;
    Unknown_0055A550();
    CellClass *cell;
    while ((cell = Unknown_0055A490()) != 0) {
        in += 4;
        cell->IsoTileIndex = *(int *)in;
        in += 4;
        cell->unknown_11a = *in;
        in += 1;
        cell->unknown_11b = *in;
        in += 1;
        cell->unknown_11c = *in;
        in += 1;
        cell->OverlayIndex = *(int *)in;
        in += 4;
        cell->OverlayData = *in;
        in += 1;
        cell->unknown_119 = *in;
        in += 1;
        in += 4;
    }
}
