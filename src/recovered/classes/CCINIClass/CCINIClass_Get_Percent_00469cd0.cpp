// CCINIClass::Get_Percent (0x00469CD0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

int CCINIClass::Get_Percent(char const *section, char const *entry, int defvalue) const
{
    int value = Get_Int(section, entry, -1);
    if (value == -1) {
        return defvalue;
    }
    if (value >= 100) {
        value = 100;
    }
    int result = ((value > 0 ? value : 0) * 256) / 100;
    if (result >= 255) {
        result = 255;
    }
    return result;
}
