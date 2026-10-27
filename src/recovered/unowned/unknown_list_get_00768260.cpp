// bool UnknownList_768260::Get(void **item, int index) -- 0x00768260
// Purpose: copies the pointer at index of the array at +0x08 (count at
// +0x00) to *item; false when index is out of range.
// Assumptions: owner unidentified (caller 0x00763CF4); names are placeholders.

class UnknownList_768260 {
public:
    bool Get(void **item, int index);

    int Count;              // +0x00
    int unknown_04;
    void **Items;           // +0x08
};

bool UnknownList_768260::Get(void **item, int index)
{
    if (index >= 0 && index < Count) {
        *item = Items[index];
        return true;
    }
    return false;
}
