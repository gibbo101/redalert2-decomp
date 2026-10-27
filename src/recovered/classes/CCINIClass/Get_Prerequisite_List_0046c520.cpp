// Get_Prerequisite_List (0x0046C520).
// Layout and behaviour: shared/ccini_class.hpp.
// @ref ??0?$DynamicVectorClass@H@@QAE@ABV0@@Z=0046ce20
// @ref ??0?$DynamicVectorClass@H@@QAE@IPBH@Z=0046d1f0
// @ref ??0?$TypeList@H@@QAE@ABV0@@Z=0046cbf0
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??_C@_04CFJE@PROC?$AA@=007d20d0
// @ref ??_C@_04GLCI@TECH?$AA@=007d20d8
// @ref ??_C@_05BCPN@RADAR?$AA@=007d1f24
// @ref ??_C@_05CKDA@POWER?$AA@=007d1f40
// @ref ??_C@_07HGND@FACTORY?$AA@=007d1f38
// @ref ??_C@_08JHEE@BARRACKS?$AA@=007d1f2c
// @ref ??_E?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ??_G?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ?Add@?$DynamicVectorClass@H@@QAE_NABH@Z=0046d300
// @ref ?Clear@?$DynamicVectorClass@H@@UAEXXZ=0046cc80
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ?From_Name@BuildingTypeClass@@SIHPBD@Z=004583d0
// @ref ?ID@?$DynamicVectorClass@H@@UAEHABH@Z=0046d350
// @ref ?ID@?$DynamicVectorClass@H@@UAEHPBH@Z=0046ccb0
// @ref ?Resize@?$DynamicVectorClass@H@@UAE_NHPBH@Z=0046d250
#include "shared/ccini_extra.hpp"

TypeList<int> __fastcall Get_Prerequisite_List(CCINIClass &ini, char const *section, char const *entry,
                                               TypeList<int> defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, "", buffer, sizeof(buffer))) {
        TypeList<int> list;
        for (char *token = strtok(buffer, ","); token != 0 && *token != '\0'; token = strtok(0, ",")) {
            bool found = false;
            if (_stricmp(token, "POWER") == 0) {
                list.Add(-1);
                found = true;
            }
            if (_stricmp(token, "FACTORY") == 0) {
                list.Add(-2);
                found = true;
            }
            if (_stricmp(token, "BARRACKS") == 0) {
                list.Add(-3);
                found = true;
            }
            if (_stricmp(token, "RADAR") == 0) {
                list.Add(-4);
                found = true;
            }
            if (_stricmp(token, "TECH") == 0) {
                list.Add(-5);
                found = true;
            }
            if (_stricmp(token, "PROC") == 0) {
                list.Add(-6);
                found = true;
            }
            if (!found) {
                int index = BuildingTypeClass::From_Name(token);
                if (index != -1) {
                    list.Add(index);
                }
            }
        }
        return list;
    }
    return defvalue;
}
