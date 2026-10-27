// char *__fastcall Unknown_006FA120(unsigned short const *string) (0x006FA120)
// Narrows a wide string into the next of eight 0x400-byte rotating buffers
// (0x00AC136C, slot index 0x00AD045C) and answers it; null stays null.
// @ref ?unknown_narrow_buffers_ac136c@@3PADA=00ac136c
// @ref ?unknown_narrow_index_ad045c@@3HA=00ad045c

extern char unknown_narrow_buffers_ac136c[];
extern int unknown_narrow_index_ad045c;

// The narrowing copy (also out of line at 0x006FA0F0).
static inline void Narrow_String(char *dst, unsigned short const *src, int limit)
{
    while (*src != 0 && limit != 0) {
        *dst++ = (char)*src++;
        if (limit != -1) {
            limit--;
        }
    }
    *dst = 0;
}

char *__fastcall Unknown_006FA120(unsigned short const *string)
{
    if (!string) {
        return 0;
    }
    int slot = unknown_narrow_index_ad045c;
    char *buffer = unknown_narrow_buffers_ac136c + slot * 0x400;
    Narrow_String(buffer, string, 0x400);
    buffer[0x3FF] = 0;
    unknown_narrow_index_ad045c = (unknown_narrow_index_ad045c + 1) & 7;
    return buffer;
}
