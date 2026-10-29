// @ref ?unknown_list_ac1344@@3PAUUnknownPointerList@@A=00ac1344
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Count@UnknownSelection@@QAEHXZ=006ac7b0
// @ref ?Get@UnknownSelection@@QAEPAVObjectClass@@H@Z=006ac7c0
// @ref ?unknown_selected_83996c@@3PAUUnknownSelection@@A=0083996c
// @ref ?Add@?$DynamicVectorClass@PAVTechnoClass@@@@QAE_NABQAVTechnoClass@@@Z=004137b0
// @ref ??0?$VectorClass@PAVTechnoClass@@@@QAE@IPBQAVTechnoClass@@@Z=0040bc10
#include "shared/uicmnds.hpp"

extern UnknownPointerList *unknown_list_ac1344;
int __fastcall Unknown_006F7DF0(TechnoClass *techno, int argument);
DynamicVectorClass<TechnoClass *> *Unknown_006F6AD0();
DynamicVectorClass<TechnoClass *> *__fastcall Unknown_006F69F0(UnknownTest test, int argument);

void Unknown_006F79C0()
{
    if (unknown_list_ac1344 != 0) {
        delete (DynamicVectorClass<TechnoClass *> *)unknown_list_ac1344;
        unknown_list_ac1344 = 0;
    }
    unknown_list_ac1344 = (UnknownPointerList *)Unknown_006F6AD0();
    if (unknown_list_ac1344->Count == 0) {
        delete (DynamicVectorClass<TechnoClass *> *)unknown_list_ac1344;
        unknown_list_ac1344 = 0;
        unknown_list_ac1344 = (UnknownPointerList *)Unknown_006F69F0((UnknownTest)Unknown_006F7DF0, 0);
    }
}
