// UnknownTableEntry_7f8cf0 *__fastcall unknown_table_find_6f8dd0(int id) -- 0x006F8DD0
// Purpose: the entry with this id in the 16-byte table at 0x007F8CF0 (the
// list ends at id 10); null when there is none. 0x006F8E00 expands it.
// Assumptions: the table's meaning is unidentified; names are placeholders.

struct UnknownTableEntry_7f8cf0 {
    int ID;
    char const *Name;
    char const *unknown_08;
    char const *unknown_0c;
};
extern UnknownTableEntry_7f8cf0 unknown_table_7f8cf0[];
// @ref ?unknown_table_7f8cf0@@3PAUUnknownTableEntry_7f8cf0@@A=007f8cf0

UnknownTableEntry_7f8cf0 *__fastcall unknown_table_find_6f8dd0(int id)
{
    for (UnknownTableEntry_7f8cf0 *entry = unknown_table_7f8cf0; entry->ID != 10; entry++) {
        if (entry->ID == id) {
            return entry;
        }
    }
    return 0;
}
