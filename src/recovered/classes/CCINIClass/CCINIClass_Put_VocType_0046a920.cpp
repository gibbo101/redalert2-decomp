// CCINIClass::Put_VocType (0x0046A920).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_VocType(char const *section, char const *entry, int voc)
{
    if ((char)voc == -1) {
        return Put_String(section, entry, "<none>");
    }
    return Put_String(section, entry, Voc_Name(voc));
}
