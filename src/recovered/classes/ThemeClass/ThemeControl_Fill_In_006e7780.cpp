// bool ThemeControl::Fill_In(CCINIClass const &ini) (0x006E7780)
// Reads the theme's section: the sound file (leading '$' and '#' dropped),
// scenario, normal and repeat flags, side and, for a normal theme, its
// display name.
#define THEME_CONTROL_RECORD
#include "shared/theme.hpp"
#include "shared/ccini_class.hpp"
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_05NJPO@Sound?$AA@=007f8318
// @ref ??_C@_06NPIB@Repeat?$AA@=007f8310
// @ref ??_C@_08DFKC@Scenario?$AA@=007d145c
// @ref ??_C@_06BILL@Normal?$AA@=007d1b30
// @ref ??_C@_04LJDI@Side?$AA@=007cdd8c
// @ref ??_C@_04EFNI@Name?$AA@=007ce2a4
// @ref ?Find_Section@INIClass@@QBEPAUINISection@1@PBD@Z=0050c9b0
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref ?Get_Int@INIClass@@QBEHPBD0H@Z=0050d7f0
// @ref ?Get_Bool@INIClass@@QBE_NPBD0_N@Z=0050f410
// @ref ?Get_Side@CCINIClass@@QBEHPBD0H@Z=0046ab30

extern "C" char *__cdecl strcpy(char *dest, char const *source);
#pragma intrinsic(strcpy)

bool ThemeControl::Fill_In(CCINIClass const &ini)
{
    if (ini.Is_Present(Name)) {
        ini.Get_String(Name, "Sound", "", Sound, sizeof(Sound));
        char *sound = Sound;
        while (*sound == '$' || *sound == '#') {
            sound++;
        }
        strcpy(Sound, sound);
        Scenario = ini.Get_Int(Name, "Scenario", Scenario);
        unknown_288 = ini.Get_Bool(Name, "Normal", unknown_288);
        unknown_289 = ini.Get_Bool(Name, "Repeat", unknown_289);
        Owner = ini.Get_Side(Name, "Side", Owner);
        if (unknown_288) {
            ini.Get_Wide_String(Name, "Name", FullName, sizeof(FullName) / sizeof(FullName[0]));
        }
        return true;
    }
    return false;
}
