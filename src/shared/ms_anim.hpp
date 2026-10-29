// MSAnim and its shape-based animations: the main-screen animation objects
// (MSAnim.cpp by the link order, 0x005AC540-0x005AFEE0; RTTI vtables
// 0x007A6D3C MSAnim, 0x007A6D64 MSShapeAnim, 0x007A6D8C MSFadeAnim,
// 0x007A6DB4 MSOverlayAnim, 9 slots each).
//
// Evidenced: layouts from the constructors 0x005AC6A0 (MSShapeAnim),
// 0x005ACDB0 (MSFadeAnim), 0x005AD370 (MSOverlayAnim) and the destructors;
// the countdown timer idiom (Started = -1 when stopped, the remaining time
// reduced by the elapsed timeGetTime()/16 ticks) in slots 2 and 3; slot 6
// returning the current frame's screen rectangle (centred when flag 0x200
// is set). Names of slots, members and helpers are hypotheses.
#ifndef RA2_SHARED_MS_ANIM_HPP
#define RA2_SHARED_MS_ANIM_HPP

#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
#include "shared/surface.hpp"
#include "shared/shape_file.hpp"
#include "shared/palette.hpp"
#include "shared/wide_string.hpp"
#include "shared/win32_api.hpp"
#include "shared/movie.hpp"
// Inline element access only (MSPCXAnim walks the engine's animation list).
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#endif
#include "shared/vector_class.hpp"

#include "shared/system_timer.hpp"

class Wstring;

// Shared countdown timer type; the full object headers use this provider too.
#include "shared/cd_timer.hpp"

class MSAnim {
public:
    MSAnim() : X(0), Y(0), unknown_0C(false) {}
    MSAnim(int x, int y) : X(x), Y(y), unknown_0C(true) {}
    virtual ~MSAnim();                                          // slot 0 (+0x00) 0x005AC690
    virtual void Set_Unknown_0C(bool value) { unknown_0C = value; }  // slot 1 (+0x04) 0x005AFC00
    // Timer.Stop() spelled out: through Stop() the expansion folds the
    // second Started test the original keeps.
    virtual void Pause()                                        // slot 2 (+0x08) 0x005AFC10
    {
        if (Timer.Started != -1) {
            Timer.DelayTime = Timer;
            Timer.Started = -1;
        }
    }
    virtual void Resume() { Timer.Start(); }                    // slot 3 (+0x0C) 0x005AFC60
    // MSEngine::Draw (0x005B2FB0) calls slot 4 on every animation with the
    // target surface and a rectangle to receive the area to refresh, and
    // deletes the animation when it returns true; slot 5 draws an
    // animation onto a freshly cleared surface (second argument 0).
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty) = 0;     // slot 4 (+0x10)
    virtual void Draw(Surface *surface, Rect const *clip) = 0;         // slot 5 (+0x14) clip 0: everything
    virtual Rect Get_Rect() = 0;                                // slot 6 (+0x18)
    virtual bool Unknown_Slot7() { return false; }              // slot 7 (+0x1C) 0x005AFC80 (MSEngine::Wait_For stops when true)
    virtual void Unknown_Slot8(int unknown1) {}                 // slot 8 (+0x20) 0x005AFC90

    int X;                                  // +0x04
    int Y;                                  // +0x08
    bool unknown_0C;                        // +0x0C
    CDTimerClass<SystemTimerClass> Timer;   // +0x10
};

class MSShapeAnim : public MSAnim {
public:
    MSShapeAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24, bool unknown_34, int flags);  // 0x005AC6A0
    virtual ~MSShapeAnim();                                     // 0x005AC720
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);     // 0x005AC850
    virtual void Draw(Surface *surface, Rect const *clip);          // 0x005ACBB0
    virtual Rect Get_Rect();                                    // 0x005ACD00

    void Set_Frame(int frame);                                  // 0x005AC760
    void Set_Start_Frame(int frame);                            // 0x005AC810
    void Set_End_Frame(int frame);                              // 0x005AC830

    ShapeFileStruct *Shape;     // +0x1C
    ConvertClass *Drawer;       // +0x20
    int unknown_24;             // +0x24
    unsigned Frame;             // +0x28 current frame
    unsigned StartFrame;        // +0x2C
    unsigned EndFrame;          // +0x30
    bool unknown_34;            // +0x34
    int Flags;                  // +0x38 0x200: centred on X/Y
    bool OwnsShape;             // +0x3C Shape was loaded, not a cached mixfile entry
};

