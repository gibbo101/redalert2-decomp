// CCINIClass::Put_Techno_List (0x0046BB30).
// Layout and behaviour: shared/ccini_class.hpp; TechnoTypeClass in
// CCINIClass_Get_Techno_List_0046b930.cpp.

bool CCINIClass::Put_Techno_List(char const *section, char const *entry, TypeList<TechnoTypeClass *> const &list)
{
    char buffer[512] = "";
    for (int index = 0; index < list.Count(); index++) {
        if (buffer[0] != '\0') {
            strcat(buffer, ",");
        }
        strcat(buffer, list[index]->ID);
    }
    return Put_String(section, entry, buffer);
}
