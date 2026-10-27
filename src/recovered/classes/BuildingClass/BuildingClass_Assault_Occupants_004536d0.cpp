// Remove occupants, with an assault animation and attacker action for each when supplied.
#include "shared/building.hpp"
#include "shared/infantry.hpp"
#include "shared/tactical.hpp"
#include "shared/anim.hpp"
#include "shared/weapon_type.hpp"
// @ref ?Unknown_006A2900@Tactical@@=006a2900
// @ref ??0AnimClass@@=00420110
// @ref ?Unknown_006D9610@TechnoClass@@=006d9610
static inline void Occupant_Offset_To_Coord(CoordStruct &coordinate,Point2D const &point)
{
    int y=point.Y;
    int x=point.X;
    coordinate.X=x;
    coordinate.Y=y;
    coordinate.Z=0;
}
void BuildingClass::Unknown_004536D0(InfantryClass *infantry)
{
    if(!infantry) {
        for(int index=unknown_554.Count()-1;index>=0;--index)
            unknown_554[index]->unknown_slot60();
    } else {
        for(int index=unknown_554.Count()-1;index>=0;--index) {
            CoordStruct coordinate;
            Occupant_Offset_To_Coord(coordinate,unknown_tactical_83996c->Unknown_006A2900(Type->MuzzleFlash[index]));
            coordinate=coordinate+unknown_slot42();
            AnimClass *animation=new AnimClass(reinterpret_cast<AnimTypeClass *>(infantry->unknown_slot231(0)->WeaponType->unknown_f4),coordinate,0,1,0x600,0);
            animation->ZAdjust=-200;
            infantry->unknown_slot55(unknown_554[index]);
            unknown_554[index]->unknown_slot60();
        }
    }
    int capacity=unknown_554.Length();
    unknown_554.Clear();
    unknown_554.Resize(capacity,0);
    Unknown_006D9610(unknown_slot105());
}
