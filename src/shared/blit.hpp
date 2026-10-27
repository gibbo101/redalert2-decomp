// Surface-to-surface and surface/buffer copies (Westwood's blit.cpp,
// 0x00434940-0x00435560).
//
// All are __fastcall free functions: the destination surface in ECX and
// the next reference in EDX. The window-taking Bit_Blit/RLE_Blit
// (0x00434B40, 0x004350C0) clip and do the work; the shorter overloads
// supply the surfaces' own rectangles as windows.
#ifndef RA2_SHARED_BLIT_HPP
#define RA2_SHARED_BLIT_HPP

#include "shared/blitter.hpp"
#include "shared/surface.hpp"

class RLEBlitter;

// Depth (ZBuffer, 0x008315B4) and alpha (ABuffer, 0x00839C6C) buffers:
// screen-sized rings of 16-bit values over a BSurface. Layout from the
// blitters (fields +0x00..+0x28; the names follow the use).
class ZBuffer {
public:
    ZBuffer(Rect area); // original00410A60; by-value spelling hypothesis
    ~ZBuffer(); // original00410BD0
    void Clear_Region_00411090(unsigned short color, Rect area); // original00411090
    // Copies an area-sized block of values, starting at the ring origin,
    // into surface at the area's position (0x00410B40).
    void Copy_To(::Surface &surface, Rect area);
    // Stores value into count entries from pointer (0x00410BF0).
    void Fill_Words(unsigned short *pointer, int count, unsigned short value);
    // Scrolls the ring by dx columns and dy rows, clearing what is exposed
    // to value (0x00410C50).
    void Adjust(int dx, int dy, unsigned short value);
    void Clear(unsigned short value);                   // 0x00411050
    // Clears a screen rectangle of the ring to 0x7F (0x004110B0).
    void Clear_Region_004110B0(Rect area);
    // Address of the value for a screen point (wraps at the ring end).
    unsigned short *Get_Buffer_Ptr(Point2D point);       // 0x00411230, by value (ret 8)
    // Keep a scanline pointer inside the ring after advancing it.
    unsigned short *Wrap_Pointer(unsigned short *pointer) const {
        if ((char *)pointer >= BufferTail) pointer = (unsigned short *)((char *)pointer - BufferSize);
        return pointer;
    }
    // Advance a scanline pointer by count values and keep it inside the ring,
    // wrapping at the end when direction is positive, at the start otherwise.
    void Advance_Pointer(unsigned short *&pointer, int count, int direction) const {
        if (direction > 0) {
            pointer += count;
            if ((char *)pointer >= BufferTail) pointer = (unsigned short *)((char *)pointer - BufferSize);
        } else {
            pointer += count;
            if ((char *)pointer < BufferHead) pointer = (unsigned short *)((char *)pointer + BufferSize);
        }
    }
    Rect Area;                  // +0x00 screen area covered
    int BufferOffset;           // +0x10 ring start offset
    BSurface *Surface;          // +0x14
    char *BufferHead;           // +0x18 ring start
    char *BufferTail;           // +0x1C ring end
    int BufferSize;             // +0x20 ring size in bytes
    int MaxValue;               // +0x24
    int Width;                  // +0x28 values per row
    int Height;                 // +0x2C; original allocation0x30
};

class ABuffer {
public:
    // Existing name retained as a hypothesis; this constructor binds instance 00839C6C.
    ABuffer(Rect area); // original 00775B80, by-value screen rectangle
    ~ABuffer(); // original 00775CF0
    void Clear(unsigned short color); // original 00776160
    void Clear_Region_007761A0(unsigned short color, Rect area); // original 007761A0
    // Copies an area-sized block of values, starting at the ring origin,
    // into surface at the area's position (0x00775C60).
    void Copy_To(::Surface &surface, Rect area);
    // Scrolls the ring by dx columns and dy rows, clearing what is exposed
    // to value (0x00775D60).
    void Adjust(int dx, int dy, unsigned short value);
    void Clear_Region_007761C0(Rect area); // original 007761C0
    // Stores value into count entries from pointer (0x00775D00).
    void Fill_Words(unsigned short *pointer, int count, unsigned short value);
    unsigned short *Wrap_Pointer(unsigned short *pointer) const {
        if ((char *)pointer >= BufferTail) pointer = (unsigned short *)((char *)pointer - BufferSize);
        return pointer;
    }
    unsigned short *Get_Buffer_Ptr(Point2D point);       // 0x00776340, by-value point hypothesis
    Rect Area;                  // +0x00
    int BufferOffset;           // +0x10
    BSurface *Surface;          // +0x14
    char *BufferHead;           // +0x18
    char *BufferTail;           // +0x1C
    int BufferSize;             // +0x20
    int MaxValue;               // +0x24
    int Width;                  // +0x28
    int Height;                 // +0x2C; original allocation is 0x30 bytes
};

extern ZBuffer *ZBufferPtr;     // 0x008315B4 (null when no depth buffering)
extern ABuffer *ABufferPtr;     // 0x00839C6C (null when no alpha buffering)

// Rows of the alpha ramp a blit walks (24-byte entries at 0x007CE168,
// indexed by Bit_Blit's second trailing argument). Field meanings unresolved.
struct BlitRamp {
    int unknown_00;             // +0x00
    int Divisor;                // +0x04 used when Flag is set
    int Numerator;              // +0x08 per-row increment of the ramp counter
    int Denominator;            // +0x0C counter wrap
    int Step;                   // +0x10 added to the alpha level on wrap
    bool Flag;                  // +0x14
};
extern BlitRamp BlitRamps[];    // 0x007CE168



// An 8-byte value with a constructor that the RLE core takes by value
// (the wrapper builds it from two zeroed registers). Probably a point
// offset; name and meaning unresolved.
struct BlitPair {
    BlitPair(int x, int y) : X(x), Y(y) {}
    int X;      // +0x00
    int Y;      // +0x04
};

// Bytes needed to hold a width x height block of the surface's pixels.
int __fastcall Buffer_Size(Surface &surface, int width, int height);
// Copies rect of surface into buffer / rect of surface from buffer, through
// a temporary BSurface over the buffer memory; false for an empty rect.
bool __fastcall To_Buffer(Surface &surface, Rect const &rect, Buffer &buffer);
bool __fastcall From_Buffer(Surface &surface, Rect const &rect, Buffer &buffer);

// The core blit (0x00434B40): dest/source windows plus areas inside them.
bool __fastcall Bit_Blit(Surface &dest, Rect const &destwindow, Rect const &destrect, Surface &source,
                         Rect const &sourcewindow, Rect const &sourcerect, Blitter const &blitter,
                         int unknown1, int unknown2, int unknown3, int unknown4);

// RLE-compressed source variant (0x00435060 wrapper, 0x004350C0 core). The
// wrapper passes 0 and BlitPair(0, 0) for the two trailing core arguments.
bool __fastcall RLE_Blit(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect,
                         RLEBlitter const &blitter, int unknown1, int unknown2, int unknown3, int unknown4);
bool __fastcall RLE_Blit(Surface &dest, Rect const &destwindow, Rect const &destrect, Surface &source,
                         Rect const &sourcewindow, Rect const &sourcerect, RLEBlitter const &blitter,
                         int unknown1, int unknown2, int unknown3, int unknown4,
                         int unknown5, BlitPair unknown6);

#endif
