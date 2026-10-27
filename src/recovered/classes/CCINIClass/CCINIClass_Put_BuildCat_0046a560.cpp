// CCINIClass::Put_BuildCat (0x0046A560).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_BuildCat(char const *section, char const *entry, BuildCat category)
{
    return Put_String(section, entry, Name_From_BuildCat(category));
}
