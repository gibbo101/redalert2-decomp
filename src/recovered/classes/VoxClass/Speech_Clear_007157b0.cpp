// void Speech_Clear() (0x007157B0): drops every waiting speech, marking its
// VoxClass idle (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_vox_list_ad0868@@3UAudioListNode@@A=00ad0868
// @ref ?unknown_vox_list_ad0890@@3UAudioListNode@@A=00ad0890
// @ref ?unknown_vox_lists_ad08e0@@3PAUAudioListNode@@A=00ad08e0
// @ref ?unknown_vox_pending_ad0948@@3PAUVoxSpeech@@A=00ad0948
// @ref ?unknown_vox_enabled_ad094c@@3HA=00ad094c

void Speech_Clear()
{
    if (!unknown_vox_enabled_ad094c) {
        return;
    }
    if (unknown_vox_pending_ad0948 != 0) {
        unknown_vox_pending_ad0948->Vox->State = 2;
        delete unknown_vox_pending_ad0948;
        unknown_vox_pending_ad0948 = 0;
    }
    VoxSpeech *speech;
    while ((speech = (VoxSpeech *)Audio_List_First(&unknown_vox_list_ad0890)) != 0) {
        Audio_List_Remove(speech);
        speech->Vox->State = 2;
        delete speech;
    }
    while ((speech = (VoxSpeech *)Audio_List_First(&unknown_vox_list_ad0868)) != 0) {
        Audio_List_Remove(speech);
        speech->Vox->State = 2;
        delete speech;
    }
    for (int i = 0; i < 4; i++) {
        while ((speech = (VoxSpeech *)Audio_List_First(&unknown_vox_lists_ad08e0[i])) != 0) {
            Audio_List_Remove(speech);
            speech->Vox->State = 2;
            delete speech;
        }
    }
}
