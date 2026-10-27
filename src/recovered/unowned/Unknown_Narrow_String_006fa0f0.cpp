// void __fastcall Unknown_006FA0F0(char *dst, unsigned short const *src, int limit) (0x006FA0F0)
// Narrows a wide string into dst, stopping at the terminator or after limit
// characters (-1: no limit); always terminates dst. Called from 20 sites
// (hypothesis: a wcstombs-like helper of the unit's string code).

void __fastcall Unknown_006FA0F0(char *dst, unsigned short const *src, int limit)
{
    while (*src != 0 && limit != 0) {
        *dst++ = (char)*src++;
        if (limit != -1) {
            limit--;
        }
    }
    *dst = 0;
}
