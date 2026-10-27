// unsigned __int64 __fastcall AudioFormat::Time_For_Bytes(int bytes) -- 0x00408480
// Purpose: the milliseconds bytes play for, or 0 without a rate.
// @ref __allmul=007820c0
// @ref __aulldiv=00782580
#include "shared/audio.hpp"

unsigned __int64 __fastcall AudioFormat::Time_For_Bytes(int bytes)
{
    if (BytesPerSecond != 0) {
        return (unsigned __int64)bytes * 1000 / BytesPerSecond;
    }
    return 0;
}
