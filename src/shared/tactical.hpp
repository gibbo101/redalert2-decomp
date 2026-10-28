// Tactical: the tactical view (moved out of shared/gscreen.hpp so that units
// such as Particle.cpp can use it without gscreen.hpp's other headers, whose
// statics would renumber the unit's initializers).
#ifndef RA2_SHARED_TACTICAL_HPP
#define RA2_SHARED_TACTICAL_HPP

#include "shared/abstract_class.hpp"
#include "shared/coord.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/rect.hpp"
#include "shared/matrix3d.hpp"

class CellClass;

class Surface;
class ObjectClass;

// A flag at 0x00AC133D (0x006F76B0) and the handler 0x006F71E0 that the
// selection band gives each object type's ID while the flag is set
// (hypotheses).
bool Unknown_006F76B0();
void __fastcall Unknown_006F71E0(char const *id);

// The screen rise of a height in leptons (0x006A2970; rounded, plus one from
// 728 up) and its inverse (0x006A29B0); hypotheses.
int __fastcall Unknown_006A2970(int z);
int __fastcall Unknown_006A29B0(int pixel);

// A lepton offset (x, y) to its screen offset before the division by 256:
// (x - y) * 30 across, (x + y) * 15 down (0x006A6800; never called, expanded
// by its users; hypothesis).
void __fastcall Unknown_006A6800(int x, int y, int *pixel_x, int *pixel_y);

// The screen offset of a lepton offset, built through 0x006A6800 (0x006A2740;
// the Tactical slot-24 line drawer 0x006AC160 builds two; name hypothesis).
struct TacticalProjection {
    TacticalProjection(int x, int y);               // 0x006A2740
    int X;
    int Y;
};


