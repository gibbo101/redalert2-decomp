// int AnimFile::Get_Frame_Count() (0x00424370)
// The frame count; one less when the file ends with a delta back to the
// first frame.
#include "shared/anim_file.hpp"

int AnimFile::Get_Frame_Count()
{
    int count = Header.FrameCount;
    if (Header.HasLastDelta) {
        count--;
    }
    return count;
}
