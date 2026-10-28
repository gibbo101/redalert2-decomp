// void Speech_Queue(VoxClass *vox, int type, int priority) (0x007159D0): a new
// speech node: type 3 and type 1 (by priority) and priority 3 speeches wait
// in their lists; any other is kept as the one pending speech when nothing
// else waits and it outranks the pending one, else dropped (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?unknown_vox_list_ad0868@@3UAudioListNode@@A=00ad0868
// @ref ?unknown_vox_list_ad0890@@3UAudioListNode@@A=00ad0890
// @ref ?unknown_vox_lists_ad08e0@@3PAUAudioListNode@@A=00ad08e0
// @ref ?unknown_vox_pending_ad0948@@3PAUVoxSpeech@@A=00ad0948
// @ref ?unknown_vox_serial_ad0950@@3HA=00ad0950

void __fastcall Speech_Queue(VoxClass *vox, int type, int priority)
{
    VoxSpeech *speech = new VoxSpeech;
    Audio_List_Init_Node(speech);
    speech->Vox = vox;
    speech->Priority = priority;
    speech->Type = type;
    speech->Serial = unknown_vox_serial_ad0950 % 100;
    unknown_vox_serial_ad0950++;
    vox->State = 1;
    if (type == 3) {
        Audio_List_Add_Tail(&unknown_vox_list_ad0868, speech);
    } else if (type == 1) {
        Audio_List_Add_Tail(&unknown_vox_lists_ad08e0[priority], speech);
    } else if (priority == 3) {
        Audio_List_Add_Tail(&unknown_vox_list_ad0890, speech);
    } else if (unknown_vox_list_ad0868.Prev == &unknown_vox_list_ad0868
            && unknown_vox_list_ad0890.Prev == &unknown_vox_list_ad0890
            && (unknown_vox_pending_ad0948 == 0 || unknown_vox_pending_ad0948->Priority < priority)) {
        unknown_vox_pending_ad0948 = speech;
    } else {
        vox->State = 2;
        delete speech;
    }
}
