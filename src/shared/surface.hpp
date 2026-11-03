// Surface, XSurface and BSurface: Westwood's drawing-surface hierarchy.
//
// Names from RTTI (vtables 0x0079B020 Surface, 0x0079AF8C XSurface,
// 0x0079AEF8 BSurface; DSurface in shared/dsurface.hpp). Slot meanings are
// evidenced by the code that implements or calls them; names follow the
// Westwood library naming where the behaviour matches, unknown_/Unknown_
// otherwise.
//
// Surface   abstract: dimensions and the virtual drawing interface.
// XSurface  generic software implementations of the drawing primitives in
//           terms of Lock/Unlock (xsurface.cpp, 0x00773950-0x00775190).
// BSurface  a surface over a memory Buffer.
//
// The small inline members are emitted as COMDATs wherever a vtable is
// needed; the copies the linker kept lie at 0x00411270-0x004113F5 (in the
// first object file, AbsType.cpp) and 0x0049ED90 / 0x0049F430.
#ifndef RA2_SHARED_SURFACE_HPP
#define RA2_SHARED_SURFACE_HPP

#include "shared/buffer.hpp"
#include "shared/rect.hpp"

class RGBClass;

class Surface {
public:
    Surface(int width = 0, int height = 0) : Width(width), Height(height) {}
    virtual ~Surface() {}                                                       // slot 0  (+0x00)

    // VC6 groups overloaded virtuals at the first one's position in reverse
    // declaration order, so each overload set is declared last slot first.

