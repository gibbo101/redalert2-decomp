// void OptionsClass::Load_Settings() (0x005D8B00)
// Reads the settings from RA2.INI ([Options], [Video], [Audio], [Network]),
// clamping the difficulty (0-4), detail level (0-2) and volumes (at most 1)
// and logging each; NetID holds two numbers stored with inverted characters.
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_02HAKO@ON?$AA@=007e1f40
// @ref ??_C@_03CMJG@OFF?$AA@=007e1f3c
// @ref ??_C@_05BHNM@Audio?$AA@=007e87b4
// @ref ??_C@_05COPE@NetID?$AA@=007e8768
// @ref ??_C@_05HAHE@Video?$AA@=007e8860
// @ref ??_C@_05JCNK@RIGHT?$AA@=007e8910
// @ref ??_C@_06BHPO@Socket?$AA@=007e871c
// @ref ??_C@_07BFAH@Options?$AA@=007dae94
// @ref ??_C@_07GNMG@NetCard?$AA@=007e8714
// @ref ??_C@_07HKHC@Network?$AA@=007e8760
// @ref ??_C@_07OPOK@DestNet?$AA@=007e870c
// @ref ??_C@_08FDMF@ToolTips?$AA@=007e8888
// @ref ??_C@_09OAAF@GameSpeed?$AA@=007e89c0
// @ref ??_C@_0BA@CDGE@UnitActionLines?$AA@=007e88c8
// @ref ??_C@_0BA@EOHF@AllowModeToggle?$AA@=007e87dc
// @ref ??_C@_0BA@HFAB@AllowHiResModes?$AA@=007e8800
// @ref ??_C@_0BA@JBIP@GameSpeed?5?$DN?5?$CFd?6?$AA@=007e89b0
// @ref ??_C@_0BB@DDEA@Difficulty?5?$DN?5?$CFd?6?$AA@=007e8990
// @ref ??_C@_0BB@FMGO@SidebarCameoText?$AA@=007e88ec
// @ref ??_C@_0BB@HANG@AllowVRAMSidebar?$AA@=007e87c8
// @ref ??_C@_0BB@JJCE@ToolTips?5are?5?$CFs?6?$AA@=007e8874
// @ref ??_C@_0BB@LGCL@ScrollRate?5?$DN?5?$CFd?6?$AA@=007e894c
// @ref ??_C@_0BC@CPNP@SoundVolume?5?$DN?5?$CFf?6?$AA@=007e86b0
// @ref ??_C@_0BC@EMAN@VoiceVolume?5?$DN?5?$CFf?6?$AA@=007e86c4
// @ref ??_C@_0BC@FPEC@ShowHidden?5is?5?$CFs?6?$AA@=007e8894
// @ref ??_C@_0BC@HPPL@AllowHiRes?5is?5?$CFs?6?$AA@=007e87ec
// @ref ??_C@_0BC@JNMK@AutoScroll?5is?5?$CFs?6?$AA@=007e892c
// @ref ??_C@_0BC@MLDC@ScoreVolume?5?$DN?5?$CFf?6?$AA@=007e869c
// @ref ??_C@_0BC@OKJP@DetailLevel?5?$DN?5?$CFd?6?$AA@=007e8918
// @ref ??_C@_0BD@FKHC@ScrollMethod?5?$DN?5?$CFd?6?$AA@=007e896c
// @ref ??_C@_0BD@OCJK@ScoreRepeat?5is?5?$CFs?6?$AA@=007e8688
// @ref ??_C@_0BE@EJCO@Sidebar?5Text?5is?5?$CFs?6?$AA@=007e88d8
// @ref ??_C@_0BE@JBIN@ScoreShuffle?5is?5?$CFs?6?$AA@=007e8674
// @ref ??_C@_0BE@PON@ActionLines?5are?5?$CFs?6?$AA@=007e88b4
// @ref ??_C@_0BF@MACC@StretchMovies?5is?5?$CFs?6?$AA@=007e8810
// @ref ??_C@_0BG@KDGG@Resolution?5?$DN?5?$CFd?5X?5?$CFd?6?$AA@=007e8838
// @ref ??_C@_0CK@NH@Emulated?5sound?5card?5latency?5defa@=007e8724
// @ref ??_C@_0DE@DFEE@?9?9?9?9?9?9?9?9?9?5Complete?5?9?9?9?9?9?9?9?9?9?9?9?9?9@=007e86d8
// @ref ??_C@_0DE@FEPI@?9?9?9?9?9?9?9?9?9?5Loading?5SUN?4INI?5settin@=007e89cc
// @ref ??_C@_0L@BKMH@ScrollRate?$AA@=007e8960
// @ref ??_C@_0L@FHFF@ShowHidden?$AA@=007e88a8
// @ref ??_C@_0L@IHH@Difficulty?$AA@=007e89a4
// @ref ??_C@_0L@NNFH@AutoScroll?$AA@=007e8940
// @ref ??_C@_0M@DKIB@ScoreVolume?$AA@=007e879c
// @ref ??_C@_0M@EHL@SoundVolume?$AA@=007e87bc
// @ref ??_C@_0M@HMFN@VoiceVolume?$AA@=007e87a8
// @ref ??_C@_0M@KHJK@ScreenWidth?$AA@=007e8868
// @ref ??_C@_0M@KPPM@InGameMusic?$AA@=007e8770
// @ref ??_C@_0M@PNCF@DetailLevel?$AA@=007cef14
// @ref ??_C@_0N@LDPM@SoundLatency?$AA@=007e8750
// @ref ??_C@_0N@NAHG@ScrollMethod?$AA@=007e8980
// @ref ??_C@_0N@PIKM@ScreenHeight?$AA@=007e8850
// @ref ??_C@_0O@CEPG@IsScoreRepeat?$AA@=007e878c
// @ref ??_C@_0O@INAO@StretchMovies?$AA@=007e8828
// @ref ??_C@_0P@CPDH@SideBar?5on?5?$CFs?6?$AA@=007e8900
// @ref ??_C@_0P@DCKB@IsScoreShuffle?$AA@=007e877c
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ?Get_Unicode@INIClass@@QBEHPBD0PBGPAGH@Z=0050edf0
// @ref ?Set@AudioLevel@@QAIXH@Z=00407080
// @ref ?Set_Volume@ThemeClass@@QAEXH@Z=006e8590
// @ref ?Set_Volume@VoxClass@@SIXH@Z=00715ef0
// @ref ?Setup_Network@OptionsClass@@QAEXXZ=005d94d0
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?Unknown_0067B880@SidebarClass@@QAEX_N@Z=0067b880
// @ref ?unknown_5d94d0@OptionsClass@@QAEXXZ=005d94d0
// @ref ?unknown_allow_mode_toggle_a40d0b@@3_NA=00a40d0b
// @ref __ftol=0077f110
// @ref __real@4@400d8000000000000000=007a77ac
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@4006ff00000000000000=007a2f50
// @ref _wcstok=00784b11
#include "shared/options.hpp"
#include "shared/debug_printf.hpp"
#include "shared/theme.hpp"
#include "shared/audio.hpp"
#include "shared/rules.hpp"
#include "shared/techno.hpp"
#include "shared/vox_class.hpp"
#include "shared/hicolor.hpp"
#include "shared/map_view.hpp"
#include "shared/crt_tokens.hpp"

