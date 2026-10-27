// CCINIClass::Get_Object_Type (0x0046C2F0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?From_Name@InfantryTypeClass@@SIHPBD@Z=0050a070
// @ref ?From_Name@UnitTypeClass@@SIHPBD@Z=0070a890
// @ref ?From_Name@AircraftTypeClass@@SIHPBD@Z=0041be60
// @ref ?From_Name@BuildingTypeClass@@SIHPBD@Z=004583d0
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref ?AircraftTypes@@3V?$DynamicVectorClass@PAVAircraftTypeClass@@@@A=00a3d278
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc

ObjectTypeClass *CCINIClass::Get_Object_Type(char const *section, char const *entry)
{
    char buffer[128];
    ObjectTypeClass *type = 0;
    Get_String(section, entry, "<none>", buffer, sizeof(buffer));
    int index = InfantryTypeClass::From_Name(buffer);
    if (index != -1) {
        type = InfantryTypes[index];
    } else {
        index = UnitTypeClass::From_Name(buffer);
        if (index != -1) {
            type = UnitTypes[index];
        } else {
            index = AircraftTypeClass::From_Name(buffer);
            if (index != -1) {
                type = AircraftTypes[index];
            } else {
                index = BuildingTypeClass::From_Name(buffer);
                if (index != -1) {
                    type = BuildingTypes[index];
                }
            }
        }
    }
    return type;
}
