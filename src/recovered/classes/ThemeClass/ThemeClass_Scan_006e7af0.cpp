// void ThemeClass::Scan() (0x006E7AF0)
// Marks each theme whose .WAV file exists as available and measures its
// length in seconds.
#define THEME_CONTROL_RECORD
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#endif
#include "shared/vector_class.hpp"
#include "shared/theme.hpp"
#include "shared/audio.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/sound_available.hpp"
// @ref ?unknown_sound_enabled_a40c18@@3DA=00a40c18
// @ref ?unknown_flag_a40d0c@@3DA=00a40d0c
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref __makepath=007831f0
// @ref ??_C@_04KFC@?4WAV?$AA@=007f8338
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?Audio_Format_Init@@YIXPAUAudioFormat@@@Z=004084c0
// @ref ?Audio_Format_Read_Wave@@YIHPAVFileClass@@PAUAudioFormat@@PAH@Z=00408530
// @ref ?Time_For_Bytes@AudioFormat@@QAI_KH@Z=00408480
// @ref __aulldiv=00782580

extern char unknown_sound_enabled_a40c18;
extern char unknown_flag_a40d0c;
extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

void ThemeClass::Scan()
{
    if (unknown_sound_enabled_a40c18 && unknown_check_406f30() && !unknown_flag_a40d0c) {
        for (int theme = 0; theme < Themes.Count(); theme++) {
            char name[512];
            _makepath(name, 0, 0, Themes[theme]->Sound, ".WAV");
            CCFileClass file(name);
            Themes[theme]->Available = file.Is_Available();
            if (Themes[theme]->Available) {
                AudioFormat format;
                Audio_Format_Init(&format);
                file.Open(1);
                int size;
                if (Audio_Format_Read_Wave(&file, &format, &size)) {
                    Themes[theme]->Duration = (int)(format.Time_For_Bytes(size) / 1000);
                }
            }
        }
    }
}