class MSFadeAnim : public MSShapeAnim {
public:
    MSFadeAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24, int flags,
               DynamicVectorClass<MSAnim *> *anims);           // 0x005ACDB0
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);     // 0x005ACE30
    virtual void Draw(Surface *surface, Rect const *clip);          // 0x005AD210

    int unknown_40;             // +0x40
    // The engine's animation list (WorldDominationTour passes &engine->Anims):
    // slot 4 redraws the others over each new step.
    DynamicVectorClass<MSAnim *> *Anims;    // +0x44 (may be 0)
};

class MSOverlayAnim : public MSFadeAnim {
public:
    MSOverlayAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24,
                  DynamicVectorClass<MSAnim *> *anims,
                  bool unknown_48, int frame, bool unknown9);    // 0x005AD370
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);     // 0x005AD450
    virtual void Draw(Surface *surface, Rect const *clip);          // 0x005AD6B0
    virtual bool Unknown_Slot7();                               // 0x005AD8C0
    virtual void Unknown_Slot8(int unknown1);                   // 0x005AD840

    bool unknown_48;            // +0x48
};

// The bitmap-font text printer (0x0084E9D0) and the font it draws with
// (0x0084E9E8); classes not recovered (code near 0x00431460-0x00432AC7).
// Names and parameter meanings are hypotheses from the MSBitPrintAnim calls.
class unknown_bit_font_84e9e8 {
public:
    // Stores the clip box (left, top, right, bottom) at +0x30 (0x00431460).
    void Set_Clip_431460(RECT const *box);
};
class unknown_bit_printer_84e9d0 {
public:
    // Draws text in the box x, y, width, height (0x00432490).
    void Print_432490(unknown_bit_font_84e9e8 *font, Surface *surface, unsigned short const *text, int x,
                      int y, int width, int height, int unknown8, int unknown9, int unknown10);
};
extern unknown_bit_printer_84e9d0 *unknown_bit_printer_84e9d0_ptr;   // 0x0084E9D0
extern unknown_bit_font_84e9e8 *unknown_bit_font_84e9e8_ptr;         // 0x0084E9E8

// Unicode text in a rectangle (RTTI vtable 0x007A6E2C).
class MSBitPrintAnim : public MSAnim {
public:
    MSBitPrintAnim(WideString const &text, Rect const &rect, bool unknown_31);  // 0x005AE480
    virtual ~MSBitPrintAnim();                                  // 0x005AE4F0
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);     // 0x005AE560
    virtual void Draw(Surface *surface, Rect const *clip);          // 0x005AE620
    virtual Rect Get_Rect();                                    // 0x005AE520
    virtual bool Unknown_Slot7();                               // 0x005AE550

    void Set_Unknown_30(bool value);                            // 0x005AE510

    WideString Text;            // +0x1C
    Rect TextRect;              // +0x20
    bool unknown_30;            // +0x30 (slot 4 returns its negation)
    bool unknown_31;            // +0x31
};

