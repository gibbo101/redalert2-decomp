// char const *Name_From_Category(CategoryType category) -- 0x00468EC0
// The category's INI name ("AFV"), "<none>" out of range.

char const *__fastcall Name_From_Category(CategoryType category)
{
    if ((unsigned)category < CATEGORY_COUNT) {
        return CategoryNames[category].Name;
    }
    return "<none>";
}
