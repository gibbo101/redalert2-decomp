// bool Unknown_Can_Force_Order_006F6670() -- 0x006F6670
// Purpose: true when the group flag at 0x00AC1330 is set; otherwise needs a
// force-fire key and a force-move key held, and every listed object that is
// flagged to answer slot 275 (hypothesis: the force-move-and-fire order is
// possible for the whole selection).
// @ref ?unknown_flag_ac1330@@3_NA=00ac1330
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Down@WWKeyboardClass@@QAE_NG@Z=00532890
// @ref ?KeyForceFire1@@3HA=00a40bac
// @ref ?KeyForceFire2@@3HA=00a40bb0
// @ref ?KeyForceMove1@@3HA=00a40bb4
// @ref ?KeyForceMove2@@3HA=00a40bb8
#include "shared/uicmnds.hpp"
#include "shared/keyboard.hpp"

// A key binding is down (the bindings are ints; WWKeyboardClass takes 16-bit keys).
inline bool Key_Down(int key) { return WWKeyboard->Down(key); }

bool Unknown_Can_Force_Order_006F6670()
{
    if (unknown_flag_ac1330) {
        return true;
    }
    bool force_fire = Key_Down(KeyForceFire1) || Key_Down(KeyForceFire2);
    bool force_move = Key_Down(KeyForceMove1) || Key_Down(KeyForceMove2);
    if (!force_fire || !force_move) {
        return false;
    }
    int count = unknown_objects_a40c60.Count();
    for (int index = 0; index < count; index++) {
        ObjectClass *object = unknown_objects_a40c60[index];
        bool flag;
        if (object != 0) {
            flag = object->unknown_14_bit0;
        }
        if (object != 0 && flag) {
            if (!((TechnoClass *)object)->unknown_slot275()) {
                return false;
            }
        }
    }
    return true;
}
