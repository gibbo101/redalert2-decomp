// int AudioTimeSpan::Is_Due(__int64 now) (0x004038E0)
// Whether a full period (+0x00) has passed since the last tick (+0x28),
// compared unsigned.
#include "shared/audio.hpp"

int AudioTimeSpan::Is_Due(__int64 now)
{
    if ((unsigned __int64)(now - LastTime) < (unsigned __int64)unknown_00) {
        return 0;
    }
    return 1;
}
