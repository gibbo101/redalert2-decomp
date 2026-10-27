// int __fastcall unknown_is_narrow_text(unsigned short const *text) -- 0x006F9E90
// Purpose: whether every character of the wide text fits in 8 bits.
// Assumptions: name hypothesis (string-table area).

int __fastcall unknown_is_narrow_text(unsigned short const *text)
{
    while (*text != 0) {
        if (*text++ > 0xFF) {
            return 0;
        }
    }
    return 1;
}
