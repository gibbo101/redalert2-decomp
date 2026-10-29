// WorldDominationTour::Selection (WDTSel.cpp, unit 0x0072D560-0x0073028F plus its COMDATs
// to 0x007304FF; header statics 0x0072D370): the campaign map screen of the World Domination
// Tour, where the player picks the next territory to attack. RTTI vtable 0x007AF36C, base
// MSEngine, size 0x4B0 (the stack object of 0x0072FF80). Layout from the constructor
// 0x0072D560 and destructor 0x0072D990; WDTMAP.INI supplies its sounds, layout and the
// voice-over thresholds. Member names other than the INI key names are hypotheses.
#ifndef RA2_SHARED_WDT_SELECTION_HPP
#define RA2_SHARED_WDT_SELECTION_HPP

#include "shared/wdt_campaign.hpp"
#include "shared/wdt_map.hpp"
#include "shared/wdt_voices.hpp"
#include "shared/ms_choice.hpp"
#include "shared/msfont.hpp"
#include "shared/theme.hpp"
#include "shared/mouse.hpp"
#include "shared/keyboard.hpp"
#include "shared/convert.hpp"
#include "shared/dsurface.hpp"

namespace WorldDominationTour {

typedef DynamicVectorClass<MSSfxEntry *> SfxList;
typedef VectorCursor<MSSfxEntry *, SfxList> SfxCursor;
typedef DynamicVectorClass<rc_ptr<Territory> > TerritoryList;
typedef VectorCursor<rc_ptr<Territory>, TerritoryList> TerritoryCursor;

class Selection : public MSEngine {
public:
    Selection(rc_ptr<Campaign> const &campaign, int faction);        // 0x0072D560
    virtual ~Selection();                                           // 0x0072D990 (slot 0 0x00730290)

    void Load_Voices(INIClass &ini, Wstring const &section);        // 0x0072DC20 (and the thresholds)
    void Load_Sounds(INIClass &ini, Wstring const &section);        // 0x0072DD10
    void Load_Layout(INIClass &ini, Wstring const &section);        // 0x0072DEA0
    void Remove_Territory_Anims();                                  // 0x0072F180
    void Remove_Territory_Anims_2();                                // 0x0072F200 (same body)
    void Play_Map_Enter();                                          // 0x0072F280
    void Check_Escape();                                            // 0x0072FC80
    void Set_Description(WideString const &text, bool unknown2);    // 0x0072FCD0
    void Set_Tooltip(WideString const &text);                       // 0x0072FDA0
    void Play_Sound(Wstring const &name);                           // 0x0072FE90
    void Show_Campaign();                                           // 0x0072FF30
    void Leave_Territory();                                         // 0x0072F340
    void Cancel();                                                  // 0x0072F430
    void Uncancel();                                                // 0x0072F540
    bool Select_Territory(rc_ptr<Territory> const &territory);      // 0x0072ED80
    bool Hover(Point2D const &point);                               // 0x0072E650
    void Hover_2(Point2D const &point);                             // 0x0072E720
    int Get_Result(int index, bool &mega);                          // 0x0072F6E0 (0 won, 1 lost, 2 neither)
    void Start_Theme();                                             // 0x00730160
    void Show_Result(int faction);                                  // 0x0072FA00
    static void __fastcall Show(rc_ptr<Campaign> const &campaign, int faction);   // 0x0072FF80
    void Clear_Screen();                                            // 0x00730230 (inline in the destructor)

    rc_ptr<Campaign> TheCampaign;                                   // +0x048
    rc_ptr<Conflict> unknown_50;                                    // +0x050
    Voices TheVoices;                                               // +0x058
    int WinningThreshold;                                           // +0x434
    int LosingThreshold;                                            // +0x438
    int MegaWinningThreshold;                                       // +0x43C
    int MegaLosingThreshold;                                        // +0x440
    bool Escaped;                                                   // +0x444 (Escape pressed)
    int unknown_448;                                                // +0x448
    int unknown_44c;                                                // +0x44C
    int unknown_450;                                                // +0x450 (the last conflict)
    int unknown_454;                                                // +0x454
    rc_ptr<Map> TheMap;                                             // +0x458
    int unknown_460;                                                // +0x460
    rc_ptr<Territory> unknown_464;                                  // +0x464
    ConvertClass *TargetPalette;                                    // +0x46C
    MSAnimEntry *ZoomingTarget;                                     // +0x470
    MSAnimEntry *Target;                                            // +0x474
    int TargetDividingFrame;                                        // +0x478
    MSBitPrintAnim *Description;                                    // +0x47C
    MSBitPrintAnim *Tooltip;                                        // +0x480
    MSFont *unknown_484;                                            // +0x484
    rc_ptr<State> unknown_488;                                      // +0x488
    Wstring ThemeName;                                              // +0x490 (the Sounds "Theme" entry)
    SfxList Sounds;                                                 // +0x494
    int OldFontColor;                                               // +0x4AC
};

}

#endif
