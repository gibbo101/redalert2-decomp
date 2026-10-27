// CCINIClass::Get_Techno_List (0x0046B930).
// Layout and behaviour: shared/ccini_class.hpp.
// @ref ??0?$VectorClass@PAVTechnoTypeClass@@@@QAE@ABV0@@Z=0046d380
// @ref ??0?$VectorClass@PAVTechnoTypeClass@@@@QAE@IPBQAVTechnoTypeClass@@@Z=0046dbd0
// @ref ??4?$VectorClass@PAVTechnoTypeClass@@@@QAEAAV0@ABV0@@Z=0046dc20
// @ref ??8?$VectorClass@PAVTechnoTypeClass@@@@UBE_NABV0@@Z=0046d400
// @ref ??_7?$TypeList@PAVTechnoTypeClass@@@@6B@=0079da34
// @ref ??_7?$VectorClass@PAVTechnoTypeClass@@@@6B@=0079da14
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_E?$TypeList@PAVTechnoTypeClass@@@@UAEPAXI@Z=0046ceb0
// @ref ??_E?$VectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=0046dac0
// @ref ??_G?$TypeList@PAVTechnoTypeClass@@@@UAEPAXI@Z=0046ceb0
// @ref ??_G?$VectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=0046dac0
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEXXZ=0046cce0
// @ref ?Clear@?$VectorClass@PAVTechnoTypeClass@@@@UAEXXZ=0046d4f0
// @ref ?Fetch@?$VectorClass@PAVTechnoTypeClass@@@@UBEPAVTechnoTypeClass@@H@Z=0046cd30
// @ref ?ID@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEHABQAVTechnoTypeClass@@@Z=0046d630
// @ref ?ID@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEHPBQAVTechnoTypeClass@@@Z=0046cd10
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHABQAVTechnoTypeClass@@@Z=0046d520
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHPBQAVTechnoTypeClass@@@Z=0046d560
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAE_NHPBQAVTechnoTypeClass@@@Z=0046d580
// @ref ?Resize@?$VectorClass@PAVTechnoTypeClass@@@@UAE_NHPBQAVTechnoTypeClass@@@Z=0046d440
// @ref ?TechnoTypes@@3V?$DynamicVectorClass@PAVTechnoTypeClass@@@@A=00a40ab8
#include "shared/ccini_extra.hpp"

TypeList<TechnoTypeClass *> CCINIClass::Get_Techno_List(char const *section, char const *entry,
                                                        TypeList<TechnoTypeClass *> defvalue)
{
    char buffer[512];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        TypeList<TechnoTypeClass *> list;
        for (char *token = strtok(buffer, ","); token != 0 && *token != '\0'; token = strtok(0, ",")) {
            for (int index = 0; index < TechnoTypes.Count(); index++) {
                if (_stricmp(token, TechnoTypes[index]->ID) == 0) {
                    list.Add(TechnoTypes[index]);
                    break;
                }
            }
        }
        return list;
    }
    return defvalue;
}
