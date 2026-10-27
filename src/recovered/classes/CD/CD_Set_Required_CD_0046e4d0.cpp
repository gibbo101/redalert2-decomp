// void __fastcall CD::Set_Required_CD(int cd) (0x0046E4D0)
// Records the disk the next file needs; any disk (-2) for a local install.
// Assumes: name and the IsLocal meaning are hypotheses.
#include "shared/cd.hpp"
// @ref ?RequiredCD@CD@@2HA=007d20e0
// @ref ?IsLocal@CD@@2_NA=00850828

void __fastcall CD::Set_Required_CD(int cd)
{
    RequiredCD = -2;
    if (IsLocal != true) {
        RequiredCD = cd;
    }
}