// Unicode text typed out character by character into a rectangle, one
// character every CharDelay ticks, optionally centring each line
// (RTTI vtable 0x007A6E54). Layout from the constructor 0x005AE6C0.
#include "shared/msfont.hpp"
class MSPrintAnim : public MSAnim {
public:
    MSPrintAnim(WideString const &text, int x, int y, MSFont *font, Rect const &rect, unsigned position,
                int char_delay, bool unknown_30, bool centered);   // 0x005AE6C0
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);     // 0x005AEDA0
    virtual void Draw(Surface *surface, Rect const *clip);          // 0x005AF030
    virtual ~MSPrintAnim() {}
    virtual Rect Get_Rect();                                    // 0x005AF400
    virtual bool Unknown_Slot7();                               // 0x005AF450

    // Fits TextRect to the text, centred in rect when it is not empty
    // (clipped to it), else placed at X, Y (0x005AE7E0; name hypothesis).
    void Set_Rect(Rect const &rect);
    // TextRect sized to the whole text (inline: Set_Rect expands it in both
    // branches; name hypothesis).
    void Measure_Text() { Font->Text_Rect(Text.Get(), TextRect); }
    // Slot 4's line-at-a-time variant: shows the line from LineStart at
    // unknown_50 in three fade steps (unknown_24 0..2), then moves to the
    // next line with a "bleep1" (0x005AF210; no caller, not in the vtable;
    // name hypothesis).
    bool Unknown_5af210(Surface *surface, Rect *dirty);
    // The width of a line up to its end or newline (inline: slot 4 and Draw
    // expand it; name hypothesis).
    int Line_Width(WideString const &line);

    WideString Text;            // +0x1C
    unsigned LineStart;         // +0x20 first character of the line shown at the top
    unsigned Position;          // +0x24 characters typed so far
    unsigned unknown_28;        // +0x28 slot 4 calls after the end of the text
    int CharDelay;              // +0x2C ticks per character
    bool unknown_30;            // +0x30 restore the background and fade in the newest characters
    MSFont *Font;               // +0x34
    Rect TextRect;              // +0x38
    bool unknown_48;            // +0x48 (slot 4 returns its negation once finished)
    bool Centered;              // +0x49 lines centred in TextRect
    int unknown_4C;             // +0x4C the last line's centring offset
    // Used only by 0x005AF210 (the constructor leaves them unset).
    int unknown_50;             // +0x50 y of the line being shown
    Rect unknown_54;            // +0x54 area of the previous step
};

inline int MSPrintAnim::Line_Width(WideString const &line)
{
    int i = 0;
    int width = 0;
    while (line.Get_Char(i) != 0 && line.Get_Char(i) != '\n') {
        width += Font->Char_Width(line.Get_Char(i));
        i++;
    }
    return width;
}

// Breaks text into lines no wider than width less one glyph: each line ends
// at its last space (the space becomes '\n'), or, when the line has none,
// after a '-' or where it runs out of room (a '\n' is inserted); '\n' and
// '@' end a line early. Returns the widest line (0x005AE9A0, __fastcall;
// name hypothesis).
int __fastcall unknown_wrap_text_5ae9a0(WideString &text, MSFont *font, int width);

class Wstring;
class FileClass;


// A Bink movie played in a screen rectangle; every other animation of the
// list is redrawn over each new frame (RTTI vtable 0x007A6DDC).
class MSBinkAnim : public MSAnim {
public:
    MSBinkAnim(Wstring const &name, Surface *surface, DynamicVectorClass<MSAnim *> *anims, Rect const &rect,
               bool unknown_38);                                // 0x005AD8E0
    virtual ~MSBinkAnim();                                      // 0x005AD9A0
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);     // 0x005ADA20
    virtual void Draw(Surface *surface, Rect const *clip);          // 0x005ADAF0
    virtual Rect Get_Rect();                                    // 0x005AD9D0
    virtual bool Unknown_Slot7();                               // 0x005ADA00 no movie, or it finished
    virtual void Unknown_Slot8(int unknown1);                   // 0x005ADB90

    BinkClass *Movie;                       // +0x1C
    Surface *Target;                        // +0x20 given to the player
    Rect MovieRect;                         // +0x24
    DynamicVectorClass<MSAnim *> *Anims;    // +0x34 redrawn over each frame
    bool unknown_38;                        // +0x38
};

