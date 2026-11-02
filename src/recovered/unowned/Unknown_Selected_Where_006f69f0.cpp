// DynamicVectorClass<TechnoClass *> *__fastcall Unknown_006F69F0(UnknownTest test, int argument) (0x006F69F0)
// The objects of the selection (0x0083996C; flag +0x14 bit 0) for which test(object, argument)
// holds, in a new list. 0x006F7800 expands it inline (with 0x006F7190 as the test).
// @ref ?Count@UnknownSelection@@QAEHXZ=006ac7b0
// @ref ?Get@UnknownSelection@@QAEPAVObjectClass@@H@Z=006ac7c0
// @ref ?unknown_selected_83996c@@3PAUUnknownSelection@@A=0083996c
#include "shared/uicmnds.hpp"

DynamicVectorClass<TechnoClass *> *__fastcall Unknown_006F69F0(UnknownTest test, int argument)
{
    DynamicVectorClass<TechnoClass *> *list = new DynamicVectorClass<TechnoClass *>(0, 0);
    int count = unknown_selected_83996c->Count();
    for (int index = 0; index < count; index++) {
        ObjectClass *object = unknown_selected_83996c->Get(index);
        bool flag;
        if (object != 0) {
            flag = object->AbstractFlags.IsTechno;
        }
        if (object != 0 && flag) {
            TechnoClass *techno = (TechnoClass *)object;
            if (test(techno, argument)) {
                list->Add(techno);
            }
        }
    }
    return list;
}
