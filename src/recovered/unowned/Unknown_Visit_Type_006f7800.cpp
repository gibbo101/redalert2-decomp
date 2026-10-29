// void __fastcall Unknown_006F7800(char const *name, UnknownVisit visit, int argument) (0x006F7800)
// Calls visit(techno, argument) for every player-side techno with the type name: from all technos
// (0x00A40C20) when the flag 0x00AC133C is set, else from the selection (0x006F69F0 expanded inline).
// The test is 0x006F7190 called through an UnknownTest, so the caller reads its answer as a bool
// (test al, al) although the function itself returns an int. The list is built, walked and deleted.
// @ref ?unknown_flag_ac133c@@3_NA=00ac133c
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?Unknown_006F7190@@YIHPAVTechnoClass@@PBD@Z=006f7190
// @ref ?Add@?$DynamicVectorClass@PAVTechnoClass@@@@QAE_NABQAVTechnoClass@@@Z=004137b0
// @ref ??0?$VectorClass@PAVTechnoClass@@@@QAE@IPBQAVTechnoClass@@@Z=0040bc10
// @ref ?Count@UnknownSelection@@QAEHXZ=006ac7b0
// @ref ?Get@UnknownSelection@@QAEPAVObjectClass@@H@Z=006ac7c0
// @ref ?unknown_selected_83996c@@3PAUUnknownSelection@@A=0083996c
#include "shared/uicmnds.hpp"

void __fastcall Unknown_006F7800(char const *name, UnknownVisit visit, int argument)
{
    UnknownTest test = (UnknownTest)Unknown_006F7190;
    DynamicVectorClass<TechnoClass *> *list;
    if (unknown_flag_ac133c) {
        list = new DynamicVectorClass<TechnoClass *>(0, 0);
        int count = Technos.Count();
        for (int index = 0; index < count; index++) {
            TechnoClass *techno = Technos[index];
            if (test(techno, (int)name)) {
                list->Add(techno);
            }
        }
    } else {
        list = Unknown_006F69F0(test, (int)name);
    }
    int total = list->Count();
    for (int index = 0; index < total; index++) {
        visit((*list)[index], argument);
    }
    delete list;
}
