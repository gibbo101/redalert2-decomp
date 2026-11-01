// char const *__fastcall unknown_table_name_6f8e00(int id) (0x006F8E00): the name of a language; "unknown" when it
// is not in the table.
#include "shared/string_table_file.hpp"
// @ref ??_C@_07CAMD@unknown?$AA@=007ccce0
char const *__fastcall unknown_table_name_6f8e00(int id)
{
    LanguageInfo *entry = unknown_table_find_6f8dd0(id);
    if (entry != 0) {
        return entry->Name;
    }
    return "unknown";
}
