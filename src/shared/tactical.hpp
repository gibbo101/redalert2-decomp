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

class CellClass;

class Surface;

// The tactical view (0x0083996C; RTTI class Tactical, an AbstractClass:
// primary vtable 0x007AC570 with 25 slots, stored by 0x006A24B0, 0x006A26C0,
// 0x006A2710 and 0x006AC800). Stand-in: only the members the screen code uses,
// layout padding otherwise; the AbstractClass overrides (slots 3, 5, 6, 8,
// 10-12, 23) are not declared yet.
class Tactical : public AbstractClass {
public:
    Tactical();                                     // 0x006A24B0 (Read_Scenario_INI makes a new view)
    virtual HRESULT __stdcall GetClassID(GUID *clsid);
    virtual HRESULT __stdcall Load(IStream *stream);
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);
    virtual int Kind_Of() const;
    virtual int Size_Of() const;
    virtual void AI();                              // 0x006A2DD0 (slot 23: the scroll animation and the view position)

    bool Unknown_006A8C80(Point2D *point);          // 0x006A8C80 (clamps a view position; false when unchanged)
    void Unknown_006A9170();                        // 0x006A9170 (after the view position changed)

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

    char unknown_24[0xA8 - 0x24];
    int unknown_a8;                 // +0xA8 the frame of the last update (-1 after construction)
    char unknown_ac[0xB0 - 0xAC];
    Point2D unknown_b0;             // +0xB0 the view position (BuildingClass slot 73 caches it)
    char unknown_b8[0xC0 - 0xB8];
    double unknown_c0;              // +0xC0 zoom factor (Blit_Display divides by it; 1.0 = none)
    Point2D unknown_c8;             // +0xC8 the scroll start (AI 0x006A2DD0 interpolates it to unknown_d0)
    Point2D unknown_d0;             // +0xD0 the scroll target
    float unknown_d8;               // +0xD8 the scroll step per frame (ScrollClass slot 26 tests it against 0)
    float unknown_dc;               // +0xDC the scroll progress, 0..1
    char unknown_e0[0xD64 - 0xE0];
    Point2D unknown_d64;            // +0xD64 the view position
    char unknown_d6c[0xD74 - 0xD6C];
    Point2D unknown_d74;            // +0xD74 the requested view position
    char unknown_d7c;
    bool unknown_d7d;               // +0xD7D set by Flag_To_Redraw
    char unknown_d7e[0xDA0 - 0xD7E];
    int unknown_da0;                // +0xDA0 counts the timer expiries
    CDTimerClass<SystemTimerClass> unknown_da4;     // +0xDA4 restarted at Rules->WaypointAnimationSpeed
    char unknown_db0[0xE18 - 0xDB0];    // (0xE18 bytes: Read_Scenario_INI's new)
};
extern Tactical *unknown_tactical_83996c;

#endif
