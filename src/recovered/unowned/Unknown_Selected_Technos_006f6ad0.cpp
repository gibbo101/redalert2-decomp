// DynamicVectorClass<TechnoClass *> *Unknown_006F6AD0() (0x006F6AD0)
// The selected objects (0x00A40C60; flag +0x14 bit 0) in a new list.
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
#include "shared/uicmnds.hpp"

DynamicVectorClass<TechnoClass *> *Unknown_006F6AD0()
{
    DynamicVectorClass<TechnoClass *> *list = new DynamicVectorClass<TechnoClass *>(0, 0);
    int count = unknown_objects_a40c60.Count();
    for (int index = 0; index < count; index++) {
        ObjectClass *object = unknown_objects_a40c60[index];
        bool flag;
        if (object != 0) {
            flag = object->AbstractFlags.IsTechno;
        }
        if (object != 0 && flag) {
            list->Add((TechnoClass *)object);
        }
    }
    return list;
}
