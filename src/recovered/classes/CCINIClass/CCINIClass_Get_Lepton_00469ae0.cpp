// CCINIClass::Get_Lepton (0x00469AE0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref __real@8@bfff8000000000000000=0079d578

int CCINIClass::Get_Lepton(char const *section, char const *entry, int defvalue) const
{
    double value = Get_Double(section, entry, -1.0);
    if (value == -1.0) {
        return defvalue;
    }
    return value * 256.0;
}
