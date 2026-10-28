// void VoxClass::Set_Volume(int volume) (0x00715EF0): the speech volume, at
// most 255.
#include "shared/vox_speech.hpp"
// @ref ?unknown_vox_volume_7f9bd4@@3HA=007f9bd4

void __fastcall VoxClass::Set_Volume(int volume)
{
    unknown_vox_volume_7f9bd4 = volume;
    if (volume >= 255) {
        unknown_vox_volume_7f9bd4 = 255;
    }
}
