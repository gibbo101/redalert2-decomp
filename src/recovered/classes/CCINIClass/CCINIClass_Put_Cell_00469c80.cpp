// CCINIClass::Put_Cell (0x00469C80).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ??_C@_05BBIB@?$CFd?0?$CFd?$AA@=007d1f10

bool CCINIClass::Put_Cell(char const *section, char const *entry, Cell const &cell)
{
    char buffer[64];
    sprintf(buffer, "%d,%d", cell.X, cell.Y);
    return Put_String(section, entry, buffer);
}
