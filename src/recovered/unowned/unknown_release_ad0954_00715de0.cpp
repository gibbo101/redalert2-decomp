// void __fastcall unknown_release_ad0954(bool flag) -- 0x00715DE0
// Purpose: marks the object at 0x00AD0954 with state 2 (+0x48) and forgets
// it, has the object at 0x00AD095C run 0x00407E60, and with flag set
// continues into 0x007157B0.
// Assumptions: none of the objects or callees is identified (callers in the
// 0x0065Dxxx and 0x0073xxxx units); names are placeholders.

struct UnknownObject_ad0954 {
    char unknown_00[0x48];
    int unknown_48;                 // +0x48
};
class UnknownObject_ad095c {
public:
    void Unknown_00407E60();
};
extern UnknownObject_ad0954 *unknown_object_ad0954;
extern UnknownObject_ad095c *unknown_object_ad095c;
void Unknown_007157B0();
// @ref ?unknown_object_ad0954@@3PAUUnknownObject_ad0954@@A=00ad0954
// @ref ?unknown_object_ad095c@@3PAVUnknownObject_ad095c@@A=00ad095c
// @ref ?Unknown_00407E60@UnknownObject_ad095c@@QAEXXZ=00407e60
// @ref ?Unknown_007157B0@@YAXXZ=007157b0

void __fastcall unknown_release_ad0954(bool flag)
{
    if (unknown_object_ad0954 != 0) {
        unknown_object_ad0954->unknown_48 = 2;
        unknown_object_ad0954 = 0;
    }
    if (unknown_object_ad095c != 0) {
        unknown_object_ad095c->Unknown_00407E60();
    }
    if (flag) {
        Unknown_007157B0();
    }
}
