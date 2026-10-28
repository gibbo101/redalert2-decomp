// void Speech_Free_All() (0x00716590): stops the speech, drops the waiting
// ones and deletes every VoxClass (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_VoxClass_list_00ad0930@@3V?$DynamicVectorClass@PAVVoxClass@@@@A=00ad0930

void Speech_Free_All()
{
    Speech_Stop(true);
    while (unknown_VoxClass_list_00ad0930.Count() > 0) {
        delete unknown_VoxClass_list_00ad0930[0];
    }
}
