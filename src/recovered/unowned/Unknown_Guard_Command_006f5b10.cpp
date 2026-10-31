// void __fastcall Unknown_006F5B10() (0x006F5B10)
// The guard command (hypothesis): in planning mode it is refused; otherwise every listed selected
// object that passes slots 39 and 38 is asked slot 200 (0x0B, its slot 107 answer); when all agree the
// rules' GuardSound (+0x644) plays.
#include "shared/uicmnds.hpp"
#include "shared/planning.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
bool Planning_Mode_Active_614840();
// @ref ?Planning_Mode_Active_614840@@YA_NXZ=00614840

void __fastcall Unknown_006F5B10()
{
    if (Planning_Mode_Active_614840()) {
        Planning_Refuse_No_Guard_Area();
        return;
    }
    if (unknown_objects_a40c60.Count() > 0) {
        char agreed = 1;
        int count = unknown_objects_a40c60.Count();
        for (int index = 0; index < count; index++) {
            ObjectClass *object = unknown_objects_a40c60[index];
            if (object != 0 && object->unknown_14_bit0 && object->unknown_slot39() && object->unknown_slot38()) {
                agreed = ((TechnoClass *)object)->unknown_slot200(0x0B, (AbstractClass *)object->unknown_slot107(), 0, 0);
                if (!agreed) {
                    return;
                }
            }
        }
        if (agreed) {
            Voc_Play(Rules->unknown_644, 1.0f, 0x2000, 0);
        }
    }
}
