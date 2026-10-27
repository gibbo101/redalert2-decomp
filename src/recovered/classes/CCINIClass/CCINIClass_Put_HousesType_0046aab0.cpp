// CCINIClass::Put_HousesType (0x0046AAB0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ??_C@_08PECD@?$DMrandom?$DO?$AA@=007d1f18

bool CCINIClass::Put_HousesType(char const *section, char const *entry, int house)
{
    char const *name = "<none>";
    if (house == -2) {
        name = "<random>";
    } else if (house == -3) {
        name = "<random>";
    } else if (house != -1 && house >= 0 && house < HouseTypes.Count()) {
        name = HouseTypes[house]->ID;
    }
    return Put_String(section, entry, name);
}
