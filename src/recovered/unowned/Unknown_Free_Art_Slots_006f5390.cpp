// void Unknown_006F5390() (0x006F5390)
// Frees the two loaded art slots (hypothesis): a raw block (0x00AC11A0, 0x00AC11A8)
// and an owned object (0x00AC11A4, 0x00AC11AC) each, clearing the pointers.
// @ref ?unknown_block_ac11a0@@3PAXA=00ac11a0
// @ref ?unknown_object_ac11a4@@3PAUUnknownOwnedObject@@A=00ac11a4
// @ref ?unknown_block_ac11a8@@3PAXA=00ac11a8
// @ref ?unknown_object_ac11ac@@3PAUUnknownOwnedObject@@A=00ac11ac
// @ref ??3@YAXPAX@Z=00781d3b

struct UnknownOwnedObject {
    virtual ~UnknownOwnedObject();
};
extern void *unknown_block_ac11a0;
extern UnknownOwnedObject *unknown_object_ac11a4;
extern void *unknown_block_ac11a8;
extern UnknownOwnedObject *unknown_object_ac11ac;

void __fastcall Unknown_006F5390()
{
    if (unknown_block_ac11a0 != 0) {
        delete unknown_block_ac11a0;
        unknown_block_ac11a0 = 0;
    }
    if (unknown_object_ac11a4 != 0) {
        delete unknown_object_ac11a4;
        unknown_object_ac11a4 = 0;
    }
    if (unknown_block_ac11a8 != 0) {
        delete unknown_block_ac11a8;
        unknown_block_ac11a8 = 0;
    }
    if (unknown_object_ac11ac != 0) {
        delete unknown_object_ac11ac;
        unknown_object_ac11ac = 0;
    }
}
