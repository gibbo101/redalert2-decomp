// void Taunt_Unblock() (0x00716910): counts the taunt block down, not below 0.
#include "shared/vox_speech.hpp"
// @ref ?unknown_taunt_stream_ad0968@@3PAUAudioStreamPlayer@@A=00ad0968
// @ref ?unknown_count_ad0910@@3HC=00ad0910

void Taunt_Unblock()
{
    if (unknown_taunt_stream_ad0968 != 0) {
        if (--unknown_count_ad0910 < 0) {
            unknown_count_ad0910 = 0;
        }
    }
}
