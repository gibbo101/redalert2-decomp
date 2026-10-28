// int Taunt_Play(int taunt) (0x00715FB0): plays taunt number 1..8 (low four
// bits) of a side (next four bits, 0..8) on the taunt stream (name hypothesis).
#include "shared/vox_speech.hpp"
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
// @ref ?unknown_taunt_stream_ad0968@@3PAUAudioStreamPlayer@@A=00ad0968
// @ref ?unknown_count_ad0910@@3HC=00ad0910
// @ref ?Audio_Stream_Open@@YIHPAUAudioStreamPlayer@@PBDH@Z=00407a90
// @ref ??_C@_0BF@PCKC@taunts?2tauam?$CF02i?4wav?$AA@=007f9d18
// @ref ??_C@_0BF@BHKE@taunts?2tauko?$CF02i?4wav?$AA@=007f9d00
// @ref ??_C@_0BF@CENG@taunts?2taufr?$CF02i?4wav?$AA@=007f9ce8
// @ref ??_C@_0BF@MAGO@taunts?2tauge?$CF02i?4wav?$AA@=007f9cd0
// @ref ??_C@_0BF@BLNP@taunts?2taubr?$CF02i?4wav?$AA@=007f9cb8
// @ref ??_C@_0BF@DFFL@taunts?2tauli?$CF02i?4wav?$AA@=007f9ca0
// @ref ??_C@_0BF@PFIL@taunts?2tauir?$CF02i?4wav?$AA@=007f9c88
// @ref ??_C@_0BF@NLOF@taunts?2taucu?$CF02i?4wav?$AA@=007f9c70
// @ref ??_C@_0BF@KIAD@taunts?2tauru?$CF02i?4wav?$AA@=007f9c58

int __fastcall Taunt_Play(int taunt)
{
    char name[20];
    if (unknown_taunt_stream_ad0968 == 0 || unknown_count_ad0910 != 0) {
        return 0;
    }
    char number = (char)(taunt & 0xf);
    if (number < 1 || number > 8) {
        return 0;
    }
    switch ((taunt >> 4) & 0xf) {
    case 0:
        sprintf(name, "taunts\\tauam%02i.wav", number);
        break;
    case 1:
        sprintf(name, "taunts\\tauko%02i.wav", number);
        break;
    case 2:
        sprintf(name, "taunts\\taufr%02i.wav", number);
        break;
    case 3:
        sprintf(name, "taunts\\tauge%02i.wav", number);
        break;
    case 4:
        sprintf(name, "taunts\\taubr%02i.wav", number);
        break;
    case 5:
        sprintf(name, "taunts\\tauli%02i.wav", number);
        break;
    case 6:
        sprintf(name, "taunts\\tauir%02i.wav", number);
        break;
    case 7:
        sprintf(name, "taunts\\taucu%02i.wav", number);
        break;
    case 8:
        sprintf(name, "taunts\\tauru%02i.wav", number);
        break;
    default:
        return 0;
    }
    return Audio_Stream_Open(unknown_taunt_stream_ad0968, name, 0);
}
