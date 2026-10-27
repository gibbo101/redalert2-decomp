// CCINIClass::Put_Side (0x0046ABE0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_Side(char const *section, char const *entry, int side)
{
    char const *name = "<none>";
    if (side != -1) {
        name = Sides[side]->ID;
    }
    return Put_String(section, entry, name);
}
