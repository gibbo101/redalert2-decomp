// void UnknownOptions_00670730::unknown_save_chat_options() -- 0x00670730
// Purpose: writes the WOL/LAN taunt and scroll-text switches (+0x1E89,
// +0x1E88, +0x1F71, +0x1F70) to [MultiPlayer] of the INI object at
// 0x00839740 and saves it to RA2.INI.
// Assumptions: the owner (a large options/session object) and the INI
// object's name are unidentified.
#include "shared/raw_file_class.hpp"
#include "shared/ccini_class.hpp"
// @ref ??0RawFileClass@@QAE@PBD@Z=00638b40
// @ref ??1RawFileClass@@UAE@XZ=00638ac0
// @ref ?Put_Bool@INIClass@@QAE_NPBD0_N@Z=0050f380
// @ref ?Save@CCINIClass@@QAEHAAVFileClass@@_N@Z=004698f0
// @ref ?unknown_ini_839740@@3VCCINIClass@@A=00839740
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8
// @ref ??_C@_0M@MLEF@MultiPlayer?$AA@=007dbce4
// @ref ??_C@_09KHPG@WOLTaunts?$AA@=007f3644
// @ref ??_C@_09HLFF@LANTaunts?$AA@=007f3638
// @ref ??_C@_0O@NDBO@WOLScrollText?$AA@=007f3628
// @ref ??_C@_0O@GLCN@LANScrollText?$AA@=007f3618

extern CCINIClass unknown_ini_839740;

struct UnknownOptions_00670730 {
    char unknown_0000[0x1E88];
    bool LANTaunts;                         // +0x1E88
    bool WOLTaunts;                         // +0x1E89
    char unknown_1e8a[0x1F70 - 0x1E8A];
    bool LANScrollText;                     // +0x1F70
    bool WOLScrollText;                     // +0x1F71
    void unknown_save_chat_options();
};

void UnknownOptions_00670730::unknown_save_chat_options()
{
    RawFileClass file("RA2.INI");
    unknown_ini_839740.Put_Bool("MultiPlayer", "WOLTaunts", WOLTaunts);
    unknown_ini_839740.Put_Bool("MultiPlayer", "LANTaunts", LANTaunts);
    unknown_ini_839740.Put_Bool("MultiPlayer", "WOLScrollText", WOLScrollText);
    unknown_ini_839740.Put_Bool("MultiPlayer", "LANScrollText", LANScrollText);
    unknown_ini_839740.Save(file, false);
}
