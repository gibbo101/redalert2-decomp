// CategoryType Category_From_Name(char const *name) -- 0x00468EE0
// The category whose INI name or description equals name ignoring case, else CATEGORY_NONE.
// @ref __stricmp=00781f20

CategoryType __fastcall Category_From_Name(char const *name)
{
    if (name != 0) {
        for (CategoryType category = CATEGORY_SOLDIER; category < CATEGORY_COUNT; category = CategoryType(category + 1)) {
            if (_stricmp(CategoryNames[category].Name, name) == 0 || _stricmp(CategoryNames[category].Description, name) == 0) {
                return category;
            }
        }
    }
    return CATEGORY_NONE;
}
