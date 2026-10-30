// Point2D and Rect: integer screen points and rectangles (Westwood's
// TPoint2D<int> / TRect<int>).
//
// Layouts from the surface code: Rect is {X, Y, Width, Height} (Get_Rect at
// 0x00411290 stores 0, 0, Width, Height; the line and blit clippers read
// +0x08/+0x0C as extents), Point2D is {X, Y}.
//
// Two point types: the corner and the point arithmetic of Rect (Top_Left,
// operator+, operator-) produce TPoint2D, the surfaces take Point2D. Passing
// a TPoint2D result by value to Surface::Lock goes through Point2D's
// converting constructor, which VC6 builds in the argument slot (sub esp, 8;
// mov ecx, esp; two member copies: Prep_For_Blit 0x007753B0 and the other
// Lock(rect.Top_Left()) callers), where a Point2D local is pushed.
// Intersect (0x0041FDF0) and Clip_Line (0x00775620) are explicit __fastcall
// free functions like the rest of the game's non-member code.
#ifndef RA2_SHARED_RECT_HPP
#define RA2_SHARED_RECT_HPP

struct INIPoint2D;

// The point type of Rect's corner arithmetic (name after Westwood's library
// TPoint2D<int>; possibly the same type as INIPoint2D, which also converts
// into Point2D).
struct TPoint2D {
    TPoint2D() {}
    TPoint2D(int x, int y) : X(x), Y(y) {}

    // Not inlined by the original (out-of-line copy 0x00435540, Blit.cpp).
    TPoint2D operator+(TPoint2D const &point) const;
    // Member-wise difference (out of line, 0x0047D040 in Cell.cpp; MapClass calls it).
    TPoint2D operator-(TPoint2D const &point) const;

    int X;          // +0x00
    int Y;          // +0x04
};

struct Point2D {
    Point2D() {}
    Point2D(int x, int y) : X(x), Y(y) {}
    // From the point an INI reader returns (defined in shared/ini_class.hpp).
    Point2D(INIPoint2D const &point);
    // From a Rect corner or a sum of them.
    Point2D(TPoint2D const &point) : X(point.X), Y(point.Y) {}

    // Member-wise sum in place (Westwood's Overlay_Shadow_Render_Rect, CellClass 0x00475100).
    Point2D &operator+=(Point2D const &point) { X += point.X; Y += point.Y; return *this; }
    // Member-wise difference in place (DisplayClass::TacticalClass::Action 0x0049AE70).
    Point2D &operator-=(Point2D const &point) { X -= point.X; Y -= point.Y; return *this; }
    // Member-wise sum by value (CellClass::unknown_475440 and its callers: Westwood's Overlay_Draw_Offset, Draw_Overlay_Shadow).
    Point2D operator+(Point2D const &point) const { return Point2D(X + point.X, Y + point.Y); }
    // Member-wise difference by value (VeinholeMonsterClass 0x00711AA0: the Y
    // difference is computed first, as a constructor argument).
    Point2D operator-(Point2D const &point) const { return Point2D(X - point.X, Y - point.Y); }
    int Length() const; // 0047D060, integer table-sqrt vector length
    // Member-wise comparison (the Point2D vectors of MSChoice.cpp,
    // 0x005B1930/0x005B1A90).
    bool operator==(Point2D const &point) const { return X == point.X && Y == point.Y; }
    bool operator!=(Point2D const &point) const { return X != point.X || Y != point.Y; }
    int X;          // +0x00
    int Y;          // +0x04
};

class Rect {
public:
    Rect() {}
    Rect(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height) {}
    Rect(TPoint2D const &point, int width, int height);

    bool Is_Valid() const { return Width > 0 && Height > 0; }
    // All four members at once (MSPrintAnim 0x005AF210 stores the reported
    // area through it: a charged four-store callee; name hypothesis).
    void Set(int x, int y, int width, int height)
    {
        X = x;
        Y = y;
        Width = width;
        Height = height;
    }

    // Member-wise comparison (MSShapeAnim::Set_Frame 0x005AC760 compares a
    // saved rectangle with a returned temporary field by field).
    bool operator==(Rect const &rect) const
    {
        return X == rect.X && Y == rect.Y && Width == rect.Width && Height == rect.Height;
    }
    bool operator!=(Rect const &rect) const { return !(*this == rect); }

    // Not inlined by the original (out-of-line copy 0x00435560, Blit.cpp).
    TPoint2D Top_Left() const;

