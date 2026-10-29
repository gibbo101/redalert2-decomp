// WorldDominationTour::Map (WDTMap.cpp, unit 0x00728FD0-0x0072BFFF): the campaign map of the
// World Domination Tour, a counted object (RTTI vtable 0x007AF1EC, base ReferenceCounted,
// size 0xD4; created by 0x007292E0). Only the members the constructor (0x00729330) and
// destructor (0x007293F0) touch are named; the types of the unknown members are hypotheses.
//   +0x08 int unknown_08, +0x0C int unknown_0c, +0x10 int unknown_10  (the constructor arguments)
//   +0x14 and +0x24 pointers to objects the destructor deletes, +0x78 another
//   +0x28 Wstring (":" when built)
//   +0x2C DynamicVectorClass<rc_ptr<Territory>> Territories
//   +0x44, +0x64, +0x6C three small member objects, each zeroed by its own inline
//         constructor (types and grouping are hypotheses). Evidence: the constructor calls
//         the VectorClass<rc_ptr<Territory>> constructor 0x0072BB10 out of line but expands
//         Palettes' VectorClass constructor. Under /Ob2 a nested site is charged its cost
//         times (1 + the inline call sites still pending in the enclosing bodies) (Study152);
//         Territories' base constructor needs three member-constructor sites after it
//         besides Palettes' (plain int members expand it; two such objects are not enough).
//   +0xBC DynamicVectorClass<AnimationPalette *> Palettes
#ifndef RA2_SHARED_WDT_MAP_HPP
#define RA2_SHARED_WDT_MAP_HPP

#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

class Voices;

// The territory of `territories` whose Index is `index` (WDTTerr.cpp 0x007311B0; an empty
// pointer when none is; name hypothesis).
rc_ptr<Territory> __fastcall Find_Territory(DynamicVectorClass<rc_ptr<Territory> > &territories, int index);

class Map : public ReferenceCounted {
public:
    class AnimationPalette;

    Map(int unknown_08, int unknown_0c, int unknown_10);          // 0x00729330
    virtual ~Map();                                                 // 0x0072AF30 (slot 0, calls 0x007293F0)

    static rc_ptr<Map> __fastcall Create(int unknown_08, int unknown_0c, int unknown_10);   // 0x007292E0
    void unknown_72a620(MSEngine *engine, Voices *voices);         // 0x0072A620
    int Territory_At(Point2D const &point) const;                   // 0x0072A660 (-1 for none)
    void Set_Unknown_74(MSEngine *engine, bool value);              // 0x0072A6D0
    void Set_Unknown_68(MSEngine *engine, bool value);              // 0x0072A720
    int Is_Inside(Point2D const &point) const;                      // 0x0072A770 (inside the +0x54 rectangle)
    // The territory of that index (inline; out-of-line copy 0x007302B0 in WDTSel.cpp).
    rc_ptr<Territory> Get_Territory(int index) { return Find_Territory(Territories, index); }

    int unknown_08;                                                 // +0x08
    int unknown_0c;                                                 // +0x0C
    int unknown_10;                                                 // +0x10
    void *unknown_14;                                               // +0x14
    int unknown_18;                                                 // +0x18
    int unknown_1c;                                                 // +0x1C
    int unknown_20;                                                 // +0x20
    void *unknown_24;                                               // +0x24
    Wstring unknown_28;                                             // +0x28
    DynamicVectorClass<rc_ptr<Territory> > Territories;             // +0x2C
    struct Unknown44 {
        Unknown44() : unknown_0(0), unknown_4(0) {}
        int unknown_0;
        int unknown_4;
    } unknown_44;                                                   // +0x44
    char unknown_4c[0x64 - 0x4C];
    struct Unknown64 {
        Unknown64() : unknown_0(0), unknown_4(0) {}
        int unknown_0;
        char unknown_4;
    } unknown_64;                                                   // +0x64
    struct Unknown6C {
        Unknown6C() : unknown_0(0), unknown_4(0), unknown_8(0) {}
        int unknown_0;
        int unknown_4;
        char unknown_8;
    } unknown_6c;                                                   // +0x6C
    void *unknown_78;                                               // +0x78
    Rect DescriptionRect;                                           // +0x7C (Selection's description text)
    Rect TooltipRect;                                               // +0x8C (Selection's tool tip text)
    Rect PlayRect;                                                  // +0x9C (GUI:PlayWDT)
    Rect BackRect;                                                  // +0xAC (TXT_BACK)
    DynamicVectorClass<AnimationPalette *> Palettes;                // +0xBC
};

}

#endif
