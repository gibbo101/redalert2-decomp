// void __fastcall Audio_Report_Usage(void (__fastcall *report)(char *text)) -- 0x00406770
// Hands the callback two lines: the audio event count against its maximum and
// the static sound count against its maximum (nothing before the event bank exists).
#include "shared/audio.hpp"
// @ref ?Audio_Static_Sound_Count@@3HA=00ad0848
// @ref ?Audio_Static_Sound_Maximum@@3HA=00ad084c
// @ref ??_C@_0BP@BEKK@AudioEvents?5?3?5?$CF05d?5?9?5Max?3?5?$CF05d?$AA@=007ccd1c
// @ref ??_C@_0BP@ELKE@StaticSounds?3?5?$CF05d?5?9?5Max?3?5?$CF05d?$AA@=007cccfc

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);

void __fastcall Audio_Report_Usage(void (__fastcall *report)(char *text))
{
    char text[200];
    if (Audio_Event_Bank != 0) {
        sprintf(text, "AudioEvents : %05d - Max: %05d", Audio_Event_Count, Audio_Event_Maximum);
        report(text);
        sprintf(text, "StaticSounds: %05d - Max: %05d", Audio_Static_Sound_Count, Audio_Static_Sound_Maximum);
        report(text);
    }
}
