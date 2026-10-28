// MultiplayerGameMode::MultiplayerGameMode(...) (0x005B6CD0)
// A mode with its name and description, its INI file (read into a new
// CCINIClass when present) and id; [MultiplayerDialogSettings]
// WonlineTournamentAllowed of that INI sets unknown_3c (default 1).
#include "shared/multiplayer_game_mode.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
// @ref _unknown_section_7a7170=007a7170
// @ref ??_C@_0BK@IOIK@MultiplayerDialogSettings?$AA@=007e5f04
// @ref ??0?$List@PAUINISection@INIClass@@@@QAE@XZ=00490ff0
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??_7?$DynamicVectorClass@PAVMultiplayerTeam@@@@6B@=007a7270
// @ref ??_C@_0BJ@NIJN@WonlineTournamentAllowed?$AA@=007e6008
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940

// The section name, a file-static pointer of the unit's data (0x007A7170).
static char const * const unknown_section_7a7170 = "MultiplayerDialogSettings";

MultiplayerGameMode::MultiplayerGameMode(WideString const &name, WideString const &description,
                                         Wstring const &ini_name, Wstring const &unknown_4, bool unknown_5,
                                         int id) :
    unknown_name_20(name),
    unknown_name_24(description),
    unknown_28(id),
    unknown_2c(ini_name),
    unknown_30(unknown_4),
    unknown_34(unknown_5),
    unknown_ini_38(0)
{
    unknown_04 = false;
    unknown_3c = 1;
    unknown_ini_38 = new CCINIClass;
    {
        CCFileClass file(unknown_2c);
        if (file.Is_Available()) {
            unknown_ini_38->Load(file, false);
        }
    }
    if (unknown_ini_38 != 0 && unknown_ini_38->Is_Present(unknown_section_7a7170)) {
        unknown_3c = unknown_ini_38->Get_Int(unknown_section_7a7170, "WonlineTournamentAllowed", unknown_3c);
    }
}
