// Create damage-fire animations at the structure's art offsets.
#include "shared/building.hpp"
#include "shared/tactical.hpp"
#include "shared/anim.hpp"
#include "shared/id_source.hpp"
extern Point2D const Damage_Fire_Offset_End_0084ed30;
// @ref ?Damage_Fire_Offset_End_0084ed30@@=0084ed30
// @ref ?Unknown_006A2900@Tactical@@=006a2900
// @ref ??0AnimClass@@=00420110
// @ref ?Foundation_Height@BuildingTypeClass@@=00458940
// @ref ?Width@BuildingTypeClass@@=00458930

inline CoordStruct Projected_Coord_0043bbd0(Point2D const &point);
inline void Accumulate_Coord_004395f0(CoordStruct &destination, CoordStruct const &offset)
{
    destination.X += offset.X;
    destination.Y += offset.Y;
    destination.Z += offset.Z;
}
void BuildingClass::Create_Damage_Fires_004395f0()
{
    int type_count = Rules->DamageFireTypes.Count();
    if (type_count != 0) {
        int type_index = unknown_id_source_a3d290->Random()(0, type_count - 1);
        for (int index = 0; index < 8; ++index) {
            if (Type->DamageFireOffset[index] == Damage_Fire_Offset_End_0084ed30) return;
            if (unknown_49c[index] != 0) return;
            CoordStruct coordinate = Projected_Coord_0043bbd0(unknown_tactical_83996c->Unknown_006A2900(Type->DamageFireOffset[index]));
            Accumulate_Coord_004395f0(coordinate, unknown_slot42());
            AnimClass *fire = new AnimClass(Rules->DamageFireTypes[type_index], coordinate, 0, 1, 0x600, 0);
            if (fire) {
                unknown_49c[index] = fire;
                fire->ZAdjust = ((Type->DamageFireOffset[index].Y - (Type->Width() + Type->Foundation_Height(false)) * 15) * 3 >> 1) - 10;
                if (fire->ZAdjust > 0) fire->ZAdjust = 0;
                int frames = fire->Class->End;
                if (frames > 0) fire->Stage = unknown_id_source_a3d290->Random()(0, frames - 1);
                ++type_index;
                if (type_index >= type_count) type_index = 0;
            }
        }
    }
}
