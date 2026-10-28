// A Firestorm collision: optional warhead damage and an effect at ground/object height.
#include "shared/building.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
// @ref ??0AnimClass@@QAE@PAVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
bool BuildingClass::unknown_450cb0(ObjectClass *object, bool damage)
{
    if(object && object->Strength > 0) {
        if(damage) {
            object->unknown_slot86(&object->Strength, 0, Rules->unknown_cac, 0, true, 1);
        }
        if(object->unknown_slot108() > 100) {
            new AnimClass(Rules->FirestormAirAnim, CoordStruct(object->Coord), 0, 1, 0x600, -10);
        } else {
            new AnimClass(Rules->FirestormGroundAnim, CoordStruct(Coord), 0, 1, 0x600, -10);
        }
        return true;
    }
    return false;
}
