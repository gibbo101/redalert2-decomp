// void __fastcall unknown_release_and_delete(UnknownComHolder_00402170 *) -- 0x00402170
// Purpose: calls the third entry of the function table that +0xD4 points
// to, then frees the holder with operator delete. No direct callers.
// @ref ??3@YAXPAX@Z=00781d3b

struct UnknownFunctionTable_00402170 {
    void (*unknown_00)();
    void (*unknown_04)();
    void (*unknown_08)();
};

struct UnknownComHolder_00402170 {
    char unknown_00[0xd4];
    UnknownFunctionTable_00402170 *unknown_d4;
};

void __fastcall unknown_release_and_delete_00402170(UnknownComHolder_00402170 *holder)
{
    holder->unknown_d4->unknown_08();
    operator delete(holder);
}
