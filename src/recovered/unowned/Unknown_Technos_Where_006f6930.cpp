// DynamicVectorClass<TechnoClass *> *__fastcall Unknown_006F6930(UnknownTest test, int argument) (0x006F6930)
// The technos (0x00A40C20) for which test(techno, argument) holds, in a new list.
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
#include "shared/uicmnds.hpp"

DynamicVectorClass<TechnoClass *> *__fastcall Unknown_006F6930(UnknownTest test, int argument)
{
    DynamicVectorClass<TechnoClass *> *list = new DynamicVectorClass<TechnoClass *>(0, 0);
    int count = Technos.Count();
    for (int index = 0; index < count; index++) {
        TechnoClass *techno = Technos[index];
        if (test(techno, argument)) {
            list->Add(techno);
        }
    }
    return list;
}
