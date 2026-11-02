// bool Unknown_006F6520() (0x006F6520)
// True when every listed object (selected objects) answers slot 275.
#include "shared/uicmnds.hpp"
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60

bool Unknown_006F6520()
{
    int count = unknown_objects_a40c60.Count();
    for (int index = 0; index < count; index++) {
        ObjectClass *object = unknown_objects_a40c60[index];
        bool flag;
        if (object != 0) {
            flag = object->AbstractFlags.IsTechno;
        }
        if (object != 0 && flag) {
            if (!((TechnoClass *)object)->unknown_slot275()) {
                return false;
            }
        }
    }
    return true;
}
