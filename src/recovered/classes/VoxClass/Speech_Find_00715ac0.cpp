// VoxSpeech *Speech_Find(VoxClass *vox) (0x00715AC0): the waiting speech of a
// VoxClass: the priority 3 list, the pending speech, the type 1 lists from
// priority 3 down, then the type 3 list; 0 for none (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_vox_list_ad0868@@3UAudioListNode@@A=00ad0868
// @ref ?unknown_vox_list_ad0890@@3UAudioListNode@@A=00ad0890
// @ref ?unknown_vox_lists_ad08e0@@3PAUAudioListNode@@A=00ad08e0
// @ref ?unknown_vox_pending_ad0948@@3PAUVoxSpeech@@A=00ad0948

VoxSpeech *__fastcall Speech_Find(VoxClass *vox)
{
    VoxSpeech *speech;
    for (speech = (VoxSpeech *)Audio_List_First(&unknown_vox_list_ad0890); speech != 0;
            speech = (VoxSpeech *)Audio_List_Next(speech)) {
        if (speech->Vox == vox) {
            return speech;
        }
    }
    if (unknown_vox_pending_ad0948 != 0 && unknown_vox_pending_ad0948->Vox == vox) {
        return unknown_vox_pending_ad0948;
    }
    for (int priority = 3; priority >= 0; priority--) {
        for (speech = (VoxSpeech *)Audio_List_First(&unknown_vox_lists_ad08e0[priority]); speech != 0;
                speech = (VoxSpeech *)Audio_List_Next(speech)) {
            if (speech->Vox == vox) {
                return speech;
            }
        }
    }
    for (speech = (VoxSpeech *)Audio_List_First(&unknown_vox_list_ad0868); speech != 0;
            speech = (VoxSpeech *)Audio_List_Next(speech)) {
        if (speech->Vox == vox) {
            return speech;
        }
    }
    return 0;
}
