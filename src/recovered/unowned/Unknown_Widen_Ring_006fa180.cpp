// unsigned short *__fastcall Unknown_006FA180(unsigned char const *string) (0x006FA180)
// Widens a narrow string into the next of eight 0x400-character rotating
// buffers (0x00AC53FC, slot index 0x00AD0460) and answers it; null stays null.
// @ref ?unknown_wide_buffers_ac53fc@@3PAGA=00ac53fc
// @ref ?unknown_wide_index_ad0460@@3HA=00ad0460

extern unsigned short unknown_wide_buffers_ac53fc[];
extern int unknown_wide_index_ad0460;

// The widening copy.
static inline void Widen_String(unsigned short *dst, unsigned char const *src, int limit)
{
    while (*src != 0 && limit != 0) {
        *dst++ = (unsigned short)*src++;
        if (limit != -1) {
            limit--;
        }
    }
    *dst = 0;
}

unsigned short *__fastcall Unknown_006FA180(unsigned char const *string)
{
    if (!string) {
        return 0;
    }
    int slot = unknown_wide_index_ad0460;
    unsigned short *buffer = unknown_wide_buffers_ac53fc + slot * 0x400;
    Widen_String(buffer, string, 0x400);
    buffer[0x3FF] = 0;
    unknown_wide_index_ad0460 = (unknown_wide_index_ad0460 + 1) & 7;
    return buffer;
}
