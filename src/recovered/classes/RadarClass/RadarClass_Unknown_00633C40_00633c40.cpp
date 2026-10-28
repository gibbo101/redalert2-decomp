// void RadarClass::Unknown_00633C40() (0x00633C40)
// The mode-4 (transmission) update: state +0x14B4 0 starts the voice
// sequence, 1 waits for it (fading the audio streams while 0x00AF8FE8 is
// set), 2 waits for the fade, then switches to mode 3 and plays the sound.
#include "shared/radar.hpp"
#include "shared/rules.hpp"
// @ref ?Unknown_00633000@RadarClass@@QAEXH_N@Z=00633000
// @ref ?Unknown_00406100@UnknownList14BC@@QAIXPAUAudioEvent@@PAUAudioEventType@@@Z=00406100
// @ref ?Unknown_004082B0@@YAXXZ=004082b0
// @ref ?Unknown_00408330@@YAHXZ=00408330
// @ref ?Unknown_005A0B10@@YAXXZ=005a0b10
// @ref ?Unknown_00716690@@YI_NH@Z=00716690
// @ref ?Unknown_00716940@@YAXXZ=00716940
// @ref ?Unknown_00716950@@YAXXZ=00716950
// @ref ?unknown_int_af8fe8@@3HA=00af8fe8
// @ref ?unknown_set_frame_rate_0053d820@@YIXH@Z=0053d820

void RadarClass::Unknown_00633C40()
{
    switch (unknown_14b4) {
    case 0:
        Speech_Clear();
        Speech_Play(unknown_14d0, 0, 3);
        Unknown_00716940();
        unknown_14b4 = 1;
        break;
    case 1:
        if (Unknown_00716690(unknown_14d0)) {
            if (unknown_int_af8fe8 != 0) {
                Unknown_004082B0();
            }
            unknown_14b4 = 2;
        }
        break;
    case 2:
        if (unknown_int_af8fe8 != 0) {
            if (Unknown_00408330() == 0) {
                return;
            }
            if (unknown_int_af8fe8 != 0) {
                Unknown_00716950();
                Unknown_005A0B10();
            }
        }
        Unknown_00633000(3, false);
        unknown_14bc.Unknown_00406070();
        unknown_14bc.Unknown_00406100(Voc_Play(Rules->unknown_618, 1.0f, 0x2000, 0), 0);
        unknown_set_frame_rate_0053d820(Rules->DetailMinFrameRateMovie);
        break;
    }
}
