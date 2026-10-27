// EBolt *TechnoClass::unknown_6ca020(AbstractClass *target, WeaponTypeClass *weapon, CoordStruct const &source) (0x006CA020)
// Fires an electric bolt from source to the target: a new EBolt, set up
// from source to the target's coordinate (slot 40 for objects, slot 22
// otherwise); a building raises it by the screen height of the source above
// its own slot 42 coordinate. The weapon's +0x129 flag is copied to the
// bolt's +0x2C.
#include "shared/techno.hpp"
#include "shared/weapon_type.hpp"
#include "shared/tactical.hpp"
#include "shared/ebolt.hpp"
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ??0EBolt@@QAE@XZ=004b17f0
// @ref ?Setup_004B2430@EBolt@@QAEXUCoordStruct@@0H@Z=004b2430
// @ref ?Unknown_006A27A0@Tactical@@QAE?AUPoint2D@@ABUCoordStruct@@@Z=006a27a0

EBolt *TechnoClass::unknown_6ca020(AbstractClass *target, WeaponTypeClass *weapon, CoordStruct const &source)
{
    int depth = 0;
    EBolt *bolt = new EBolt;
    if (bolt == 0) {
        return 0;
    }
    if (Kind_Of() == 6) {
        Point2D from = unknown_tactical_83996c->Unknown_006A27A0(source);
        Point2D to = unknown_tactical_83996c->Unknown_006A27A0(unknown_slot42());
        depth = from.Y - to.Y;
        if (depth > 0) {
            depth = 0;
        }
    }
    CoordStruct coord;
    if (target != 0 && target->unknown_14_bit1) {
        coord = ((ObjectClass *)target)->unknown_slot40();
    } else {
        coord = target->unknown_slot22();
    }
    if (weapon != 0) {
        bolt->unknown_2c = weapon->unknown_129;
    }
    bolt->Setup_004B2430(source, coord, depth);
    return bolt;
}
