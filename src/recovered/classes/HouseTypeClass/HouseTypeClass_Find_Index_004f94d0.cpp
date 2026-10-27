// int __fastcall HouseTypeClass::Find_Index(char const *name) (0x004F94D0)
// @ref ??_C@_08PECD@?$DMrandom?$DO?$AA@=007d1f18

int __fastcall HouseTypeClass::Find_Index(char const *name)
{
    if (_stricmp(name, "<random>") == 0) {
        return -2;
    }
    if (name != 0) {
        for (int index = 0; index < HouseTypes.Count(); index++) {
            HouseTypeClass *house = HouseTypes[index];
            if (_stricmp(house->Name, name) == 0 || _stricmp(house->ID, name) == 0) {
                return house->House;
            }
        }
    }
    return -1;
}
