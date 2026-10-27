// bool UnknownList_636ea0::Has_Free_Slot() const -- 0x00636EA0
// Purpose: whether the pointer array at +0xCC (count +0xD0) has a null
// entry.
// Assumptions: owner unidentified; names are placeholders.

class UnknownList_636ea0 {
public:
    bool Has_Free_Slot() const;

    char unknown_00[0xCC];
    void **Slots;               // +0xCC
    int Count;                  // +0xD0
};

bool UnknownList_636ea0::Has_Free_Slot() const
{
    for (int index = 0; index < Count; index++) {
        if (Slots[index] == 0) {
            return true;
        }
    }
    return false;
}
