// void __fastcall unknown_global_c_value(int *out) -- 0x004031D0
// Purpose: stores the value of the member at +0x0C of the object that
// 0x007CC968 points to (0x004072F0) in *out. No direct callers.
// @ref ?unknown_value_4072f0@UnknownValueMember_004031d0@@QAEHXZ=004072f0
// @ref ?unknown_object_7cc968@@3PAUUnknownValueOwner_004031d0@@A=007cc968

struct UnknownValueMember_004031d0 {
    int unknown_value_4072f0();
};

struct UnknownValueOwner_004031d0 {
    int unknown_00[3];
    UnknownValueMember_004031d0 unknown_0c;
};

extern UnknownValueOwner_004031d0 *unknown_object_7cc968;

void __fastcall unknown_global_c_value_004031d0(int *out)
{
    *out = unknown_object_7cc968->unknown_0c.unknown_value_4072f0();
}
