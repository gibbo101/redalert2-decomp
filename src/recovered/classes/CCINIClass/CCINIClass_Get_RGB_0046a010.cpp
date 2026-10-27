// CCINIClass::Get_RGB (0x0046A010).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

RGBClass CCINIClass::Get_RGB(char const *section, char const *entry, RGBClass const &defvalue) const
{
    char defbuffer[64];
    char buffer[64];
    sprintf(defbuffer, "%d,%d,%d", defvalue.Red, defvalue.Green, defvalue.Blue);
    if (Get_String(section, entry, defbuffer, buffer, sizeof(buffer))) {
        int red;
        int green;
        int blue;
        sscanf(buffer, "%d,%d,%d", &red, &green, &blue);
        return RGBClass(red, green, blue);
    }
    return defvalue;
}
