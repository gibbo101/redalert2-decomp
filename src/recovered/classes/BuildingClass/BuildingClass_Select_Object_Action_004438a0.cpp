// Building object-selection action, 0x004438A0.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/keyboard.hpp"
#include "shared/bullet_type.hpp"
// @ref ?unknown_slot28@TechnoClass@@=006cc5d0
// @ref ?Down@WWKeyboardClass@@=00532890
// @ref ?WWKeyboard@@=00832468
// @ref ?unknown_key_a40ba4@@=00a40ba4
// @ref ?unknown_key_a40ba8@@=00a40ba8
// @ref ?unknown_player_a35db4@@=00a35db4
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
inline bool Building_Key_Down(int key);
int BuildingClass::unknown_slot28(ObjectClass *object, bool alternate)
{
    if (Type->InvisibleInGame) return 0;
    if (object->Kind_Of() == 6 && ((BuildingClass *)object)->Type->InvisibleInGame) return 0;
    int action = TechnoClass::unknown_slot28(object, alternate);
    if (action == 8) return 8;
    if (action == 4) {
        BuildingTypeClass *type = Type;
        int factory;
        if (type->GapGenerator && unknown_player_a35db4 == House) {
            if (!unknown_1fc && House->Power_Output() - House->Power_Drain() <= type->ExtraPowerDrain_c74) goto no_action;
        } else if (unknown_554.Count() <= 0) {
            if (type->Factory == 0) { action = 0; goto result_action; }
            goto primary_action;
        }
        factory = type->Factory;
        action = 4;
        if (factory == 0) goto result_action;
primary_action:
        if (unknown_32b) action = 0;
        goto result_action;
    }
    if (action == 5) {
        if (!unknown_slot231(0)->WeaponType) goto object_action;
        if (!unknown_slot231(0)->WeaponType->Projectile->AG || Type->EMPulseCannon) action = 0;
        if (Mission == 19) {
no_action:
            action = 0; goto result_action; }
    }
    if (action == 1 || action == 2) {
        if (!unknown_slot39()) { action = 7; goto result_action; }
        int factory = Type->Factory;
        if (factory == 16 || factory == 40 || factory == 3) {
            if (!Building_Key_Down(unknown_key_a40ba4) && !Building_Key_Down(unknown_key_a40ba8)) { action = 7; goto result_action; }
            Cell cell = object->Center_Coord();
            if (Type->Factory != 3) {
                CoordStruct position;
                position.X = cell.X * 256 + 128;
                position.Y = cell.Y * 256 + 128;
                position.Z = 0;
                if (!unknown_slot171(position)) action = 2;
                if (!(Map[cell].unknown_140 & 0x100) && Map[cell].unknown_4c) { action = 2; goto result_action; }
            }
        }
    }
    if (action != 5) goto result_action;
object_action:
    if (object->Class_Of()->unknown_203) action = 2;
result_action:
    return action;
}
