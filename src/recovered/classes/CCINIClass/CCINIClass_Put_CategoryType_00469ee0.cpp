// CCINIClass::Put_CategoryType (0x00469EE0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_CategoryType(char const *section, char const *entry, CategoryType category)
{
    if (category != CATEGORY_SOLDIER) {
        return Put_String(section, entry, Name_From_Category(category));
    }
    return false;
}