    // The rectangle moved back by point (out of line, 0x0047D000 in Cell.cpp).
    Rect operator-(TPoint2D const &point) const;
    // Moves the origin back by a point (FoggedObjectClass 0x004C00F0).
    Rect &operator-=(Point2D const &point) { X -= point.X; Y -= point.Y; return *this; }

    // The two rectangles overlap, shared edges excluded (TibSun TRect::Is_Overlapping; Tactical 0x006AA090).
    bool Is_Overlapping(Rect const &rect) const
    {
        return X < rect.X + rect.Width && Y < rect.Y + rect.Height && X + Width > rect.X && Y + Height > rect.Y;
    }
    // The rectangle moved by a point (TibSun TRect::operator+, here member-wise inline).
    Rect operator+(Point2D const &point) const { return Rect(X + point.X, Y + point.Y, Width, Height); }

    // Overlap with another rectangle (the free Intersect below).
    Rect Intersect(Rect const &rect, int *x = 0, int *y = 0) const;

    // The point lies inside the rectangle (right and bottom edges excluded).
    bool Is_Point_Within(Point2D const &point) const
    {
        return point.X >= X && point.X < X + Width && point.Y >= Y && point.Y < Y + Height;
    }

    int X;          // +0x00
    int Y;          // +0x04
    int Width;      // +0x08
    int Height;     // +0x0C
};

// The point moved by the window's origin: window-relative to surface
// coordinates (the clipped line drawers).
inline Point2D Offset_Point(Point2D const &point, Rect const &window)
{
    return Point2D(point.X + window.X, point.Y + window.Y);
}

// The rectangle moved by (x, y) (Tactical's layer redraws 0x006A9E10,
// 0x006A9F60 move a drawn area onto the screen with it; name hypothesis).
inline Rect Offset_Rect(Rect const &rect, int x, int y)
{
    return Rect(rect.X + x, rect.Y + y, rect.Width, rect.Height);
}

// The two rectangles overlap (shared edges excluded; Tactical 0x006A9E10,
// 0x006A9F60; name hypothesis).
inline bool Rects_Overlap(Rect const &rect1, Rect const &rect2)
{
    return rect1.X < rect2.X + rect2.Width && rect1.Y < rect2.Y + rect2.Height
        && rect1.X + rect1.Width > rect2.X && rect1.Y + rect1.Height > rect2.Y;
}

// Overlap of two rectangles; x/y (optional) receive the offset adjustments.
// Hypothesis from the callers (0x0041FDF0): rect1 in EDX, rect2 and the two
// optional pointers on the stack, the result through the hidden pointer.
Rect __fastcall Intersect(Rect const &rect1, Rect const &rect2, int *x = 0, int *y = 0);

inline Rect Rect::Intersect(Rect const &rect, int *x, int *y) const
{
    return ::Intersect(*this, rect, x, y);
}

// The smallest rectangle holding both (Westwood's wwlib Union, a function
// template); an invalid rectangle contributes nothing. RadarClass::Draw_It
// 0x0062F580 expands it inline; the BuildingType unit's instance 0x0045EFE0
// is the out-of-line copy the cell and building code call (__fastcall).
template<class T>
T __fastcall Union(T const &rect1, T const &rect2)
{
    if (rect1.Is_Valid()) {
        if (rect2.Is_Valid()) {
            T result = rect1;
            if (result.X > rect2.X) {
                result.Width += result.X - rect2.X;
                result.X = rect2.X;
            }
            if (result.Y > rect2.Y) {
                result.Height += result.Y - rect2.Y;
                result.Y = rect2.Y;
            }
            if (result.X + result.Width < rect2.X + rect2.Width) {
                result.Width = ((rect2.X + rect2.Width) - result.X) + 1;
            }
            if (result.Y + result.Height < rect2.Y + rect2.Height) {
                result.Height = ((rect2.Y + rect2.Height) - result.Y) + 1;
            }
            return result;
        }
        return rect1;
    }
    return rect2;
}

// Clips a line to a rectangle; false when nothing of it is inside
// (0x00775620).
bool __fastcall Clip_Line(Point2D &start, Point2D &end, Rect const &rect);
// Cohen-Sutherland region code of a point against rect (0x007758F0; Clip_Line
// expands it inline).
int __fastcall Clip_Line_Outcode(Rect const &rect, double x, double y);

// Moves every side of a rectangle inwards by amount (outwards when negative)
// (0x006F1B00).
void __fastcall Unknown_Rect_Shrink_006F1B00(Rect *rect, int amount);

#endif
