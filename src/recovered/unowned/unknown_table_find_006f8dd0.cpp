// UnknownTableEntry_7f8cf0 *__fastcall unknown_table_find_6f8dd0(int id) (0x006F8DD0): the language table entry
// with this id; null when there is none.
#include "shared/string_table_file.hpp"
// @ref ?unknown_languages_7f8cf0@@3PAUUnknownTableEntry_7f8cf0@@A=007f8cf0
UnknownTableEntry_7f8cf0 *__fastcall unknown_table_find_6f8dd0(int id)
{
    for (LanguageInfo *entry = unknown_languages_7f8cf0; entry->ID != 10; entry++) {
        if (entry->ID == id) {
            return entry;
        }
    }
    return 0;
}
