// void OptionsClass::Save_Settings() (0x005D91B0)
// Writes the settings back to RA2.INI (NetID with inverted characters) and
// saves the file.
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_C@_05BHNM@Audio?$AA@=007e87b4
// @ref ??_C@_05COPE@NetID?$AA@=007e8768
// @ref ??_C@_05HAHE@Video?$AA@=007e8860
// @ref ??_C@_06BHPO@Socket?$AA@=007e871c
// @ref ??_C@_07BFAH@Options?$AA@=007dae94
// @ref ??_C@_07GNMG@NetCard?$AA@=007e8714
// @ref ??_C@_07HKHC@Network?$AA@=007e8760
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8
// @ref ??_C@_07OPOK@DestNet?$AA@=007e870c
// @ref ??_C@_08FDMF@ToolTips?$AA@=007e8888
// @ref ??_C@_09OAAF@GameSpeed?$AA@=007e89c0
// @ref ??_C@_0BA@CDGE@UnitActionLines?$AA@=007e88c8
// @ref ??_C@_0BB@FMGO@SidebarCameoText?$AA@=007e88ec
// @ref ??_C@_0BG@OKEL@Saving?5game?5settings?6?$AA@=007e8a0c
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
// @ref ??_C@_0P@DCKB@IsScoreShuffle?$AA@=007e877c
// @ref ??_C@_1M@LKON@?$AA?$CF?$AAd?$AA?5?$AA?$CF?$AAd?$AA?$AA@=007e8a00
// @ref ?Put_Unicode@INIClass@@QAE_NPBD0PBG@Z=0050ecf0
// @ref ?Setup_Network@OptionsClass@@QAEXXZ=005d94d0
// @ref ?unknown_5d94d0@OptionsClass@@QAEXXZ=005d94d0
#include "shared/options.hpp"
#include "shared/debug_printf.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/string_table.hpp"

void OptionsClass::Save_Settings()
{
    CCFileClass file("RA2.INI");
    Debug_Printf("Saving game settings\n");

    unknown_ini_839740.Put_Int("Options", "GameSpeed", GameSpeed);
    unknown_ini_839740.Put_Int("Options", "Difficulty", Difficulty);
    unknown_ini_839740.Put_Int("Options", "ScrollMethod", ScrollMethod);
    unknown_ini_839740.Put_Int("Options", "ScrollRate", ScrollRate);
    unknown_ini_839740.Put_Bool("Options", "AutoScroll", AutoScroll);
    unknown_ini_839740.Put_Int("Options", "DetailLevel", DetailLevel);
    unknown_ini_839740.Put_Bool("Options", "SidebarCameoText", SidebarCameoText);
    unknown_ini_839740.Put_Bool("Options", "UnitActionLines", UnitActionLines);
    unknown_ini_839740.Put_Bool("Options", "ShowHidden", ShowHidden);
    unknown_ini_839740.Put_Bool("Options", "ToolTips", ToolTips);

    unknown_ini_839740.Put_Int("Video", "ScreenWidth", ScreenWidth);
    unknown_ini_839740.Put_Int("Video", "ScreenHeight", ScreenHeight);
    unknown_ini_839740.Put_Bool("Video", "StretchMovies", StretchMovies);

    unknown_ini_839740.Put_Double("Audio", "SoundVolume", SoundVolume);
    unknown_ini_839740.Put_Double("Audio", "VoiceVolume", VoiceVolume);
    unknown_ini_839740.Put_Double("Audio", "ScoreVolume", ScoreVolume);
    unknown_ini_839740.Put_Bool("Audio", "IsScoreRepeat", IsScoreRepeat);
    unknown_ini_839740.Put_Bool("Audio", "IsScoreShuffle", IsScoreShuffle);
    unknown_ini_839740.Put_Int("Audio", "SoundLatency", SoundLatency);
    unknown_ini_839740.Put_Bool("Audio", "InGameMusic", InGameMusic);

    unknown_ini_839740.Put_Int("Network", "Socket", Socket);
    unknown_ini_839740.Put_Int("Network", "NetCard", NetCard);
    unknown_ini_839740.Put_String("Network", "DestNet", DestNet);
    unsigned short buffer[200];
    swprintf(buffer, L"%d %d", UnlockedMovie[0] + 1, UnlockedMovie[1] + 1);
    for (unsigned short *letter = buffer; *letter != 0; letter++) {
        *letter = ~*letter;
        if (*letter == 0) {
            *letter = 0xFFFF;
        }
    }
    unknown_ini_839740.Put_Unicode("Network", "NetID", buffer);

    unknown_ini_839740.Save(file, false);
    Setup_Network();
}