    // Copies (blits) the source; trans skips colour 0 (transparent blitters).
    virtual bool Copy_From(Rect const &toclip, Rect const &toarea, Surface &source,
                           Rect const &fromclip, Rect const &fromarea,
                           bool trans = false, bool unknown = false) = 0;      // slot 3  (+0x0C)
    virtual bool Copy_From(Rect const &toarea, Surface &source, Rect const &fromarea,
                           bool trans = false, bool unknown = false) = 0;      // slot 2  (+0x08)
    virtual bool Copy_From(Surface &source, bool trans = false, bool unknown = false) = 0;   // slot 1 (+0x04)
    virtual bool Fill_Rect(Rect const &fillrect, int color) = 0;               // slot 5  (+0x14)
    virtual bool Fill_Rect(Rect const &cliprect, Rect const &fillrect, int color) = 0;   // slot 4 (+0x10)
    virtual bool Fill(int color) = 0;                                          // slot 6  (+0x18)
    // Blends color over rect, percent (0-100) of the way (16-bit surfaces;
    // Simple_Text_Print's shadow box passes black at 60).
    virtual bool Fill_Rect_Trans(Rect const &rect, RGBClass const &color, unsigned int percent) = 0;  // slot 7 (+0x1C)
    virtual bool Draw_Ellipse(Point2D center, int radiusx, int radiusy, Rect cliprect, int color) = 0;  // slot 8 (+0x20)
    virtual bool Put_Pixel(Point2D const &point, int color) = 0;               // slot 9  (+0x24)
    virtual int Get_Pixel(Point2D const &point) = 0;                           // slot 10 (+0x28)
    virtual bool Draw_Line(Point2D const &startpoint, Point2D const &endpoint, int color) = 0;  // slot 12 (+0x30)
    virtual bool Draw_Line(Rect const &cliprect, Point2D const &startpoint,
                           Point2D const &endpoint, int color) = 0;            // slot 11 (+0x2C)
    // TibSun Draw_Depth_Shaded_Line (names from the TibSun reconstruction; LaserDrawClass::Draw_It
    // 0x005334F0 calls slots 13 and 15 where TibSun laser.cpp calls these two).
    virtual bool Draw_Depth_Shaded_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                       unsigned color, int start_depth, int end_depth, bool write_depth = false) = 0;  // slot 13 (+0x34)
    // TibSun Draw_Depth_Glow_Line: brightens the background by glow_strength/256 where the line is in front.
    virtual bool Draw_Depth_Glow_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                      int glow_strength, int start_depth, int end_depth, bool write_depth = false) = 0;  // slot 14 (+0x38)
    virtual bool Draw_Depth_Antialiased_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                       RGBClass const &color, int start_depth, int end_depth, bool write_depth,
                                       bool blend_red, bool blend_green, bool blend_blue, float intensity) = 0;  // slot 15 (+0x3C)
    // RA2 addition (not in TibSun): DSurface 0x004ADE00 scales the colour's three bytes by intensity.
    virtual bool Unknown_Slot16(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                       RGBClass const &color, float intensity, int start_depth, int end_depth) = 0;  // slot 16 (+0x40)
    // Steps along the clipped line calling plotter for every point.
    virtual bool Plot_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                           void (__fastcall *plotter)(Point2D const &)) = 0;   // slot 17 (+0x44)
    // Draws the line with a 16-entry on/off pattern; returns the pattern phase.
    virtual int Draw_Dashed_Line(Point2D const &startpoint, Point2D const &endpoint, int color,
                                 bool const *pattern, int offset) = 0;         // slot 18 (+0x48)
    // Draw_Dashed_Line limited by the depth buffer like Draw_Line_Depth_Masked.
    virtual int Draw_Dashed_Line_Depth_Masked(Point2D const &startpoint, Point2D const &endpoint, int color,
                                              bool const *pattern, int phase, bool empty_only) = 0;  // slot 19 (+0x4C)
    // Draw_Line limited by the depth buffer: plots only where the depth value
    // is zero (empty_only) or only where it is not (16-bit surfaces only).
    virtual bool Draw_Line_Depth_Masked(Point2D const &startpoint, Point2D const &endpoint, int color,
                                        bool empty_only) = 0;                    // slot 20 (+0x50)
    virtual bool Draw_Rect(Rect const &rect, int color) = 0;                   // slot 22 (+0x58)
    virtual bool Draw_Rect(Rect const &cliprect, Rect const &rect, int color) = 0;  // slot 21 (+0x54)
    virtual void *Lock(Point2D point = Point2D(0, 0)) = 0;                              // slot 23 (+0x5C)
    virtual bool Unlock() = 0;                                                 // slot 24 (+0x60)
    // Whether the surface can be locked now (DSurface tries a lock).
    virtual bool Can_Lock(int x = 0, int y = 0) { return true; }              // slot 25 (+0x64)
    virtual bool Unknown_Slot26(Point2D point = Point2D(0, 0)) { return true; }   // slot 26 (+0x68; a point by value: WWMouseClass::Process_Mouse pushes two zeroed registers)
    virtual bool Is_Locked() = 0;                                              // slot 27 (+0x6C)
    virtual int Bytes_Per_Pixel() = 0;                                         // slot 28 (+0x70)
    virtual int Stride() = 0;                                                  // slot 29 (+0x74)
    virtual Rect Get_Rect() { return Rect(0, 0, Width, Height); }              // slot 30 (+0x78)
    virtual int Get_Width() { return Width; }                                  // slot 31 (+0x7C)
    virtual int Get_Height() { return Height; }                                // slot 32 (+0x80)
    virtual bool Is_Direct_Draw() { return false; }                            // slot 33 (+0x84)

protected:
    int Width;      // +0x04
    int Height;     // +0x08
};

class XSurface : public Surface {
public:
    XSurface(int width = 0, int height = 0) : Surface(width, height), LockLevel(0) {}
    virtual ~XSurface() {}

