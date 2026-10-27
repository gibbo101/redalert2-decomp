// CCINIClass::Get_RTTIType (0x0046A4B0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Name_From_RTTI@@YIPBDW4RTTIType@@@Z=0040db60
// @ref ?RTTI_From_Name@@YI?AW4RTTIType@@PBD@Z=0040db90

RTTIType CCINIClass::Get_RTTIType(char const *section, char const *entry, RTTIType defvalue) const
{
    char buffer[32];
    Get_String(section, entry, Name_From_RTTI(defvalue), buffer, sizeof(buffer));
    return RTTI_From_Name(buffer);
}
