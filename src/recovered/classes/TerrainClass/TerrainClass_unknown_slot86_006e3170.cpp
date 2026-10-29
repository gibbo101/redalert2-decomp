// int TerrainClass::unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6) (0x006E3170, slot 86)
// Takes damage (hypothesis: Take_Damage). Only wood-affecting warheads hurt
// terrain whose type is not immune (+0x203). When the object is destroyed
// (result 4) a tiberium spawner explodes (the C4 warhead's animation and
// damage around it), a burning one (+0xB4) stops its attached animations and
// anything else starts crumbling; then its area is redrawn and it leaves the
// map (slots 54 and 60).
#include "shared/terrain.hpp"
#include "shared/tactical.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/warhead_type.hpp"
// @ref ?unknown_slot86@ObjectClass@@UAEHPAHHPAVWarheadTypeClass@@PAVTechnoClass@@_NH@Z=005d3d20
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Select_Damage_Anim@@YIPAVAnimTypeClass@@HPAVWarheadTypeClass@@HPAUCoordStruct@@@Z=0047f4d0
// @ref ?Unknown_0047FCC0@@YGHUCoordStruct@@@Z=0047fcc0

// The object's coordinate as a value (local helper; each use is its own copy).
static inline CoordStruct Get_Coord(ObjectClass const *object)
{
    return object->Coord;
}

// The land type of the cell at a coordinate (local helper).
static inline int Land_Type_At(CoordStruct coord)
{
    return Map[coord].unknown_ec;
}

int TerrainClass::unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6)
{
    int result = 0;
    if (warhead == 0) {
        return 0;
    }
    if (warhead->Wood && !Class->unknown_203) {
        result = ObjectClass::unknown_slot86(damage, distance, warhead, source, forced, arg6);
        if (result == 5) {
            return result;
        }
        if (result == 4) {
            if (Class->SpawnsTiberium) {
                new AnimClass(Select_Damage_Anim(100, Rules->unknown_c74, Land_Type_At(Get_Coord(this)), &Get_Coord(this)), Get_Coord(this), 0, 1, 0x2600, Unknown_0047FCC0(Get_Coord(this)));
                Unknown_0047E2C0(Get_Coord(this), 100, 0, Rules->unknown_c74, 1);
                unknown_slot104().unknown_47e2b0();
            } else if (unknown_b4) {
                Unknown_00420D30(this);
            } else {
                Start_Crumbling();
            }
            unknown_tactical_83996c->Unknown_006A3020(unknown_slot73(), 0);
            unknown_slot54(true);
            unknown_slot60();
        }
    }
    return result;
}
