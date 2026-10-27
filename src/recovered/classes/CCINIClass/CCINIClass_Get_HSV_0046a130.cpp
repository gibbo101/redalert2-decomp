// CCINIClass::Get_HSV (0x0046A130).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

HSVClass CCINIClass::Get_HSV(char const *section, char const *entry, HSVClass const &defvalue) const
{
    char defbuffer[64];
    char buffer[64];
    sprintf(defbuffer, "%d,%d,%d", defvalue.Hue, defvalue.Saturation, defvalue.Value);
    if (Get_String(section, entry, defbuffer, buffer, sizeof(buffer))) {
        int hue = 0;
        int saturation = 0;
        int value = 0;
        sscanf(buffer, "%d,%d,%d", &hue, &saturation, &value);
        return HSVClass(hue, saturation, value);
    }
    return defvalue;
}
