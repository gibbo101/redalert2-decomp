// void OptionsClass::Set() (0x005D95E0)
// Applies the current settings: volumes, score repeat/shuffle, sidebar cameo
// text and unit action lines (name after TS's OptionsClass::Set).
// @ref ??_C@_02HAKO@ON?$AA@=007e1f40
// @ref ??_C@_03CMJG@OFF?$AA@=007e1f3c
// @ref ??_C@_0BC@CPNP@SoundVolume?5?$DN?5?$CFf?6?$AA@=007e86b0
// @ref ??_C@_0BC@EMAN@VoiceVolume?5?$DN?5?$CFf?6?$AA@=007e86c4
// @ref ??_C@_0BC@MLDC@ScoreVolume?5?$DN?5?$CFf?6?$AA@=007e869c
// @ref ??_C@_0BD@OCJK@ScoreRepeat?5is?5?$CFs?6?$AA@=007e8688
// @ref ??_C@_0BE@JBIN@ScoreShuffle?5is?5?$CFs?6?$AA@=007e8674
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Set_Volume@ThemeClass@@QAEXH@Z=006e8590
// @ref ?Set_Volume@VoxClass@@SIXH@Z=00715ef0
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?Unknown_0067B880@SidebarClass@@QAEX_N@Z=0067b880
// @ref __ftol=0077f110
// @ref __real@4@400d8000000000000000=007a77ac
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@4006ff00000000000000=007a2f50
#include "shared/options.hpp"
#include "shared/techno.hpp"
#include "shared/map_view.hpp"

void OptionsClass::Set()
{
    Set_Sound_Volume(SoundVolume, false);
    Set_Voice_Volume(VoiceVolume, false);
    Set_Score_Volume(ScoreVolume, false);
    Set_Repeat(IsScoreRepeat);
    Set_Shuffle(IsScoreShuffle);
    Map.Unknown_0067B880(SidebarCameoText);
    TechnoClass::unknown_6d79c0(UnitActionLines);
}
