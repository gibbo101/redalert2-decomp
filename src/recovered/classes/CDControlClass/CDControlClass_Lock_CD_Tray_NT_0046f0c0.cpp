// bool CDControlClass::Lock_CD_Tray_NT(char drive) (0x0046F0C0)
// Windows NT: with the volume locked, prevents ejection of the media.
// False only when the volume cannot be opened.
#include "shared/cd_control.hpp"

bool CDControlClass::Lock_CD_Tray_NT(char drive)
{
    HANDLE volume = Open_Removable_Volume(drive);
    if (volume == INVALID_HANDLE_VALUE) {
        return false;
    }
    bool changed = false;   // computed but unused: the result is true either way
    if (Lock_Volume(volume) && Prevent_Removal_Of_Volume(volume, true)) {
        changed = true;
    }
    Unlock_Volume(volume);
    Close_Removable_Volume(volume);
    return true;
}
