// Selection::Selection(rc_ptr<Campaign> const &campaign, int faction) (0x0072D560)
// @ref ??_E?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ?Load@INIClass@@QAEHAAVFileClass@@_N@Z=0050bbe0
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??0GenericNode@@QAE@XZ=0040e160
// @ref ?Link@GenericNode@@QAEXPAV1@@Z=0040e180
// @ref ??_7INIClass@@6B@=007a2b34
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??0?$VectorClass@PAVMSSfxEntry@@@@QAE@IPBQAVMSSfxEntry@@@Z=007304c0
// @ref ??_C@_06KPLP@SOUNDS?$AA@=007fc338
// @ref ??_C@_07GPLM@LAYOUTS?$AA@=007fc330
// @ref ??_C@_08MJDF@TXT_BACK?$AA@=007fc304
// @ref ??_C@_0L@JFM@WDTMAP?4INI?$AA@=007fc34c
// @ref ??_C@_0L@OOLB@VoiceOvers?$AA@=007fc340
// @ref ??_C@_0M@LADB@GUI?3PlayWDT?$AA@=007fc310
// @ref ?Load@Map@WorldDominationTour@@QAEXAAVINIClass@@PAVMSEngine@@_N@Z=00729510
// @ref ?unknown_color_a733e4@@3HA=00a733e4
// @ref ??_C@_00A@?$AA@=0083c55c
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
#include "shared/text_print.hpp"
#include "shared/hicolor.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/string_table.hpp"
extern int unknown_color_a733e4;
namespace WorldDominationTour {
Selection::Selection(rc_ptr<Campaign> const &campaign, int faction) :
    TheCampaign(campaign),
    TheVoices(campaign->Player_Faction()),
    Escaped(false),
    LastMouse(-1, -1),
    unknown_450(campaign->Properties->Last_Conflict()),
    unknown_454(-1),
    TheMap(Map::Create(campaign->Properties->unknown_14(), faction, campaign->Player_Faction())),
    unknown_460(-1),
    TargetPalette(0),
    ZoomingTarget(0),
    Target(0),
    TargetDividingFrame(32),
    Description(0),
    Tooltip(0),
    unknown_484(new MSFont(false)),
    unknown_488(State::Create()),
    ThemeName((char const *)0)
{
    int color = unknown_color_a733e4;
    int pixel = Build_Hicolor_Pixel((unsigned char)color, (unsigned char)((unsigned short)color >> 8), (unsigned char)(color >> 16));
    OldFontColor = BitFont->Set_Color(pixel) & 0xFFFF;
    Add_Anim(TheVoices.Create_Anim());
    CCFileClass file("WDTMAP.INI");
    INIClass ini;
    ini.Load(file);
    Load_Voices(ini, "VoiceOvers");
    Load_Sounds(ini, "SOUNDS");
    Wstring layout;
    ini.Get_String("LAYOUTS", Int_To_Wstring(campaign->Properties->unknown_72d2a0()), "", layout);
    Load_Layout(ini, layout);
    TheMap->Load(ini, this, campaign->Progress_Differs(faction));
    WideString play_text(StringTable::Load_String("GUI:PlayWDT", 0, "D:\\Ra2\\WDTSel.cpp", 157));
    MSBitPrintAnim *play = new MSBitPrintAnim(play_text, TheMap->Get_Play_Rect(), true);
    play->Set_Unknown_30(true);
    Add_Anim(play);
    WideString back_text(StringTable::Load_String("TXT_BACK", 0, "D:\\Ra2\\WDTSel.cpp", 164));
    MSBitPrintAnim *back = new MSBitPrintAnim(back_text, TheMap->Get_Back_Rect(), true);
    back->Set_Unknown_30(true);
    Add_Anim(back);
    Start_Theme();
}
}
