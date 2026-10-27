// Point2D and Rect: integer screen points and rectangles (Westwood's
// TPoint2D<int> / TRect<int>).
//
// Layouts from the surface code: Rect is {X, Y, Width, Height} (Get_Rect at
// 0x00411290 stores 0, 0, Width, Height; the line and blit clippers read
// +0x08/+0x0C as extents), Point2D is {X, Y}.
// Intersect (0x0041FDF0) and Clip_Line (0x00775620) are explicit __fastcall
// free functions like the rest of the game's non-member code.
#ifndef RA2_SHARED_RECT_HPP
#define RA2_SHARED_RECT_HPP

struct INIPoint2D;

struct Point2D {
    Point2D() {}
    Point2D(int x, int y) : X(x), Y(y) {}
    // From the point an INI reader returns (defined in shared/ini_class.hpp).
    Point2D(INIPoint2D const &point);

    // Not inlined by the original (out-of-line copy 0x00435540, Blit.cpp).
    Point2D operator+(Point2D const &point) const;
    // Member-wise difference in place (DisplayClass::TacticalClass::Action 0x0049AE70).
    Point2D &operator-=(Point2D const &point) { X -= point.X; Y -= point.Y; return *this; }
    // Member-wise difference (out of line, 0x0047D040 in Cell.cpp; MapClass calls it).
    Point2D operator-(Point2D const &point) const;
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
    Rect(Point2D const &point, int width, int height);

    bool Is_Valid() const { return Width > 0 && Height > 0; }

    // Member-wise comparison (MSShapeAnim::Set_Frame 0x005AC760 compares a
    // saved rectangle with a returned temporary field by field).
    bool operator==(Rect const &rect) const
    {
        return X == rect.X && Y == rect.Y && Width == rect.Width && Height == rect.Height;
    }
    bool operator!=(Rect const &rect) const { return !(*this == rect); }

    // Not inlined by the original (out-of-line copy 0x00435560, Blit.cpp).
    Point2D Top_Left() const;

    // The rectangle moved back by point (out of line, 0x0047D000 in Cell.cpp).
    Rect operator-(Point2D const &point) const;

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
// (0x00775620, hypothesis from the surface line drawers).
bool __fastcall Clip_Line(Point2D &start, Point2D &end, Rect const &rect);

#endif