    virtual bool Copy_From(Surface &source, bool trans = false, bool unknown = false);
    virtual bool Copy_From(Rect const &toarea, Surface &source, Rect const &fromarea,
                           bool trans = false, bool unknown = false);
    virtual bool Copy_From(Rect const &toclip, Rect const &toarea, Surface &source,
                           Rect const &fromclip, Rect const &fromarea,
                           bool trans = false, bool unknown = false);
    virtual bool Fill_Rect(Rect const &cliprect, Rect const &fillrect, int color);
    virtual bool Fill_Rect(Rect const &fillrect, int color);
    virtual bool Fill(int color);
    virtual bool Fill_Rect_Trans(Rect const &rect, RGBClass const &color, unsigned int percent);
    virtual bool Draw_Ellipse(Point2D center, int radiusx, int radiusy, Rect cliprect, int color);
    virtual bool Put_Pixel(Point2D const &point, int color);
    virtual int Get_Pixel(Point2D const &point);
    virtual bool Draw_Line(Rect const &cliprect, Point2D const &startpoint,
                           Point2D const &endpoint, int color);
    virtual bool Draw_Line(Point2D const &startpoint, Point2D const &endpoint, int color);
    virtual bool Draw_Depth_Shaded_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                       unsigned color, int start_depth, int end_depth, bool write_depth = false);
    virtual bool Draw_Depth_Glow_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                      int glow_strength, int start_depth, int end_depth, bool write_depth = false);
    virtual bool Draw_Depth_Antialiased_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                       RGBClass const &color, int start_depth, int end_depth, bool write_depth,
                                       bool blend_red, bool blend_green, bool blend_blue, float intensity);
    virtual bool Unknown_Slot16(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                       RGBClass const &color, float intensity, int start_depth, int end_depth);
    virtual bool Plot_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                           void (__fastcall *plotter)(Point2D const &));
    virtual int Draw_Dashed_Line(Point2D const &startpoint, Point2D const &endpoint, int color,
                                 bool const *pattern, int offset);
    virtual int Draw_Dashed_Line_Depth_Masked(Point2D const &startpoint, Point2D const &endpoint, int color,
                                              bool const *pattern, int phase, bool empty_only);
    virtual bool Draw_Line_Depth_Masked(Point2D const &startpoint, Point2D const &endpoint, int color,
                                        bool empty_only);
    virtual bool Draw_Rect(Rect const &cliprect, Rect const &rect, int color);
    virtual bool Draw_Rect(Rect const &rect, int color);
    virtual void *Lock(Point2D point = Point2D(0, 0)) { LockLevel++; return 0; }      // 0x004112E0
    virtual bool Unlock() { LockLevel--; return true; }                        // 0x004112F0
    virtual bool Is_Locked() { return LockLevel != 0; }                        // 0x00411300
    virtual bool Is_Direct_Draw() { return false; }                            // 0x00411310
    // Clipped single-pixel access (slots 34 and 35, introduced here).
    virtual bool Put_Pixel(Point2D const &point, int color, Rect const &cliprect);   // slot 34 (+0x88)
    virtual int Get_Pixel(Point2D const &point, Rect const &cliprect);         // slot 35 (+0x8C)

    // Filled circle drawn as horizontal Draw_Line spans (0x00774C90).
    void Fill_Circle(Point2D center, int radius, Rect cliprect, int color);

protected:
    int LockLevel;  // +0x0C nesting count of Lock calls
};

// Clips a destination and a source rectangle against their surfaces'
// windows so a blit copies only what both can hold (0x00775190; false when
// nothing is left). Called by the surface copies and the game's blitters.
bool __fastcall Clip_Blit_Rects(Rect &toarea, Rect const &towindow, Rect &fromarea, Rect const &fromwindow);

// Clips both areas, decides whether a same-surface copy must run backward
// and locks both surfaces at the areas' top left corners (0x007753B0); the
// short form clips against the surfaces' own rectangles (0x00775360).
bool __fastcall Prep_For_Blit(Surface &dest, Rect const &dcliprect, Rect &drect, Surface &source,
                              Rect const &scliprect, Rect &srect, bool &overlapped, void *&dbuffer,
                              void *&sbuffer);
bool __fastcall Prep_For_Blit(Surface &dest, Rect &drect, Surface &source, Rect &srect, bool &overlapped,
                              void *&dbuffer, void *&sbuffer);

class BSurface : public XSurface {
public:
    BSurface(int width, int height, int bytesperpixel, void *buffer = 0)
        : XSurface(width, height), BytesPerPixel(bytesperpixel), Buff(buffer, width * height * bytesperpixel)
    {
    }
    // No user-declared destructor: the implicit one (inside the scalar
    // deleting destructor 0x004113D0) does not store the BSurface vtable.

    virtual void *Lock(Point2D point = Point2D(0, 0))                          // 0x00411370
    {
        XSurface::Lock();
        return (char *)Buff.Get_Buffer() + point.Y * Stride() + point.X * Bytes_Per_Pixel();
    }
    virtual int Bytes_Per_Pixel() { return BytesPerPixel; }                    // 0x004113B0
    virtual int Stride() { return Get_Width() * BytesPerPixel; }               // 0x004113C0

protected:
    int BytesPerPixel;  // +0x10
    Buffer Buff;        // +0x14 pixel memory (size Width * Height * BytesPerPixel)
};

#endif
