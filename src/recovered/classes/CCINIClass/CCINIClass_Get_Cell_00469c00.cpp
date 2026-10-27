// CCINIClass::Get_Cell (0x00469C00).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

Cell CCINIClass::Get_Cell(char const *section, char const *entry, Cell const &defvalue) const
{
    char buffer[64];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        int x;
        int y;
        sscanf(buffer, "%d,%d", &x, &y);
        return Cell(x, y);
    }
    return defvalue;
}
