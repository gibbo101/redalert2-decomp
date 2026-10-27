// bool CDControlClass::Eject_CD(char drive) (0x0046EF00)
// Windows NT: opens the volume, locks and dismounts it, allows removal and
// ejects the media; true when the media was ejected.
#include "shared/cd_control.hpp"

bool CDControlClass::Eject_CD(char drive)
{
    bool ejected = false;
    HANDLE volume = Open_Removable_Volume(drive);
    if (volume == INVALID_HANDLE_VALUE) {
        return false;
    }
    if (Lock_Volume(volume) && Dismount_Volume(volume) && Prevent_Removal_Of_Volume(volume, false)
        && Auto_Eject_Volume(volume)) {
        ejected = true;
    }
    Close_Removable_Volume(volume);
    return ejected;
}