// The tactical view (0x0083996C; RTTI class Tactical, an AbstractClass:
// primary vtable 0x007AC570 with 25 slots, stored by 0x006A24B0, 0x006A26C0,
// 0x006A2710 and 0x006AC800). Stand-in: only the members the screen code uses,
// layout padding otherwise; the AbstractClass overrides (slots 3, 5, 6, 8,
// 10-12, 23) are not declared yet.
class Tactical : public AbstractClass {
public:
    Tactical();                                     // 0x006A24B0 (Read_Scenario_INI makes a new view)
    Tactical(NoInitClass const &noinit);            // 0x006A26C0
    virtual HRESULT __stdcall GetClassID(GUID *clsid);
    virtual HRESULT __stdcall Load(IStream *stream);
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);
    virtual ~Tactical();                            // 0x006A2710 (clears 0x0083996C; scalar deleting 0x006AC800)
    virtual void Detach(AbstractClass *target, bool all = true);   // 0x006AAB60 slot 10
    virtual int Kind_Of() const;
    virtual int Size_Of() const;
    virtual void AI();                              // 0x006A2DD0 (slot 23: the scroll animation and the view position)

    bool Unknown_006A8C80(Point2D *point);          // 0x006A8C80 (clamps a view position; false when unchanged)
    void Unknown_006A9170();                        // 0x006A9170 (after the view position changed)
    void Unknown_006AA610(void (__fastcall *callback)(ObjectClass *object));          // 0x006AA610 (ends the selection band: the rectangle of its two corners to 0x006AABC0; hypothesis)
    // Redraw the terrain objects (0x006A9E10, last first) and the buildings
    // (0x006A9F60) of display layer 2 whose drawn area overlaps the
    // intersection of the two rectangles (hypothesis).
    void Unknown_006A9E10(bool arg1, Rect const &rect1, Rect const &rect2);
    void Unknown_006A9F60(bool arg1, Rect const &rect1, Rect const &rect2);
    bool Unknown_006AA510(ObjectClass *object, int x, int y);   // 0x006AA510 (lists an object's pixel when it is near the tactical area; 0x006AA300 expands it)
    int Unknown_006AA6A0();                         // 0x006AA6A0 (1 when an object pixel lies inside the selection band; hypothesis)
    void Unknown_006AA790();                        // 0x006AA790 (draws the selection band rectangle; hypothesis)
    void Unknown_006AABC0(Rect const *rect, void (__fastcall *callback)(ObjectClass *object));   // 0x006AABC0 (hypothesis)

    // Draws a line between two coordinates in a color (0x006AC160, slot 24;
    // TechnoClass 0x006C3950/0x006C3A90; true when drawn; hypothesis).
    virtual bool unknown_slot24(CoordStruct const &from, CoordStruct const &to, int color, int arg4);

    // Draws one pass (0, 1, 2) of the tactical view into surface (0x006A45A0).
    void Unknown_006A45A0(Surface *surface, bool redraw, int pass);
    // A screen point converted for the techno types' smoke offsets (0x006A2900).
    Point2D Unknown_006A2900(Point2D const &point);
    // Moves the view to a point (0x006A66B0; radar slot 52).
    void Unknown_006A66B0(Point2D const &point);
    void Unknown_006A66B0(CoordStruct const &coord);    // the same entry, given a coordinate
    // The coordinate under a screen point (0x006A2B10) and the cell under it
    // (0x006A6BD0; radar slot 51).
    CoordStruct Unknown_006A2B10(Point2D const &point);
    CoordStruct Unknown_006A2BF0(Point2D const &point); // original ECX Tactical, hidden CoordStruct result, RET8
    Point2D Unknown_006A27A0(CoordStruct const &coord);  // 0x006A27A0 (the screen point of a coordinate; hidden Point2D result, RET8)
    Cell Unknown_006A6BD0(Point2D const &point);
    void Unknown_006A2CB0(CoordStruct const &coord, int arg2);   // 0x006A2CB0 (TeamClass script handler 0x006BC4C0: looks at a coordinate; hypothesis)
    int Unknown_006AA840(int arg1);                 // 0x006AA840 (display slot 41; -1 when none)
    void Unknown_006A8B70(int arg1, int arg2);      // 0x006A8B70 (display slot 41)

    // The screen pixel of a coordinate; false when off screen (0x006A29D0;
    // hypothesis: Coord_To_Pixel).
    bool Unknown_006A29D0(CoordStruct const &coord, Point2D &pixel);
    int Unknown_006A8D40(Cell const &cell, int layer);     // 0x006A8D40 (a cell's shroud frame for a layer; DisplayClass slot 37; hypothesis)
    void Unknown_006AADD0(CellClass *cell);        // 0x006AADD0 (DisplayClass slot 37: a cell to redraw; hypothesis)
    void Unknown_006AA5A0(Point2D const &point);   // 0x006AA5A0 starts a selection band at a point (DisplayClass slot 47; hypothesis)
    void Unknown_006AA5E0(Point2D const &point);   // 0x006AA5E0 drags the band to a point (DisplayClass slot 47; hypothesis)
    void Unknown_006AA770();                       // 0x006AA770 (DisplayClass slot 35: ends the band selection; hypothesis)
    void Unknown_006AAD40();                       // 0x006AAD40 (Planning.cpp; hypothesis: drops the pending command)
    // Redraws a screen rectangle (0x006A3020; hypothesis; BuildingClass slot 52).
    void Unknown_006A3020(Rect rect, int arg2);
    // Sets the view rectangle (0x006A65A0; DisplayClass slot 42).
    void Unknown_006A65A0(Rect const &rect);
    void Unknown_006A6640(Point2D const &point);    // 0x006A6640 (sets the view position, clamped)

    // Layout from the constructor 0x006A24B0 (init-list stores, then the body).
    short unknown_24;               // +0x24 cleared by the constructor
    char unknown_26[0xA4 - 0x26];
    int unknown_a4;                 // +0xA4 -1 after construction
    int unknown_a8;                 // +0xA8 the frame of the last update (-1 after construction)
    bool unknown_ac;                // +0xAC
    bool unknown_ad;                // +0xAD
    Point2D unknown_b0;             // +0xB0 the view position (BuildingClass slot 73 caches it)
    Point2D unknown_b8;             // +0xB8
    double unknown_c0;              // +0xC0 zoom factor (Blit_Display divides by it; 1.0 = none)
    Point2D unknown_c8;             // +0xC8 the scroll start (AI 0x006A2DD0 interpolates it to unknown_d0)
    Point2D unknown_d0;             // +0xD0 the scroll target
    float unknown_d8;               // +0xD8 the scroll step per frame (ScrollClass slot 26 tests it against 0)
    float unknown_dc;               // +0xDC the scroll progress, 0..1
    int unknown_e0;                 // +0xE0
    int unknown_e4[800];            // +0xE4 pointers (cleared by the constructor, swizzled by Load; unknown_e0 counts them)
    Point2D unknown_d64;            // +0xD64 the view position
    Point2D unknown_d6c;            // +0xD6C
    Point2D unknown_d74;            // +0xD74 the requested view position
    bool unknown_d7c;               // +0xD7C true after construction
    bool unknown_d7d;               // +0xD7D set by Flag_To_Redraw
    bool unknown_d7e;               // +0xD7E
    Rect unknown_d80;               // +0xD80 copied from the global rectangle at 0x00ABE4A8
    Point2D unknown_d90;            // +0xD90 the selection band corner (DisplayClass slot 47 starts it)
    Point2D unknown_d98;            // +0xD98 the other corner
    int unknown_da0;                // +0xDA0 counts the timer expiries
    CDTimerClass<SystemTimerClass> unknown_da4;     // +0xDA4 restarted at Rules->WaypointAnimationSpeed
    int unknown_db0;                // +0xDB0 the number of entries of the table at 0x00ABE5F8
    Matrix3D unknown_db4;           // +0xDB4 the view transform (identity, rotated, scaled)
    Matrix3D unknown_de4;           // +0xDE4 the screen projection (rows set by the constructor)
    int unknown_e14;                // +0xE14
    // (0xE18 bytes: Read_Scenario_INI's new)
};
extern Tactical *unknown_tactical_83996c;

// An object and the screen pixel it was drawn at (the table at 0x00ABE5F8,
// filled by 0x006AA300; Tactical +0xDB0 counts the entries, at most 500).
struct TacticalObjectPixel {
    ObjectClass *Object;
    Point2D Pixel;
};
extern TacticalObjectPixel unknown_tactical_pixels_abe5f8[500];

#endif
