// TypeList<int> __fastcall Get_Voc_List(CCINIClass &ini, char const *section, char const *entry, TypeList<int> defvalue) (0x0050B610)
// The sounds named by the entry (comma separated; unknown names skipped),
// else the default. The out-of-line copy InfantryType.cpp's readers call.
#include "shared/infantry_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/voc_class.hpp"
// @ref ?Find@VocClass@@SIPAV1@PBD@Z=00714990
// @ref ?Index_Of@VocClass@@SIHPAV1@@Z=00714a30

extern "C" char *__cdecl strtok(char *string, char const *delimiters);

TypeList<int> __fastcall Get_Voc_List(CCINIClass &ini, char const *section, char const *entry, TypeList<int> defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer))) {
        TypeList<int> list;
        for (char *name = strtok(buffer, ","); name != 0 && *name != 0; name = strtok(0, ",")) {
            VocClass *voc = VocClass::Find(name);
            if (voc != 0) {
                list.Add(VocClass::Index_Of(voc));
            }
        }
        return list;
    }
    return defvalue;
}
