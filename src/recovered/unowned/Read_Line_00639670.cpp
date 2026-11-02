// int __fastcall Read_Line(Straw &file, char *buffer, int len, bool &eof) (0x00639670; Tiberian Sun readline.cpp): one line through LF, CR dropped, at most len - 1 bytes kept; returns strlen.
#include "shared/reference_counted.hpp"
#include "shared/straw.hpp"
#include "shared/crt_string.hpp"

int __fastcall Read_Line(Straw &file, char *buffer, int len, bool &eof)
{
    if (len == 0 || buffer == 0) {
        return 0;
    }

    int count = 0;
    for (;;) {
        char c;
        if (file.Get(&c, sizeof(c)) != sizeof(c)) {
            eof = true;
            buffer[count] = '\0';
            break;
        }

        if (c == '\x0A') {
            break;
        }
        if (c != '\x0D' && count + 1 < len) {
            buffer[count++] = c;
        }
    }
    buffer[count] = '\0';
    return strlen(buffer);
}
