// void UnknownTable_70c540::Clear() -- 0x0070C540
// Purpose: zeroes the first Count (+0x800) words of the table.
// Assumptions: owner unidentified (callers 0x00699A89..); names are
// placeholders.

class UnknownTable_70c540 {
public:
    void Clear();

    int Table[0x200];           // +0x000
    int Count;                  // +0x800
};

void UnknownTable_70c540::Clear()
{
    for (int index = 0; index < Count; index++) {
        Table[index] = 0;
    }
}
