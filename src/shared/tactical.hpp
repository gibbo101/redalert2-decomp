// Tactical: the tactical view (moved out of shared/gscreen.hpp so that units
// such as Particle.cpp can use it without gscreen.hpp's other headers, whose
// statics would renumber the unit's initializers).
#ifndef RA2_SHARED_TACTICAL_HPP
#define RA2_SHARED_TACTICAL_HPP

#include "shared/coord.hpp"
#include "shared/rect.hpp"

class CellClass;

class Surface;

// The tactical view (0x0083996C; RTTI class Tactical, an AbstractClass).
// Stand-in: only the members the screen code uses, layout padding otherwise.
struct UnknownPoint2D;
class Tactical {
public:
    // Draws one pass (0, 1, 2) of the tactical view into surface (0x006A45A0).
    void Unknown_006A45A0(Surface *surface, bool redraw, int pass);
    // A screen point converted for the techno types' smoke offsets (0x006A2900).
    UnknownPoint2D Unknown_006A2900(UnknownPoint2D const &point);
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

    char unknown_00[0xB0];
    Point2D unknown_b0;             // +0xB0 the view position (BuildingClass slot 73 caches it)
    char unknown_b8[0xC0 - 0xB8];
    double unknown_c0;              // +0xC0 zoom factor (Blit_Display divides by it; 1.0 = none)
    char unknown_c8[0xD8 - 0xC8];
    float unknown_d8;               // +0xD8 ScrollClass slot 26 tests it against 0
    char unknown_dc[0xD7D - 0xDC];
    bool unknown_d7d;               // +0xD7D set by Flag_To_Redraw
};
extern Tactical *unknown_tactical_83996c;

#endif
