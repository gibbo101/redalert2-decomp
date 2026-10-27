// void CDControlClass::Force_CD_Eject(char drive) (0x0046EAA0)
// Ejects the CD in drive (0 = A:): through VWIN32 when the Windows 95 flag is
// set, else through the volume handle (Eject_CD, expanded inline).
// Assumes: the flag's meaning (hypothesis).
#include "shared/cd_control.hpp"
// @ref ?unknown_flag_839c4c@@3_NA=00839c4c
// @ref ?Eject_CD_Win95@CDControlClass@@QAEXD@Z=0046f3e0

void CDControlClass::Force_CD_Eject(char drive)
{
    if (unknown_flag_839c4c) {
        Eject_CD_Win95(drive);
    } else {
        Eject_CD(drive);
    }
}
