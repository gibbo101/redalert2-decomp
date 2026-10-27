// Assigns each linked item its running position (0x005B5D80): the first item
// sits one step after the start when both flags at +0x19 and +0x1A are set.
struct UnknownLayoutItem_005b5d80 {
    virtual void unknown_slot00();
    virtual UnknownLayoutItem_005b5d80 *Next();     // slot 1
    char unknown_04[0x10 - 4];
    int Position;                                   // +0x10
};

struct UnknownLayoutList_005b5d80 {
    UnknownLayoutItem_005b5d80 *First;              // +0x00
    int unknown_04;
    int Start;                                      // +0x08
    char unknown_0c[0x14 - 0x0C];
    int Step;                                       // +0x14
    char unknown_18;
    bool unknown_19;
    bool unknown_1a;
    void Layout_005b5d80();
};

void UnknownLayoutList_005b5d80::Layout_005b5d80()
{
    int position;
    if (unknown_19 && unknown_1a) {
        position = Start + Step;
    } else {
        position = Start;
    }
    UnknownLayoutItem_005b5d80 *item = First;
    while (item) {
        item->Position = position;
        item = item->Next();
        position += Step;
    }
}
