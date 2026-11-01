// void __fastcall unknown_touch_pages_737160(char *buffer, int length) (0x00737160)
#include "shared/win_util.hpp"

void __fastcall unknown_touch_pages_737160(char *buffer, int length)
{
    int offset = (int)buffer & 0xFFF;
    char *page = buffer + offset;
    length -= offset;
    if (length < 1) {
        return;
    }
    length -= length & 0xFFF;
    if (length < 1) {
        return;
    }
    int sum = 0;
    for (int index = 0x10000; index < length; index += 0x1000) {
        sum = sum + page[index] + page[index - 0x10000];
    }
}
