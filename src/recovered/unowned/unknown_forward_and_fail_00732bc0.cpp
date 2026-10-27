// bool UnknownOwner_00732BC0::unknown_forward(int arg1, int arg2) -- 0x00732BC0
// Purpose: runs 0x00732870 on the object at +0x1C and returns false; both
// arguments are unused.
// Assumptions: a __thiscall member (likely a virtual slot) of an
// unidentified class; /O1 like its neighbours.
// @ref ?unknown_call_732870@UnknownPart_00732bc0@@QAEXXZ=00732870

struct UnknownPart_00732bc0 {
    void unknown_call_732870();             // 0x00732870
};
struct UnknownOwner_00732bc0 {
    char unknown_00[0x1C];
    UnknownPart_00732bc0 *unknown_1c;       // +0x1C
    bool unknown_forward(int arg1, int arg2);
};

bool UnknownOwner_00732bc0::unknown_forward(int arg1, int arg2)
{
    unknown_1c->unknown_call_732870();
    return false;
}