void OptionsClass::Load_Settings()
{
    Debug_Printf("--------- Loading SUN.INI settings ---------------\n");

    GameSpeed = unknown_ini_839740.Get_Int("Options", "GameSpeed", GameSpeed);
    Debug_Printf("GameSpeed = %d\n", GameSpeed);
    Difficulty = unknown_ini_839740.Get_Int("Options", "Difficulty", Difficulty);
    Difficulty = Difficulty < 4 ? Difficulty : 4;
    Difficulty = Difficulty > 0 ? Difficulty : 0;
    Debug_Printf("Difficulty = %d\n", Difficulty);
    ScrollMethod = unknown_ini_839740.Get_Int("Options", "ScrollMethod", ScrollMethod);
    Debug_Printf("ScrollMethod = %d\n", ScrollMethod);
    ScrollRate = unknown_ini_839740.Get_Int("Options", "ScrollRate", ScrollRate);
    Debug_Printf("ScrollRate = %d\n", ScrollRate);
    AutoScroll = unknown_ini_839740.Get_Bool("Options", "AutoScroll", AutoScroll);
    Debug_Printf("AutoScroll is %s\n", AutoScroll == true ? "ON" : "OFF");
    DetailLevel = unknown_ini_839740.Get_Int("Options", "DetailLevel", DetailLevel);
    DetailLevel = DetailLevel < 2 ? DetailLevel : 2;
    DetailLevel = DetailLevel > 0 ? DetailLevel : 0;
    Debug_Printf("DetailLevel = %d\n", DetailLevel);
    SidebarOn = true;
    Debug_Printf("SideBar on %s\n", "RIGHT");
    SidebarCameoText = unknown_ini_839740.Get_Bool("Options", "SidebarCameoText", SidebarCameoText);
    Debug_Printf("Sidebar Text is %s\n", SidebarCameoText == true ? "ON" : "OFF");
    UnitActionLines = unknown_ini_839740.Get_Bool("Options", "UnitActionLines", UnitActionLines);
    Debug_Printf("ActionLines are %s\n", UnitActionLines == true ? "ON" : "OFF");
    ShowHidden = unknown_ini_839740.Get_Bool("Options", "ShowHidden", ShowHidden);
    Debug_Printf("ShowHidden is %s\n", ShowHidden == true ? "ON" : "OFF");
    ToolTips = unknown_ini_839740.Get_Bool("Options", "ToolTips", ToolTips);
    Debug_Printf("ToolTips are %s\n", ToolTips == true ? "ON" : "OFF");

    ScreenWidth = unknown_ini_839740.Get_Int("Video", "ScreenWidth", ScreenWidth);
    ScreenHeight = unknown_ini_839740.Get_Int("Video", "ScreenHeight", ScreenHeight);
    Debug_Printf("Resolution = %d X %d\n", ScreenWidth, ScreenHeight);
    StretchMovies = unknown_ini_839740.Get_Bool("Video", "StretchMovies", StretchMovies);
    StretchMovies = StretchMovies == true && AllowStretchBlits_852fd6 == true;
    Debug_Printf("StretchMovies is %s\n", StretchMovies == true ? "ON" : "OFF");
    AllowHiResModes = unknown_ini_839740.Get_Bool("Video", "AllowHiResModes", AllowHiResModes);
    Debug_Printf("AllowHiRes is %s\n", AllowHiResModes == true ? "ON" : "OFF");
    unknown_allow_mode_toggle_a40d0b = unknown_ini_839740.Get_Bool("Video", "AllowModeToggle", unknown_allow_mode_toggle_a40d0b);
    AllowVRAMSidebar = unknown_ini_839740.Get_Bool("Video", "AllowVRAMSidebar", AllowVRAMSidebar);

    Set_Sound_Volume(unknown_ini_839740.Get_Double("Audio", "SoundVolume", SoundVolume), false);
    Set_Voice_Volume(unknown_ini_839740.Get_Double("Audio", "VoiceVolume", VoiceVolume), false);
    Set_Score_Volume(unknown_ini_839740.Get_Double("Audio", "ScoreVolume", ScoreVolume), false);
    Set_Repeat(unknown_ini_839740.Get_Bool("Audio", "IsScoreRepeat", IsScoreRepeat));
    Set_Shuffle(unknown_ini_839740.Get_Bool("Audio", "IsScoreShuffle", IsScoreShuffle));
    InGameMusic = unknown_ini_839740.Get_Bool("Audio", "InGameMusic", InGameMusic);

    UnlockedMovie[0] = -1;
    UnlockedMovie[1] = -1;
    unsigned short buffer[200];
    unknown_ini_839740.Get_Unicode("Network", "NetID", unknown_empty_wide_839d4c, buffer, 200);
    if (buffer[0] != 0) {
        for (unsigned short *letter = buffer; *letter != 0; letter++) {
            *letter = ~*letter;
            if (*letter == 0) {
                *letter = 0xFFFF;
            }
        }
        unsigned short *token = wcstok(buffer, L" ");
        if (token != 0) {
            UnlockedMovie[0] = wcstol(token, 0, 10) - 1;
            token = wcstok(0, L" ");
            if (token != 0) {
                UnlockedMovie[1] = wcstol(token, 0, 10) - 1;
            }
        }
    }
    if (UnlockedMovie[0] < -1 || UnlockedMovie[0] >= 12) {
        UnlockedMovie[0] = -1;
    }
    if (UnlockedMovie[1] < -1 || UnlockedMovie[1] >= 12) {
        UnlockedMovie[1] = -1;
    }

    SoundLatency = unknown_ini_839740.Get_Int("Audio", "SoundLatency", SoundLatency);
    Debug_Printf("Emulated sound card latency default = %d\n", SoundLatency);
    Socket = unknown_ini_839740.Get_Int("Network", "Socket", Socket);
    NetCard = unknown_ini_839740.Get_Int("Network", "NetCard", NetCard);
    unknown_ini_839740.Get_String("Network", "DestNet", "", DestNet, sizeof(DestNet));
    Debug_Printf("--------- Complete -------------------------------\n");

    Map.Unknown_0067B880(SidebarCameoText);
    TechnoClass::unknown_6d79c0(UnitActionLines);
    Setup_Network();
}
