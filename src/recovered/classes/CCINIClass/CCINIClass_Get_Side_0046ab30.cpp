// CCINIClass::Get_Side (0x0046AB30).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ??0SideClass@@QAE@PBD@Z=0067ae10

int CCINIClass::Get_Side(char const *section, char const *entry, int defvalue) const
{
    char buffer[128];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        int index = SideClass::Find_Index(buffer);
        if (index == -1) {
            // An unknown name creates the side.
            return Sides.ID(new SideClass(buffer));
        }
        return index;
    }
    return defvalue;
}