// A VQA movie shown in a screen rectangle with an optional PCX picture
// copied into the target when it ends (RTTI vtable 0x007A6E04).
class MSVQAnim : public MSAnim {
public:
    // Plays in `dest`; the source is a centred unknown_8523e0 x unknown_8523e4 box.
    MSVQAnim(Wstring const &name, Surface *surface, DynamicVectorClass<MSAnim *> *anims, Rect const &dest,
             bool unknown_2c);                                  // 0x005ADBA0
    // Plays a 640x400 movie centred on the screen.
    MSVQAnim(Wstring const &name, Surface *surface, DynamicVectorClass<MSAnim *> *anims,
             bool unknown_2c);                                  // 0x005ADD90
    virtual ~MSVQAnim();                                        // 0x005ADF90
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);     // 0x005ADFE0
    virtual void Draw(Surface *surface, Rect const *clip);          // 0x005AE230
    virtual Rect Get_Rect();                                    // 0x005AE3E0
    virtual bool Unknown_Slot7();                               // 0x005AE470
    virtual void Unknown_Slot8(int unknown1);                   // 0x005AE390 recopies the picture

    VQAMovie *Movie;                        // +0x1C
    Surface *Target;                        // +0x20
    DynamicVectorClass<MSAnim *> *Anims;    // +0x24 redrawn over each frame
    Surface *Image;                         // +0x28 "<name>.PCX" (owned)
    bool unknown_2c;                        // +0x2C
    bool Done;                              // +0x2D
};

// Opens a VQA movie (0x005A1010, as declared in Movie_Create_Movie_Handle).
VQAMovie *__fastcall VQA_Unknown_005A1010(char const *filename, Surface *surface, Rect unknown1, Rect area,
                                          int unknown2, int unknown3);

// Loads a palette file into 0x00838710 (6-bit components scaled by 4) and
// returns a new drawer for it, or null (0x005AC560, __fastcall; name is a
// hypothesis).
ConvertClass *__fastcall unknown_load_drawer_5ac560(Wstring const &filename);
extern PaletteClass unknown_palette_838710;     // 0x00838710

// A PCX picture copied into the background surface, then every other
// animation redrawn over it (RTTI vtable 0x007A6E80). Name of the loader and
// member names are hypotheses.
class MSPCXAnim : public MSAnim {
public:
    MSPCXAnim(Wstring const &name, DynamicVectorClass<MSAnim *> *anims, bool unknown_28);   // 0x005AF5F0 centred on Background
    MSPCXAnim(Wstring const &name, DynamicVectorClass<MSAnim *> *anims, Point2D const &position,
              bool unknown_28);                                 // 0x005AF790 loads <name up to '.'>.PCX
    virtual ~MSPCXAnim();                                       // 0x005AF8F0
    virtual bool Unknown_Slot4(Surface *surface, Rect *dirty);     // 0x005AF910
    virtual void Draw(Surface *surface, Rect const *clip);          // 0x005AFA00
    virtual Rect Get_Rect();                                    // 0x005AFBC0
    virtual bool Unknown_Slot7();                               // 0x005AFBF0
    virtual void Unknown_Slot8(int unknown1);                   // 0x005AFB80 recopies the picture

    Surface *Background;                    // +0x1C 0x00839958 when constructed
    DynamicVectorClass<MSAnim *> *Anims;    // +0x20 redrawn over the picture
    Surface *Image;                         // +0x24 the loaded picture (owned)
    bool unknown_28;                        // +0x28
    bool Done;                              // +0x29 set once the picture was shown
    Rect PCXRect;                           // +0x2C picture size at the given position
};

// Reads a PCX file into a new surface (0x0060D110, __fastcall; the other
// arguments are 0 at the only caller here).
Surface *__fastcall unknown_load_pcx_60d110(FileClass *file, int unknown2, int unknown3, int unknown4);

// Shape draw flags for the fade levels 0..3 (0x007E57F0: 0x406, 0x404,
// 0x402, 0x400; translucency bits over 0x400 as in MSShapeAnim::Draw).
extern int unknown_fade_flags_7e57f0[4];

// Shape or null; *allocated tells whether it was loaded into a new block
// (0x00495310, __fastcall; hypothesis).
ShapeFileStruct *__fastcall unknown_load_shape_495310(Wstring const &filename, bool *allocated);

// Surfaces: an animation whose rectangle changes restores the old area of
// 0x00839954 from 0x00839958 (Surface::Copy_From, slot 2).

#endif
