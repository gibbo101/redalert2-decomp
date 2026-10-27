// CCINIClass::Put_Integer_List (0x0046B370).
// Layout and behaviour: shared/ccini_class.hpp.
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
extern "C" char *__cdecl strcat(char *destination, char const *source);
#pragma intrinsic(strcat)

bool CCINIClass::Put_Integer_List(char const *section, char const *entry, TypeList<int> const &list)
{
    char buffer[512] = "";
    for (int index = 0; index < list.Count(); index++) {
        if (buffer[0] != '\0') {
            strcat(buffer, ",");
        }
        char number[12];
        sprintf(number, "%d", list[index]);
        strcat(buffer, number);
    }
    return Put_String(section, entry, buffer);
}
