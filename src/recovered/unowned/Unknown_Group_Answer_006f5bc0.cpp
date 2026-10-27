// void Unknown_006F5BC0() (0x006F5BC0)
// Answers a group command (hypothesis): when every listed object that passes slot 39 or 38 answers slot 199 (6), the rules' +0x640 sound plays.
#include "shared/uicmnds.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Unknown_00713DB0@@YIHHMHH@Z=00713db0


void Unknown_006F5BC0()
{
    if (unknown_objects_a40c60.Count() > 0) {
        char agreed = 1;
        int count = unknown_objects_a40c60.Count();
        for (int index = 0; index < count; index++) {
            ObjectClass *object = unknown_objects_a40c60[index];
            if (object != 0 && object->unknown_14_bit0 && (object->unknown_slot39() || object->unknown_slot38())) {
                agreed = (char)((TechnoClass *)object)->unknown_slot199(6);
                if (!agreed) {
                    break;
                }
            }
        }
        if (agreed) {
            Unknown_00713DB0(Rules->unknown_640, 1.0f, 0x2000, 0);
        }
    }
}
