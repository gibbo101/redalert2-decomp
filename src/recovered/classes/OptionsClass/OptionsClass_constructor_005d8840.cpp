// OptionsClass::OptionsClass() (0x005D8840)
// The default settings (RA2.INI overrides them in Load_Settings).
#include "shared/options.hpp"

OptionsClass::OptionsClass() :
    GameSpeed(3),
    Difficulty(1),
    ScrollMethod(0),
    ScrollRate(3),
    AutoScroll(true),
    DetailLevel(2),
    SidebarOn(true),
    SidebarCameoText(true),
    UnitActionLines(true),
    ShowHidden(false),
    ToolTips(true),
    ScreenWidth(-1),
    ScreenHeight(-1),
    StretchMovies(false),
    AllowHiResModes(false),
    AllowVRAMSidebar(false),
    SoundVolume(0.7f),
    VoiceVolume(1.0f),
    ScoreVolume(0.5f),
    IsScoreRepeat(false),
    InGameMusic(true),
    IsScoreShuffle(false),
    SoundLatency(9),
    Socket(0xFFFF),
    NetCard(0),
    KeyForceMove1(0x12),
    KeyForceMove2(0x12),
    KeyForceAttack1(0x11),
    KeyForceAttack2(0x11),
    KeySelect1(0x10),
    KeySelect2(0x10),
    KeyQueueMove1(0x51),
    KeyQueueMove2(0x51)
{
    UnlockedMovie[0] = -1;
    UnlockedMovie[1] = -1;
    DestNet[0] = 0;
}
