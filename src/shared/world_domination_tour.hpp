// World Domination Tour (the RA2 campaign map game mode): the reference
// counted classes of the WorldDominationTour namespace (RTTI names), as far
// as the recovered units use them. Units: Campaign 0x00725BF0, Conflict
// 0x00727100, GameOption 0x00728480, History 0x00728C60, Map 0x00728FD0,
// WDTTerritory/WDTState 0x0072BBD0, CampaignProperties 0x0072CF90,
// Selection 0x0072D370, State 0x00730510, Territory 0x00730990, ...
// Layouts are partial; field names are hypotheses unless stated.
#ifndef RA2_SHARED_WORLD_DOMINATION_TOUR_HPP
#define RA2_SHARED_WORLD_DOMINATION_TOUR_HPP

#include "shared/reference_counted.hpp"
#include "shared/wdt_state.hpp"
#include "shared/wdt_territory.hpp"
#include "shared/wstring.hpp"
#include "shared/wide_string.hpp"
#include "shared/string_table.hpp"
#include "shared/ini_class.hpp"
#include "shared/ms_engine.hpp"
#include "shared/cd_file_class.hpp"
#include "shared/vector_class.hpp"
#include "shared/vector_cursor.hpp"

// WDTState (RTTI vtable 0x007AF308, global namespace; size 0x4C): the
// campaign map's INI data, made by the rc_ptr<WDTState> factory 0x0072BEB0
// (constructor 0x0072BFA0, WDTTerritory/WDTState unit). Only the fields the
// recovered units read:
//   +0x08 char const *ShortLabel   CSF label of the short description
//   +0x0C char const *LongLabel    CSF label of the long description
//   +0x10 char const *unknown_10   (CampaignProperties 0x0072D2E0)
//   +0x14 unsigned char unknown_14 (0x0072D2B0)
//   +0x18 int unknown_18           (0x0072D290)
//   +0x20 unsigned unknown_20      the number of territories State tracks
//   +0x24 unsigned ConflictCount
//   +0x2C DynamicVectorClass<rc_ptr<WDTTerritory>> (vtable 0x007AF318)
//   +0x44 void **unknown_44        one owner byte array per conflict



// The two-letter code of a faction (0x007686D0; function statics; 1..3,
// "XX" otherwise). Name hypothesis.
Wstring const &__fastcall Faction_Code(int faction);

namespace WorldDominationTour {

class State;
class History;
class CampaignProperties;

class GameOption;

// RTTI vtable 0x007AF07C; Conflict.cpp (unit 0x00727100-0x0072847F).
// One battle of the campaign: a territory and the shared game option list.
//   +0x08 rc_ptr<WDTTerritory> Territory   size 0x10
class Conflict : public ReferenceCounted {
public:
    Conflict(rc_ptr<WDTTerritory> const &territory);               // 0x00727360
    virtual ~Conflict();                                            // 0x007273C0

    static rc_ptr<Conflict> __fastcall Create(rc_ptr<WDTTerritory> const &territory);   // 0x007272F0
    bool operator==(Conflict const &other) const;                   // 0x007273A0
    bool Is_Valid() const;                                          // 0x007273E0
    int unknown_7273f0() const;                                     // 0x007273F0 (the territory's +0x08, 0 without one)
    static void __fastcall Init_Options();                          // 0x00727480
    static void Clear_Options();                                    // 0x00727920
    WideString Describe_Options() const;                            // 0x00727960

    rc_ptr<WDTTerritory> Territory;                                 // +0x08
};

// RTTI vtable 0x007AF194; History.cpp (unit 0x00728C60-0x00728FCF).
//   +0x08 rc_ptr<WDTState> TheWDTState
//   size 0x10
class History : public ReferenceCounted {
public:
    History(rc_ptr<WDTState> const &wdt_state);                      // 0x00728EC0
    virtual ~History();                                             // 0x00728F40

    static rc_ptr<History> __fastcall Create(rc_ptr<WDTState> const &wdt_state);   // 0x00728E50
    rc_ptr<State> Get_State(int index) const;                       // 0x00728F00
    int Is_Valid(unsigned index) const;                             // 0x00728F20

    rc_ptr<WDTState> TheWDTState;                                   // +0x08
};

// RTTI vtable 0x007AF3CC; State.cpp (unit 0x00730510-0x0073098F).
//   +0x08 rc_ptr<WDTState> TheWDTState
//   +0x10 unsigned char *Owners  one byte per territory (0, 1, 2) from the
//         WDTState's +0x44 list entry `index`; null when built empty
//   size 0x14
class State : public ReferenceCounted {
public:
    State();                                                        // 0x007307F0
    State(rc_ptr<WDTState> const &wdt_state, unsigned index);        // 0x00730830
    virtual ~State();                                               // 0x007308E0

