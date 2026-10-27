// CCINIClass::Put_Voc_List (0x0046B0B0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Voc_Name@@YIPBDH@Z=00714a00

bool CCINIClass::Put_Voc_List(char const *section, char const *entry, TypeList<int> list)
{
    char buffer[128] = "";
    for (int index = 0; index < list.Count(); index++) {
        if (buffer[0] != '\0') {
            strcat(buffer, ",");
        }
        strcat(buffer, Voc_Name(list[index]));
    }
    return Put_String(section, entry, buffer);
}
