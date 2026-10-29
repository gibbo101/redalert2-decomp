// bool TActionClass::unknown_meteor_shower_at_waypoint(...) (0x006B2040)
// METLARGE or METSMALL animations (random) at random offsets around waypoint +0x44 (ground height); their count is abs(random) % 3 plus the size table entry Data, the radius 70 leptons per meteor; always true.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/crt_memory.hpp"
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Anim_From_Name@@YIHPBD@Z=00420cd0
// @ref ?unknown_meteor_counts_7f6ad8@@3QBHB=007f6ad8
// @ref _unknown_geometry_j=00abfdf8
// @ref ??_C@_08JLMH@METSMALL?$AA@=007f6c00
// @ref ??_C@_08OAEP@METLARGE?$AA@=007f6c0c
extern int const unknown_meteor_counts_7f6ad8[4];    // 0x007F6AD8 (1, 5, 9, 15: the meteors of each shower size)

// A random offset of up to radius leptons in X and Y (inline; name hypothesis).
inline CoordStruct Random_Offset(int radius)
{
    Random2Class &random = unknown_id_source_a3d290->Random();
    int x = random() % radius;
    int y = random() % radius;
    return CoordStruct(x, y, 0);
}

bool TActionClass::unknown_meteor_shower_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = Cell_Center(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    if ((Map[waypoint].unknown_140 & 0x100) || (Map[waypoint].unknown_140 & 0x400)) {
        coord.Z += unknown_geometry_j;
    }
    int count = abs(unknown_id_source_a3d290->Random()()) % 3 + unknown_meteor_counts_7f6ad8[Data];
    int large = Anim_From_Name("METLARGE");
    int small = Anim_From_Name("METSMALL");
    int radius = count * 70;
    for (int index = 0; index < count; index++) {
        CoordStruct spot = coord + Random_Offset(radius);
        spot.Z = Map.Unknown_0055A280(spot);
        new AnimClass(AnimTypes[(abs(unknown_id_source_a3d290->Random()()) % 2) ? large : small], spot, 0, 1, 0x600, 0);
    }
    return true;
}
