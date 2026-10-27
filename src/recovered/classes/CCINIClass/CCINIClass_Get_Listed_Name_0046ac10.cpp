// CCINIClass::Get_Listed_Name (0x0046AC10).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?unknown_name_index_482e60@@YIHPBD@Z=00482e60

int CCINIClass::Get_Listed_Name(char const *section, char const *entry, int defvalue) const
{
    char buffer[128];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        int index = unknown_name_index_482e60(buffer);
        if (index != -1) {
            return index;
        }
    }
    return defvalue;
}
