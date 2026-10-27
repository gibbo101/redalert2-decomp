// CCINIClass::Get_Integer_List (0x0046B1B0).
// Layout and behaviour: shared/ccini_class.hpp.
// @ref ??0?$VectorClass@H@@QAE@ABV0@@Z=0046cfa0
// @ref ??0?$VectorClass@H@@QAE@IPBH@Z=0046d020
// @ref ??4?$VectorClass@H@@QAEAAV0@ABV0@@Z=0046db60
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ??_7?$TypeList@H@@6B@=0079d9f4
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_E?$TypeList@H@@UAEPAXI@Z=0046cdd0
// @ref ??_E?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_G?$TypeList@H@@UAEPAXI@Z=0046cdd0
// @ref ??_G?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ?Clear@?$DynamicVectorClass@H@@UAEXXZ=0046cc80
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ?ID@?$DynamicVectorClass@H@@UAEHABH@Z=0046d350
// @ref ?ID@?$DynamicVectorClass@H@@UAEHPBH@Z=0046ccb0
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
// @ref ?Resize@?$DynamicVectorClass@H@@UAE_NHPBH@Z=0046d250
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
#include "shared/ccini_class.hpp"

TypeList<int> CCINIClass::Get_Integer_List(char const *section, char const *entry, TypeList<int> defvalue)
{
    char buffer[512];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        TypeList<int> list;
        for (char *token = strtok(buffer, ","); token != 0 && *token != '\0'; token = strtok(0, ",")) {
            list.Add(atoi(token));
        }
        return list;
    }
    return defvalue;
}
