// WorldDominationTour::Map (WDTMap.cpp, unit 0x00728FD0-0x0072BFFF): the campaign map of the
// World Domination Tour, a counted object (RTTI vtable 0x007AF1EC, base ReferenceCounted,
// size 0xD4; created by 0x007292E0). Only the members the constructor (0x00729330) and
// destructor (0x007293F0) touch are named; the types of the unknown members are hypotheses.
//   +0x08 int unknown_08, +0x0C int unknown_0c, +0x10 int unknown_10  (the constructor arguments)
//   +0x14 and +0x78 drawers made by unknown_load_drawer_5ac560, +0x24 the territory index surface
//         (unknown_load_pcx_60d110), all deleted by the destructor; +0x18/+0x1C animations
//         (built in the loader 0x00729510, used by unknown_72a620)
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
#include "shared/convert.hpp"

// Shown while the World Domination Tour map (0x00839958 background) is up: slot 4 and
// slot 5 redraw the interface frame (0x006F3650) while the flags 0x007FBD04 / 0x007FBD05
// are set (RTTI vtable 0x007AF1BC; no members of its own; names are hypotheses).
class MSFrameAnim : public MSAnim {
public:
    MSFrameAnim();                                                  // 0x007291C0
    virtual ~MSFrameAnim();                                         // 0x007291F0 (deleting 0x0072AF00)
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);      // 0x00729200
    virtual void Draw(Surface *surface, Rect const *clip);          // 0x00729220
    virtual Rect Get_Rect();                                        // 0x007292B0 (the 640x480 screen)
};

extern bool unknown_flag_7fbd05;  // 0x007FBD05 (MSFrameAnim::Draw draws while set)
// Draws the interface frame clipped to window (0x006F3650, unowned/Unknown_Draw_Interface_006f3650.cpp).
void __fastcall Unknown_006F3650(Surface *surface, Rect const &window, bool arg3);

namespace WorldDominationTour {

class Voices;

// The territory of `territories` whose Index is `index` (WDTTerr.cpp 0x007311B0; an empty
// pointer when none is; name hypothesis).
rc_ptr<Territory> __fastcall Find_Territory(DynamicVectorClass<rc_ptr<Territory> > &territories, int index);

class Map : public ReferenceCounted {
public:
    // A named drawer of the map's palette list (0x0072A510 makes them; inline constructor
    // and destructor, out-of-line copies 0x0072A5E0 and 0x0072A600).
    class AnimationPalette {
    public:
        AnimationPalette(Wstring const &name, ConvertClass *drawer) : Name(name), Drawer(drawer) {}
        ~AnimationPalette();                                        // 0x0072A600

        Wstring Name;                                               // +0x00
        ConvertClass *Drawer;                                       // +0x04
    };

#ifdef RA2_WDT_MAP_LOAD_LAYOUT
    void Load(INIClass &ini, MSEngine *engine, int unknown3);
    Point2D const &Get_Origin() const { return unknown_44; }
#endif
    Map(int unknown_08, int unknown_0c, int unknown_10);          // 0x00729330
    virtual ~Map();                                                 // 0x0072AF30 (slot 0, calls 0x007293F0)

    static rc_ptr<Map> __fastcall Create(int unknown_08, int unknown_0c, int unknown_10);   // 0x007292E0
    void unknown_72a620(MSEngine *engine, Voices *voices);         // 0x0072A620
    // The drawer of the palette file `name`, loaded and kept in Palettes on first use (0 when
    // it cannot be loaded; name hypothesis).
    ConvertClass *Get_Drawer(Wstring const &name);                  // 0x0072A510
    int Territory_At(Point2D const &point) const;                   // 0x0072A660 (-1 for none)
    void Set_Unknown_74(MSEngine *engine, bool value);              // 0x0072A6D0
    void Set_Unknown_68(MSEngine *engine, bool value);              // 0x0072A720
    bool Is_Inside(Point2D const &point) const;                     // 0x0072A770 (inside the +0x54 rectangle)
    // A shape animation from the INI entry "file,x,y[,rate[,palette]]" (x, y relative to unknown_44;
    // rate 5 and palette `drawer` by default); 0 when the entry, the file or a drawer is missing.
    MSAnim *Load_Anim(INIClass &ini, Wstring const &section, Wstring const &entry, ConvertClass *drawer);   // 0x0072A280
    // The territory of that index (inline; out-of-line copy 0x007302B0 in WDTSel.cpp).
    rc_ptr<Territory> Get_Territory(int index) { return Find_Territory(Territories, index); }

    int unknown_08;                                                 // +0x08
    int unknown_0c;                                                 // +0x0C
    int unknown_10;                                                 // +0x10
    ConvertClass *unknown_14;                                       // +0x14
    MSAnim *unknown_18;                                             // +0x18
    MSAnim *unknown_1c;                                             // +0x1C
#ifdef RA2_WDT_MAP_LOAD_LAYOUT
    MSAnim *unknown_20;
#else
    int unknown_20;
#endif
    //                                                 // +0x20
    Surface *unknown_24;                                            // +0x24 (each pixel a territory index: Territory_At)
    Wstring unknown_28;                                             // +0x28
    DynamicVectorClass<rc_ptr<Territory> > Territories;             // +0x2C
#ifdef RA2_WDT_MAP_LOAD_LAYOUT
    Point2D unknown_44;  // +0x44 map origin
    Point2D unknown_4c;  // +0x4C help-bar origin
    Rect unknown_54;     // +0x54 back-button rectangle
#else
    struct Unknown44 {
        Unknown44() : unknown_0(0), unknown_4(0) {}
        int unknown_0;
        int unknown_4;
    } unknown_44;                                                   // +0x44
    char unknown_4c[0x64 - 0x4C];
#endif
    struct Unknown64 {
        Unknown64() : unknown_0(0), unknown_4(0) {}
#ifdef RA2_WDT_MAP_LOAD_LAYOUT
        MSOverlayAnim *unknown_0;
#else
        int unknown_0;
#endif
        char unknown_4;
    } unknown_64;                                                   // +0x64
    struct Unknown6C {
        Unknown6C() : unknown_0(0), unknown_4(0), unknown_8(0) {}
        int unknown_0;
        int unknown_4;
        char unknown_8;
    } unknown_6c;                                                   // +0x6C
    ConvertClass *unknown_78;                                       // +0x78
    Rect DescriptionRect;                                           // +0x7C (Selection's description text)
    Rect TooltipRect;                                               // +0x8C (Selection's tool tip text)
    Rect PlayRect;                                                  // +0x9C (GUI:PlayWDT)
    Rect BackRect;                                                  // +0xAC (TXT_BACK)
    DynamicVectorClass<AnimationPalette *> Palettes;                // +0xBC
};

}

#endif
