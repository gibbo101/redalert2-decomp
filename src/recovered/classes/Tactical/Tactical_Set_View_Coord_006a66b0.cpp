// void __fastcall Unknown_006A6800(int x, int y, int *pixel_x, int *pixel_y)
// (0x006A6800): a lepton offset to its screen offset before the division by
// 256. Never called: the Tactical unit expands it inline (0x006A2740 and the
// coordinate-to-pixel family).
#include "shared/tactical.hpp"

inline void __fastcall Unknown_006A6800(int x, int y, int *pixel_x, int *pixel_y)
{
    *pixel_x = x * 60 / 2;
    *pixel_y = x * 30 / 2;
    *pixel_x += y * -60 / 2;
    *pixel_y += y * 30 / 2;
}

// Point2D __fastcall Rectangular_To_Isometric(Point2D point) (0x006A2740): a rectangular point rotated onto
// the isometric axes through 0x006A6800 (TibSun Tactical::Rectangular_To_Isometric). The hidden result comes
// in ecx and the point on the stack, which is why the old TacticalProjection constructor spelling also fit.
#include "shared/tactical.hpp"

inline Point2D __fastcall Rectangular_To_Isometric(Point2D point)
{
    Point2D iso;
    Unknown_006A6800(point.X, point.Y, &iso.X, &iso.Y);
    return iso;
}

// Point2D Tactical::Coord_To_Pixel_Absolute(CoordStruct const &coord) (0x006A27A0): the absolute screen pixel of a
// coordinate: its X/Y rotated onto the isometric axes, leptons to pixels (/256), raised by the screen
// height of its Z (0x006A2970) (TibSun Tactical::Coord_To_Pixel_Absolute(Coord const &)).
#include "shared/tactical.hpp"

inline Point2D Tactical::Coord_To_Pixel_Absolute(CoordStruct const &coord)
{
    Point2D point(coord.X, coord.Y);
    Point2D pixel = Rectangular_To_Isometric(point);
    pixel.X /= 256;
    pixel.Y /= 256;
    int lift = Unknown_006A2970(coord.Z);
    pixel.Y -= lift;
    return pixel;
}

// Tactical world-coordinate view position, original006A66B0 (255 body + 1 NOP).
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
#include "shared/tactical.hpp"

void Tactical::Unknown_006A66B0(CoordStruct const &coord)
{
    Point2D pixel = Coord_To_Pixel_Absolute(coord);
    pixel -= Point2D(TacPixelX,TacPixelY);
    pixel += Point2D(TacPixelX,TacPixelY);
    Unknown_006A6640(pixel);
}
