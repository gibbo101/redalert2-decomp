// void UnknownNameTable_006677F0::unknown_scan(char const *name, int arg2) -- 0x006677F0
// Purpose: when name is given and sound is available (0x00406F30), walks
// the records (pointers at +0x38, count at +0x44) while their names
// (first word) differ from name; the result is discarded.
// Assumptions: owner unidentified; arg2 is unused. The loop's result is
// not stored (as in the original).
// @ref _stricmp=00781f20
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
#include "shared/sound_available.hpp"

extern "C" int __cdecl _stricmp(char const *left, char const *right);

struct UnknownNamed_006677f0 {
    char const *Name;
};
struct UnknownNameTable_006677f0 {
    char unknown_00[0x38];
    UnknownNamed_006677f0 **Records;        // +0x38
    char unknown_3c[0x44 - 0x3C];
    int Count;                              // +0x44
    void unknown_scan(char const *name, int arg2);
};

void UnknownNameTable_006677f0::unknown_scan(char const *name, int arg2)
{
    if (name != 0 && unknown_check_406f30()) {
        for (int index = 0; index < Count; index++) {
            char const *other = Records[index]->Name;
            if (_stricmp(name, other) == 0) {
                break;
            }
        }
    }
}
