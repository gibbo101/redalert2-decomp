// CCINIClass::Get_SpeedType (0x0046C400).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Name_From_Speed@@YIPBDW4SpeedType@@@Z=00482f60
// @ref ?Speed_From_Name@@YI?AW4SpeedType@@PBD@Z=00482f20

SpeedType CCINIClass::Get_SpeedType(char const *section, char const *entry, SpeedType defvalue)
{
    char buffer[128];
    if (Get_String(section, entry, Name_From_Speed(defvalue), buffer, sizeof(buffer))) {
        return Speed_From_Name(buffer);
    }
    return defvalue;
}
