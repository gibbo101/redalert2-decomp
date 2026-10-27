// int AnimClass::unknown_slot116() (0x00421580)
// One bounce step (UnknownBounce 0x004370E0): a meteor speeds up; on a
// bounce (1) the type's BounceAnim is spawned and every object in the cell
// within DamageRadius (|dx| + |dy|) takes the type's Damage with its
// Warhead, scaled by distance; at rest (2) the animation ends (slot 60).
// The position follows the bounce state; returns the step's result.
#include "shared/anim.hpp"

#include "shared/crt_memory.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_004370E0@UnknownBounce@@QAEHXZ=004370e0
// @ref ?Unknown_00436F80@UnknownBounce@@QBE?AUCoordStruct@@XZ=00436f80
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
// @ref ??2@YAPAXI@Z=00782017
// @ref __ftol=0077f110
// @ref ??0AnimClass@@QAE@PAVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110

int AnimClass::unknown_slot116()
{
    UnknownBounce &bounce = unknown_108;
    int state = bounce.Unknown_004370E0();
    if (Class->IsMeteor) {
        bounce.unknown_2c += bounce.unknown_08;
    }
    switch (state) {
    case 1:
        {
            if (Class->BounceAnim) {
                new AnimClass(Class->BounceAnim, Center_Coord(), 0, 1, 0x600, 0);
            }
            UnknownAnimCell *cell = (UnknownAnimCell *)&Map[unknown_108.Unknown_00436F80()];
            for (ObjectClass *object = cell->unknown_e4; object != 0; object = object->unknown_30) {
                CoordStruct delta = unknown_108.Unknown_00436F80() - object->Center_Coord();
                int distance = abs(delta.X) + abs(delta.Y);
                if (distance <= Class->DamageRadius) {
                    int damage = Class->Damage;
                    object->unknown_slot86(&damage, Unknown_006A2970(distance), (WarheadTypeClass *)Class->Warhead, 0, 0, 0);
                }
            }
        }
        break;
    case 2:
        unknown_slot60();
        break;
    }
    unknown_slot103(unknown_108.Unknown_00436F80());
    return state;
}
