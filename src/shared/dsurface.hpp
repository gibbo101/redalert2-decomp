// DSurface: a surface backed by a DirectDraw surface (Westwood's dsurface).
//
// Name from RTTI (vtable 0x007A0BE4, 38 slots); methods in dsurface.cpp
// (0x004AA4A0-0x004B14F0). Layout from the constructors 0x004AA4A0,
// 0x004AA610 and 0x004AAB60 and the destructor 0x004AA5A0. The surface
// description is kept up to date by Lock (lpSurface, pitch, pixel format).
#ifndef RA2_SHARED_DSURFACE_HPP
#define RA2_SHARED_DSURFACE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/directdraw.hpp"
#include "shared/surface.hpp"

class RGBClass;

// DirectDraw object the surfaces are created with (0x008523CC).
extern IDirectDraw *DirectDrawObject;
// Clipper attached to the primary surface, released with it (0x00852FB4).
extern IDirectDrawClipper *unknown_clipper_852fb4;
// When set, new surfaces are created as plain offscreen 3D-device
// surfaces (0x00852FD7).
// Either flag enables lost-surface restoration before locking
// (0x00851CB0, 0x00A40D28); with both clear Lock fails.
extern bool unknown_flag_851cb0;
// Allows DirectDraw colour-fill blits in Fill_Rect (0x007D6294).
extern bool unknown_flag_7d6294;

class DSurface : public XSurface {
public:
    static DSurface *__fastcall Create_Primary(DSurface **back_buffer); // 004AA660
    DSurface();                                                     // 0x004AA610
    DSurface(int width, int height, bool system_memory);            // 0x004AA4A0
    DSurface(IDirectDrawSurface *surface);                          // 0x004AAB60
    virtual ~DSurface();                                            // 0x004AA5A0

    virtual bool Copy_From(Rect const &toclip, Rect const &toarea, Surface &source,
                           Rect const &fromclip, Rect const &fromarea,
                           bool trans = false, bool unknown = false);   // slot 3, 0x004AAFD0
    virtual bool Copy_From(Rect const &toarea, Surface &source, Rect const &fromarea,
                           bool trans = false, bool unknown = false);   // slot 2, 0x004AAF80
    virtual bool Copy_From(Surface &source, bool trans = false, bool unknown = false)   // slot 1, 0x004B14C0
    {
        return XSurface::Copy_From(source, trans, unknown);
    }
    virtual bool Fill_Rect(Rect const &fillrect, int color);               // slot 5, 0x004AB4F0
    virtual bool Fill_Rect(Rect const &cliprect, Rect const &fillrect, int color);   // slot 4, 0x004AB520
    virtual bool Fill_Rect_Trans(Rect const &rect, RGBClass const &color, unsigned int percent);  // slot 7, 0x004AB730
    virtual bool Draw_Depth_Shaded_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                       unsigned color, int start_depth, int end_depth, bool write_depth = false);  // slot 13, 0x004AFC30
    virtual bool Unknown_Slot14(int, int, int, int, int, int, int);        // slot 14, 0x004ABBA0
    virtual bool Draw_Depth_Antialiased_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                       RGBClass const &color, int start_depth, int end_depth, bool write_depth,
                                       bool blend_red, bool blend_green, bool blend_blue, float intensity);  // slot 15, 0x004AC650
    virtual bool Unknown_Slot16(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                       RGBClass const &color, float intensity, int start_depth, int end_depth);  // slot 16, 0x004ADE00
    virtual int Draw_Dashed_Line_Depth_Masked(Point2D const &startpoint, Point2D const &endpoint, int color,
                                              bool const *pattern, int phase, bool empty_only);  // slot 19, 0x004B0650
    virtual bool Draw_Line_Depth_Masked(Point2D const &startpoint, Point2D const &endpoint, int color,
                                        bool empty_only);                  // slot 20, 0x004B0D30
    virtual void *Lock(Point2D point = Point2D(0, 0));                              // slot 23, 0x004AAC80
    virtual bool Unlock();                                                 // slot 24, 0x004AAE40
    virtual bool Can_Lock(int x = 0, int y = 0);                           // slot 25, 0x004AADC0
    virtual int Bytes_Per_Pixel();                                         // slot 28, 0x004AAC60
    virtual int Stride();                                                  // slot 29, 0x004AAC70
    virtual bool Is_Direct_Draw() { return true; }                         // slot 33, 0x004B14E0
    // Draws a 16-bit line whose colour runs from from to to: each pixel takes
    // the colour at ratio, which advances by step and bounces between 0 and 1.
    virtual bool Draw_Gradient_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                    RGBClass const &from, RGBClass const &to, float &step,
                                    float &ratio);                         // slot 36, 0x004AF650
    // Whether DirectDraw can accept a blit now (GetBltStatus(DDGBS_CANBLT)).
    virtual bool Can_Blit();                                               // slot 37, 0x004AAE20

    // Device context of the DirectDraw surface (counts as a lock); null
    // when the surface is locked or GetDC fails.
    HDC Get_DC();                                                   // 0x004AABF0
    int Release_DC(HDC dc);                                         // 0x004AAC30
    // The DirectDraw surface has been lost (DDERR_SURFACELOST).
    bool Is_Surface_Lost();                                         // 0x004AAEE0
    // Restores a lost DirectDraw surface and re-establishes an outstanding
    // lock; false when restoration is disabled or fails.
    bool Restore_Check();                                           // 0x004AAF00

private:
    // The body of Restore_Check, expanded inline by Lock, Unlock, Fill_Rect
    // and Restore_Check itself (defined with Lock, 0x004AAC80).
    bool Restore_Lost_Surface();

public:

    // The DirectDraw surface (inline accessor; BinkClass::Open passes it to
    // BinkDDSurfaceType).
    IDirectDrawSurface *Get_DD_Surface() const { return VideoSurfacePtr; }
    // Whether the surface lives in video memory (inline accessor; Get_Performance_Profile 0x0051A880).
    bool Is_Video_Ram() const { return IsVideoRam; }

protected:
    int BytesPerPixel;                          // +0x10
    void *BufferPtr;                            // +0x14 surface memory while locked
    bool IsPrimary;                             // +0x18 primary surface: owns the clipper
    bool IsVideoRam;                            // +0x19 surface lives in video memory
    IDirectDrawSurface *VideoSurfacePtr;        // +0x1C
    DDSURFACEDESC *VideoSurfaceDescription;     // +0x20
};

#endif
