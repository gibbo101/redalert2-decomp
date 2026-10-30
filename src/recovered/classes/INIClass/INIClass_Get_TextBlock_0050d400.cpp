// INIClass::Get_TextBlock (0x0050D400)
// Joins the section's entries (in order, separated by one space) into
// buffer, stopping when it is full; returns the length written.
#include "shared/ini_class.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_string_83c55c@@3PADA=0083c55c

int INIClass::Get_TextBlock(char const *section, char *buffer, int length) const
{
    if (length <= 0) return 0;

    buffer[0] = '\0';
    if (length <= 1) return 0;

    int elen = Entry_Count(section);
    int total = 0;
    for (int index = 0; index < elen; index++) {

        if (index > 0) {
            *buffer++ = ' ';
            length--;
            total++;
        }

        Get_String(section, Get_Entry(section, index), unknown_string_83c55c, buffer, length);

        int partial = strlen(buffer);
        total += partial;
        buffer += partial;
        length -= partial;
        if (length <= 1) break;
    }
    return total;
}
