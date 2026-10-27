// CCINIClass::Get_Color_List (0x0046BF60).
// Layout and behaviour: shared/ccini_class.hpp, shared/rgb_class.hpp.
// @ref ??0?$VectorClass@VRGBClass@@@@QAE@ABV0@@Z=0046d660
// @ref ??0?$VectorClass@VRGBClass@@@@QAE@IPBVRGBClass@@@Z=0046dc90
// @ref ??4?$VectorClass@VRGBClass@@@@QAEAAV0@ABV0@@Z=0046dd20
// @ref ??8?$VectorClass@VRGBClass@@@@UBE_NABV0@@Z=0046d720
// @ref ??_7?$TypeList@VRGBClass@@@@6B@=0079da74
// @ref ??_7?$VectorClass@VRGBClass@@@@6B@=0079da54
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_E?$TypeList@VRGBClass@@@@UAEPAXI@Z=0046cf00
// @ref ??_E?$VectorClass@VRGBClass@@@@UAEPAXI@Z=0046db10
// @ref ??_G?$TypeList@VRGBClass@@@@UAEPAXI@Z=0046cf00
// @ref ??_G?$VectorClass@VRGBClass@@@@UAEPAXI@Z=0046db10
// @ref ?Clear@?$DynamicVectorClass@VRGBClass@@@@UAEXXZ=0046cd40
// @ref ?Clear@?$VectorClass@VRGBClass@@@@UAEXXZ=0046d880
// @ref ?Fetch@?$VectorClass@VRGBClass@@@@UBE?AVRGBClass@@H@Z=0046cda0
// @ref ?ID@?$DynamicVectorClass@VRGBClass@@@@UAEHABVRGBClass@@@Z=0046da30
// @ref ?ID@?$DynamicVectorClass@VRGBClass@@@@UAEHPBVRGBClass@@@Z=0046cd70
// @ref ?ID@?$VectorClass@VRGBClass@@@@UAEHABVRGBClass@@@Z=0046d8b0
// @ref ?ID@?$VectorClass@VRGBClass@@@@UAEHPBVRGBClass@@@Z=0046d900
// @ref ?Resize@?$DynamicVectorClass@VRGBClass@@@@UAE_NHPBVRGBClass@@@Z=0046d930
// @ref ?Resize@?$VectorClass@VRGBClass@@@@UAE_NHPBVRGBClass@@@Z=0046d780
#include "shared/ccini_class.hpp"

TypeList<RGBClass> CCINIClass::Get_Color_List(char const *section, char const *entry, TypeList<RGBClass> defvalue)
{
    char buffer[512];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        TypeList<RGBClass> list;
        for (char *token = strtok(buffer, ","); token != 0 && *token != '\0'; token = strtok(0, ",")) {
            RGBClass color;
            bool valid = true;
            if (token != 0) {
                color.Red = atoi(token + 1);      // after the '('
            } else {
                valid = false;
            }
            token = strtok(0, ",");
            if (token != 0 && *token != '\0') {
                color.Green = atoi(token);
            } else {
                valid = false;
            }
            token = strtok(0, ",");
            if (token != 0 && *token != '\0') {
                token[strlen(token) - 1] = '\0';  // drops the ')'
                color.Blue = atoi(token);
                if (valid) {
                    list.Add(color);
                }
            }
        }
        return list;
    }
    return defvalue;
}
