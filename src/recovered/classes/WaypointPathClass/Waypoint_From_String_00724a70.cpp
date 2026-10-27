// Waypoint From String (0x724A70)
#include "shared/waypoint_path.hpp"
// @ref _isalpha=00782b0e
// @ref _toupper=007829d3

int __fastcall Waypoint_From_String(char const *string)
{
    int index = -1;
    if (isalpha(string[0])) {
        index = toupper(string[0]) - 'A';
        if (isalpha(string[1])) {
            return toupper(string[1]) - 0x27 + index * 26;
        }
    }
    return index;
}

