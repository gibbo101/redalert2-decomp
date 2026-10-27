// char const *__fastcall unknown_table_name_6f8e00(int id) -- 0x006F8E00
// Purpose: the first name of the entry with this id in the 16-byte table at
// 0x007F8CF0 (an id, then three name pointers; the list ends at id 10),
// through an inline lookup; "unknown" when there is none.
// Assumptions: the table's meaning is unidentified (no callers by direct
// call); names are placeholders.

struct UnknownTableEntry_7f8cf0 {
    int ID;
    char const *Name;
    char const *unknown_08;
    char const *unknown_0c;
};
extern UnknownTableEntry_7f8cf0 unknown_table_7f8cf0[];
// @ref ?unknown_table_7f8cf0@@3PAUUnknownTableEntry_7f8cf0@@A=007f8cf0
// @ref ??_C@_07CAMD@unknown?$AA@=007ccce0

static inline UnknownTableEntry_7f8cf0 *Find_Entry(int id)
{
    for (UnknownTableEntry_7f8cf0 *entry = unknown_table_7f8cf0; entry->ID != 10; entry++) {
        if (entry->ID == id) {
            return entry;
        }
    }
    return 0;
}

char const *__fastcall unknown_table_name_6f8e00(int id)
{
    UnknownTableEntry_7f8cf0 *entry = Find_Entry(id);
    if (entry != 0) {
        return entry->Name;
    }
    return "unknown";
}
