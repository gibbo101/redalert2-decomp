// void __fastcall unknown_get_f8_value(UnknownValueOwner_004035b0 *, int *out) -- 0x004035B0
// Purpose: stores the value of the member at +0xF8 (0x004072F0) in *out.
// No direct callers. Types not identified.
// @ref ?unknown_value_4072f0@UnknownValueMember_004035b0@@QAEHXZ=004072f0

struct UnknownValueMember_004035b0 {
    int unknown_value_4072f0();
};

struct UnknownValueOwner_004035b0 {
    char unknown_00[0xf8];
    UnknownValueMember_004035b0 unknown_f8;
};

void __fastcall unknown_get_f8_value_004035b0(UnknownValueOwner_004035b0 *owner, int *out)
{
    *out = owner->unknown_f8.unknown_value_4072f0();
}
