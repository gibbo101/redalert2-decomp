// The score screen's fonts (Score.cpp): ScoreFontClass (RTTI vtable
// 0x007A92A0) and its two shape-sheet fonts ScoreFullFontClass
// (0x007A92B8, FULLFNT3.SHP) and ScoreBigFontClass (0x007A92D0). A sheet
// holds three frames per character from '!' (0x21); frame 3n+2 sizes it.
// Layout from the constructors 0x00667840/0x00667870/0x00667DC0; names are
// hypotheses. Every font shares the score screen's three typing sounds
// (TEXT1-3.AUD, loaded by the first font and released by the last).
#ifndef RA2_SHARED_SCORE_FONT_HPP
#define RA2_SHARED_SCORE_FONT_HPP

#include "shared/rect.hpp"

struct ShapeFileStruct;
class ConvertClass;
class Surface;

class ScoreFontClass {
public:
    ScoreFontClass();                                                   // 0x00667840
    ScoreFontClass(int width, int height, ShapeFileStruct const *image, ConvertClass *drawer);   // 0x00667870
    virtual ~ScoreFontClass();                                          // 0x006678B0 (deleting 0x006683D0)
    virtual int Char_Pixel_Width(unsigned short character);             // slot 1 0x00667AA0 (a space is 8)
    virtual int String_Pixel_Width(unsigned short const *string);       // slot 2 0x00667A60
    virtual void Print(Surface *surface, unsigned short const *string, int x, int y, int frame);    // slot 3 0x00667C70
    virtual void Print_Char(Surface *surface, unsigned short character, int x, int y, int frame, int unused);   // slot 4 0x00667B60

    // Loads the typing sounds the first time (0x00667900).
    void Load_Sounds();

    int Width;                      // +0x04
    int Height;                     // +0x08
    ShapeFileStruct const *Image;   // +0x0C
    bool IsAllocated;               // +0x10 Image was read from a loose file
    ConvertClass *Drawer;           // +0x14
};

class ScoreFullFontClass : public ScoreFontClass {
public:
    ScoreFullFontClass(ConvertClass *drawer);                           // 0x00667DC0 (deleting 0x00668430)
};

class ScoreBigFontClass : public ScoreFontClass {
public:
    ScoreBigFontClass(ConvertClass *drawer);                            // 0x00667E80 (deleting 0x00668490)
};

// The typing sounds (0x00AB6FA8: TEXT1.AUD, TEXT2.AUD, TEXT3.AUD) and the
// fonts alive (0x00AB6FA4).
struct ScoreFontSound {
    void const *Data;               // +0x00
    bool IsAllocated;               // +0x04 read from a loose file
};
extern int unknown_score_fonts_ab6fa4;
// Score.cpp's copy of the shape helpers' empty rectangle (0x00AB6F20; see
// shared/shape_file.hpp, SHAPE_FILE_EMPTY_RECT).
extern Rect const unknown_score_empty_rect_ab6f20;
extern ScoreFontSound unknown_score_sounds_ab6fa8[3];

#endif
