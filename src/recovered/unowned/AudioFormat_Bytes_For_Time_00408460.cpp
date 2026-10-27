// int AudioFormat::Bytes_For_Time(__int64 milliseconds) -- 0x00408460
// Purpose: the number of bytes playing for milliseconds lasts.
#include "shared/audio.hpp"

int AudioFormat::Bytes_For_Time(__int64 milliseconds)
{
    return BytesPerSecond * (int)milliseconds / 1000;
}
