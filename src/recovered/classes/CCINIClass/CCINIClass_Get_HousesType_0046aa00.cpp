// CCINIClass::Get_HousesType (0x0046AA00).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ??0HouseTypeClass@@QAE@PBD@Z=004f90f0
// @ref ?HouseTypes@@3V?$DynamicVectorClass@PAVHouseTypeClass@@@@A=00a35d08

int CCINIClass::Get_HousesType(char const *section, char const *entry, int defvalue) const
{
    char buffer[128];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        int index = HouseTypeClass::Find_Index(buffer);
        if (index == -1) {
            // An unknown name creates the house type.
            return HouseTypes.ID(new HouseTypeClass(buffer));
        }
        return index;
    }
    return defvalue;
}
