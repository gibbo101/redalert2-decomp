// CCINIClass::Get_CategoryType (0x00469EA0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Name_From_Category@@YIPBDW4CategoryType@@@Z=00468ec0
// @ref ?Category_From_Name@@YI?AW4CategoryType@@PBD@Z=00468ee0

CategoryType CCINIClass::Get_CategoryType(char const *section, char const *entry, CategoryType defvalue) const
{
    char buffer[32];
    Get_String(section, entry, Name_From_Category(defvalue), buffer, sizeof(buffer));
    return Category_From_Name(buffer);
}
