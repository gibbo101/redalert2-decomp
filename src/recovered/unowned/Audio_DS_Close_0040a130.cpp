// void Audio_DS_Close() -- 0x0040A130
// Purpose: detaches the device from the mixing thread under the driver
// lock, then stops and releases the primary buffer.
// @ref ?Audio_Lock@@3UCRITICAL_SECTION@@A=00831590
// @ref ?Audio_Primary_Buffer@@3PAUIDirectSoundBuffer@@A=008315b0
// @ref ?Audio_Thread@@3UAudioThreadBlock@@A=00831560
#include "shared/audio.hpp"

void Audio_DS_Close()
{
    EnterCriticalSection(&Audio_Lock);
    Audio_Thread.Device = 0;
    LeaveCriticalSection(&Audio_Lock);
    if (Audio_Primary_Buffer != 0) {
        Audio_Primary_Buffer->Stop();
        Audio_Primary_Buffer->Release();
        Audio_Primary_Buffer = 0;
    }
}
