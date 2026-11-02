// ShapeFileStruct: a Westwood shape file (header plus frame headers), moved
// unchanged out of shared/wwmouse.hpp so the main-screen code can use it.
// Evidence: WWMouseClass (0x00771A20..) and MSFont (0x005B4300, 0x005B43D0,
// 0x005B44F0) both expand Get_Frame/Get_Frame_Rect inline with the unsigned
// FrameCount test and the per-unit empty rectangle fallback.
#ifndef RA2_SHARED_SHAPE_FILE_HPP
#define RA2_SHARED_SHAPE_FILE_HPP

#include "shared/rect.hpp"
#ifdef RA2_SHAPE_FRAME_COLOR
#include "shared/rgb_class.hpp"
#endif

// One frame header of a shape file (24 bytes).
struct ShapeFileFrameStruct {
#ifdef RA2_DRAW_SHAPE_OPERATIONS
    // Draw_Shape0049EEA0 reads Flags' low byte, then promotes for the shift.
    bool Is_RLE_Compressed() const { return (Flags & 2) != 0; }
#endif
    short X;                // +0x00 placement of the frame's pixels in the shape
    short Y;                // +0x02
    short Width;            // +0x04
    short Height;           // +0x06
#ifdef RA2_DRAW_SHAPE_OPERATIONS
    union {
        int unknown_08;     // preserve the existing raw-word interface
        struct { short Flags; short unknown_0A; };
    };                     // +0x08 (Flags width remains a reference-backed hypothesis)
#else
    int unknown_08;         // +0x08
#endif
#ifdef RA2_SHAPE_FRAME_COLOR
    union {
        int unknown_0C;
        unsigned char Color[4];     // the frame's radar colour (TibSun ShapeRecord::Color)
    };                      // +0x0C
#else
    int unknown_0C;         // +0x0C
#endif
    int unknown_10;         // +0x10
    int DataOffset;         // +0x14 offset of the frame's pixels from the shape header (0: none)
};

// Every object file that uses the shape helpers has its own copy of this
// empty rectangle (0x00B2AF20 wwmous.cpp, 0x00A71848 MSFont, 0x0084ED88 in
// the one that kept Get_Frame_Rect), initialized dynamically (0x007717A0,
// 0x005B3F20).
// A unit can supply its own fallback rectangle instead (AnimType.cpp uses
// shared/unknown_static_rect.hpp's, initialized after the geometry
// constants): define SHAPE_FILE_EMPTY_RECT before including this header.
#ifndef SHAPE_FILE_EMPTY_RECT
static Rect const unknown_empty_rect(0, 0, 0, 0);
#define SHAPE_FILE_EMPTY_RECT unknown_empty_rect
#endif

// A shape file: header followed by FrameCount frame headers.
struct ShapeFileStruct {
#ifdef RA2_DRAW_SHAPE_OPERATIONS
    // Original unsigned range test, factored as in the Westwood shape API.
    bool Is_Shape_Index_Valid(int index) const { return (unsigned)index < (unsigned)FrameCount; }
#endif
    // Header of frame, or null past the last frame (unsigned comparison).
#ifdef RA2_SHAPE_FRAME_SOURCE
    ShapeFileFrameStruct const *Get_Frame(unsigned frame) const;
#else
    ShapeFileFrameStruct const *Get_Frame(unsigned frame) const
    {
#ifdef RA2_DRAW_SHAPE_OPERATIONS
        if (Is_Shape_Index_Valid(frame)) return &Frames[frame];
        return 0;
#else
        return frame < (unsigned)FrameCount ? &Frames[frame] : 0;
#endif
    }
#endif
#ifdef RA2_SHAPE_FRAME_COLOR
    // Colour of a frame, black past the last frame (TibSun ShapeSet::Get_Color;
    // OverlayTypeClass 0x005DD000 expands it).
    RGBClass Get_Color(int frame) const
    {
        ShapeFileFrameStruct const *record = Get_Frame(frame);
        if (record != 0) {
            return RGBClass(record->Color[0], record->Color[1], record->Color[2]);
        }
        return RGBClass(0, 0, 0);
    }
#endif
    // Frame rectangle; the out-of-line copy the linker kept is 0x0045ED50.
#ifdef RA2_SHAPE_RECT_SOURCE
    Rect Get_Frame_Rect(int frame) const;
#else
    Rect Get_Frame_Rect(int frame) const
    {
        ShapeFileFrameStruct const *header = Get_Frame(frame);
        if (header != 0) {
            return Rect(header->X, header->Y, header->Width, header->Height);
        }
        return SHAPE_FILE_EMPTY_RECT;
    }
#endif
    // Frame pixels (Width * Height bytes), or null.
    void const *Get_Frame_Data(int frame) const
    {
        ShapeFileFrameStruct const *header = Get_Frame(frame);
        if (header != 0 && header->DataOffset != 0) {
            return (char const *)this + header->DataOffset;
        }
        return 0;
    }
#ifdef RA2_DRAW_SHAPE_OPERATIONS
    bool Is_RLE_Compressed(int frame) const {
        ShapeFileFrameStruct const *header = Get_Frame(frame);
        if (header) return header->Is_RLE_Compressed();
        return false;
    }
#endif
    // Accessors (WWMouseClass sizes its save-under surfaces with them; the
    // field reads must happen before the Bytes_Per_Pixel call there).
    int Get_Width() const { return Width; }
    int Get_Height() const { return Height; }

    short unknown_00;       // +0x00
    short Width;            // +0x02 largest frame size
    short Height;           // +0x04
    short FrameCount;       // +0x06
    ShapeFileFrameStruct Frames[1];  // +0x08
};

#endif
