// void ThemeClass::Unknown_006E7890(CCINIClass &ini) (0x006E7890)
// Tiberian Sun's Init_Themes: reads every theme listed under [Themes]
// (new records for unknown names), then opens the music stream.
#define THEME_CONTROL_RECORD
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#endif
#include "shared/vector_class.hpp"
#include "shared/theme.hpp"
#include "shared/audio.hpp"
#include "shared/ccini_class.hpp"
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_06PJBK@Themes?$AA@=007f8330
// @ref ??_C@_0N@ELFH@Music?5Stream?$AA@=007f8320
// @ref ?Fill_In@ThemeControl@@QAE_NABVCCINIClass@@@Z=006e7780
// @ref __stricmp=00781f20
// @ref ?Entry_Count@INIClass@@QBEHPBD@Z=0050cb00
// @ref ?Get_Entry@INIClass@@QBEPBDPBDH@Z=0050ce00
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref ?Audio_Get_Device@@YAPAUAudioDevice@@XZ=00406f40
// @ref ?Audio_Stream_Create@@YIPAUAudioStreamPlayer@@PAUAudioDevice@@_J@Z=00407790
// @ref ?Audio_Stream_Set_Name@@YIXPAUAudioStreamPlayer@@PBD@Z=00407fa0
// @ref ?Audio_Stream_Set_Levels_94@@YIXPAUAudioStreamPlayer@@PAUAudioLevelSet@@@Z=00407a70
// @ref ?Audio_Stream_Set_Levels_9c@@YIXPAUAudioStreamPlayer@@PAUAudioLevelSet@@@Z=00407a80
// @ref ?unknown_audio_levels_831454@@3PAUAudioLevelSet@@A=00831454
// @ref ?unknown_audio_levels_831464@@3PAUAudioLevelSet@@A=00831464

extern "C" char *__cdecl strcpy(char *dest, char const *source);
#pragma intrinsic(strcpy)

// Two of the eight global level sets (0x0083144C-0x00831468; shared/audio.hpp).
extern AudioLevelSet *unknown_audio_levels_831454;
extern AudioLevelSet *unknown_audio_levels_831464;

void ThemeClass::Unknown_006E7890(CCINIClass &ini)
{
    ThemeControl *ctrl;
    int count = ini.Entry_Count("Themes");
    for (int index = 0; index < count; index++) {
        char name[32];
        if (ini.Get_String("Themes", ini.Get_Entry("Themes", index), "", name, sizeof(name))) {
            ThemeType theme = From_Name(name);
            if (theme == THEME_NONE) {
                ctrl = new ThemeControl;
                strcpy(ctrl->Name, name);
                Themes.Add(ctrl);
            } else {
                ctrl = Themes[theme];
            }
            ctrl->Fill_In(ini);
        }
    }
    if (Audio_Get_Device() != 0) {
        Sample = Audio_Stream_Create(Audio_Get_Device(), 20000);
        if (Sample != 0) {
            Audio_Stream_Set_Name((AudioStreamPlayer *)Sample, "Music Stream");
            Audio_Stream_Set_Levels_94((AudioStreamPlayer *)Sample, unknown_audio_levels_831454);
            Audio_Stream_Set_Levels_9c((AudioStreamPlayer *)Sample, unknown_audio_levels_831464);
        }
    }
}