    static rc_ptr<State> __fastcall Create(rc_ptr<WDTState> const &wdt_state, int index);   // 0x00730700
    static rc_ptr<State> __fastcall Create();                       // 0x00730790
    int Owner_Of(unsigned territory) const;                         // 0x00730890 (1..3, 0 for none)
    int Count_Owned(int owner) const;                               // 0x00730900 (owners 2 and 3 only)

    rc_ptr<WDTState> TheWDTState;                                   // +0x08
    unsigned char *Owners;                                          // +0x10
};

// RTTI vtable 0x007AF34C; WDTProps.cpp (unit 0x0072CF90-0x0072D36F).
//   +0x08 rc_ptr<WDTState> TheWDTState
//   +0x10 WideString ShortDescription, +0x14 WideString LongDescription
//         (the campaign's CSF labels, or the WDT:Default... ones)
//   size 0x18
class CampaignProperties : public ReferenceCounted {
public:
    CampaignProperties(rc_ptr<WDTState> const &wdt_state);           // 0x0072D1F0
    virtual ~CampaignProperties();                                  // 0x0072D1C0

    static rc_ptr<CampaignProperties> __fastcall Create(rc_ptr<WDTState> const &wdt_state);   // 0x0072D180
    int unknown_18() const;                                         // 0x0072D290 (0 without a campaign)
    int unknown_72d2a0() const;                                     // 0x0072D2A0 (1)
    int unknown_14() const;                                         // 0x0072D2B0 (1 without a campaign)
    int Last_Conflict() const;                                      // 0x0072D2D0 (ConflictCount - 1)
    Wstring unknown_10() const;                                     // 0x0072D2E0 ("" without a campaign)
    rc_ptr<WDTState> const &WDT_State() const { return TheWDTState; }

    rc_ptr<WDTState> TheWDTState;                                   // +0x08
    WideString ShortDescription;                                    // +0x10
    WideString LongDescription;                                     // +0x14
};

// RTTI vtable 0x007AF3EC; WDTTerr.cpp (unit 0x00730990-0x007312CF).
//   +0x08 int Index
//   +0x0C WideString Name           CSF text of <name_prefix><NN>
//   +0x10 INIPoint2D Target, +0x18 INIPoint2D Origin   ("Target_<width>",
//         "Origin_<width>" of the INI section; the _800 keys as fallback)
//   +0x20 Wstring ShapeName         <shape_prefix><NN>.shp
//   +0x24 MSAnim *OwnerAnim, +0x28 MSAnim *HighlightAnim  (hypotheses)
//   +0x2C int unknown_2c
//   size 0x30
// A point member that starts at (0, 0) and takes INI points (the
// Territory constructor zeroes its points as member constructors before
// the shape name; the type's real name is unknown, perhaps TPoint2D<int>).
struct TerritoryPoint : INIPoint2D {
    TerritoryPoint()
    {
        X = 0;
        Y = 0;
    }
};

class Territory : public ReferenceCounted {
public:
    Territory(int index, INIClass const &ini, Wstring const &section, Wstring const &shape_prefix,
              Wstring const &name_prefix);                          // 0x00730BE0
    virtual ~Territory();                                           // 0x00730F80

    static rc_ptr<Territory> __fastcall Create(int index, INIClass const &ini, Wstring const &section,
                                               Wstring const &shape_prefix, Wstring const &name_prefix);   // 0x00730B80
    void Create_Owner_Anim(MSEngine *engine, ConvertClass *drawer, Point2D const &offset);      // 0x00730E00 (name hypothesis)
    void Create_Highlight_Anim(MSEngine *engine, ConvertClass *drawer, Point2D const &offset);  // 0x00730EC0 (name hypothesis)
    void Show_Highlight(bool arg, MSEngine *engine);                // 0x00731120 (name hypothesis)
    void Set_unknown_2c(int value);                                 // 0x00731190
    int Take_unknown_2c();                                          // 0x007311A0 (returns and clears)

    int Index;                                                      // +0x08
    WideString Name;                                                // +0x0C
    TerritoryPoint Target;                                          // +0x10
    TerritoryPoint Origin;                                          // +0x18
    Wstring ShapeName;                                              // +0x20
    MSAnim *OwnerAnim;                                              // +0x24
    MSAnim *HighlightAnim;                                          // +0x28
    int unknown_2c;                                                 // +0x2C
};

}

#endif
