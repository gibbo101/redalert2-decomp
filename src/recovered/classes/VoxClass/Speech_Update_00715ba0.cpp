// void Speech_Update() (0x00715BA0): when the stream is free and the gap after the
// last speech has passed, starts the next waiting speech: a type 3 one, a
// priority 3 one, the pending one, then the first of the type 1 lists from
// priority 3 down. Its VoxClass's file (".WAV") is opened on the stream (name
// hypothesis).
#include "shared/vox_speech.hpp"
#include "shared/sound_available.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_flag_a40d0c@@3DA=00a40d0c
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?Audio_Now@@YI_JXZ=004092d0
// @ref ?unknown_vox_type_ad0858@@3HA=00ad0858
// @ref ?unknown_vox_list_ad0868@@3UAudioListNode@@A=00ad0868
// @ref ?unknown_vox_priority_ad0880@@3HA=00ad0880
// @ref ?unknown_vox_list_ad0890@@3UAudioListNode@@A=00ad0890
// @ref ?unknown_countdown_ad08c8@@3HC=00ad08c8
// @ref ?unknown_vox_lists_ad08e0@@3PAUAudioListNode@@A=00ad08e0
// @ref ?unknown_vox_pending_ad0948@@3PAUVoxSpeech@@A=00ad0948
// @ref ?unknown_vox_playing_ad0954@@3PAVVoxClass@@A=00ad0954
// @ref ?unknown_flag_ad0958@@3HA=00ad0958
// @ref ?unknown_vox_stream_ad095c@@3PAUAudioStreamPlayer@@A=00ad095c
// @ref ?unknown_vox_delay_ad0960@@3_KA=00ad0960
// @ref ??_C@_04KFC@?4WAV?$AA@=007f8338
// @ref ?Audio_Stream_Open@@YIHPAUAudioStreamPlayer@@PBDH@Z=00407a90

extern char unknown_flag_a40d0c;

void Speech_Update()
{
    if (unknown_flag_a40d0c || !unknown_check_406f30() || unknown_vox_stream_ad095c == 0
            || Audio_Stream_Is_Playing(unknown_vox_stream_ad095c)) {
        return;
    }
    if (Audio_Now() <= Audio_Stream_Stop_Time(unknown_vox_stream_ad095c) + unknown_vox_delay_ad0960) {
        return;
    }
    if (unknown_countdown_ad08c8 != 0) {
        return;
    }
    if (unknown_vox_playing_ad0954 != 0) {
        unknown_vox_playing_ad0954->State = 2;
        unknown_vox_playing_ad0954 = 0;
    }
    int type = 0;
    int priority = 0;
    VoxSpeech *speech = (VoxSpeech *)Audio_List_First(&unknown_vox_list_ad0868);
    if (speech != 0) {
        Audio_List_Remove(speech);
        if (unknown_vox_pending_ad0948 != 0) {
            delete unknown_vox_pending_ad0948;
            unknown_vox_pending_ad0948 = 0;
        }
    } else {
        speech = (VoxSpeech *)Audio_List_First(&unknown_vox_list_ad0890);
        if (speech != 0) {
            Audio_List_Remove(speech);
            if (unknown_vox_pending_ad0948 != 0) {
                delete unknown_vox_pending_ad0948;
                unknown_vox_pending_ad0948 = 0;
            }
        } else if (unknown_vox_pending_ad0948 != 0) {
            speech = unknown_vox_pending_ad0948;
            unknown_vox_pending_ad0948 = 0;
        } else {
            for (int i = 3; i >= 0; i--) {
                speech = (VoxSpeech *)Audio_List_First(&unknown_vox_lists_ad08e0[i]);
                if (speech != 0) {
                    break;
                }
            }
            if (speech != 0) {
                Audio_List_Remove(speech);
            }
        }
    }
    if (speech == 0) {
        return;
    }
    VoxClass *vox = speech->Vox;
    speech->Get(&type, &priority);
    delete speech;
    if (vox == 0) {
        return;
    }
    vox->State = 2;
    char filename[256];
    strcpy(filename, unknown_flag_ad0958 == 0 ? vox->Allied : vox->Russian);
    strcat(filename, ".WAV");
    if (Audio_Stream_Open(unknown_vox_stream_ad095c, filename, 1)) {
        unknown_vox_delay_ad0960 = 500;
        unknown_vox_playing_ad0954 = vox;
        unknown_vox_type_ad0858 = type;
        unknown_vox_priority_ad0880 = priority;
        vox->State = 0;
    }
}
