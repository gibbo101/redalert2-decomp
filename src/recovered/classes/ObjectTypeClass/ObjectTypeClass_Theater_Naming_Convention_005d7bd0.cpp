// void __fastcall ObjectTypeClass::Theater_Naming_Convention(char *buffer, int theater) (0x005D7BD0)
// A theater-generic image name ("G", "N" or "C" first, "A" or "T" second,
// either case) gets the theater's letter as its second character.
#include "shared/object_type.hpp"
#include "shared/anim_type.hpp"
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68

void __fastcall ObjectTypeClass::Theater_Naming_Convention(char *buffer, int theater)
{
    if (theater != -1) {
        char first = buffer[0];
        char second = buffer[1];
        if (first >= 'A' && first <= 'Z') {
            first += 'a' - 'A';
        }
        if (second >= 'A' && second <= 'Z') {
            second += 'a' - 'A';
        }
        if ((first == 'g' || first == 'n' || first == 'c') && (second == 'a' || second == 't')) {
            buffer[1] = Theaters[theater].Letter[0];
        }
    }
}
