// PaletteClass, ConvertClass and the shape drawer: the colour and
// shape-drawing interfaces the main-screen code calls.
//
// Evidence (MSFont::Load 0x005B3FD0): a 256-entry palette of 3-byte colours
// indexed modulo 256 (signed `% 256` expansion) and assigned as a word+byte
// copy; `new` of 0x188 bytes constructed by 0x00483650 with (palette,
// palette, surface, 1, 0) and destroyed through vtable slot 0; the drawer
// 0x0049EEA0 is __fastcall (surface in ECX, drawer in EDX, 13 stack
// arguments). Names follow Westwood's palette classes; the ConvertClass
// constructor parameters and every drawer argument after `window` are
// hypotheses (`flags` 0x400 and `brightness` 1000 are the values passed).
#ifndef RA2_SHARED_PALETTE_HPP
#define RA2_SHARED_PALETTE_HPP

#include "shared/rect.hpp"
#include "shared/shape_file.hpp"
#include "shared/rgb_class.hpp"
#include "shared/convert.hpp"

class Surface;

// RGBClass: shared/rgb_class.hpp.

// PaletteClass: shared/convert.hpp.

// ConvertClass: shared/convert.hpp.

// The last argument is an 8-byte value pushed from two zeroed registers by
// every caller seen (MSFont 0x005B43D0/0x005B44F0, MSShapeAnim 0x005ACBB0):
// a Point2D passed by value (hypothesis).
void __fastcall CC_Draw_Shape(Surface *surface, ConvertClass *drawer, ShapeFileStruct const *shape, int frame,
                              Point2D const &point, Rect const &window, int flags, int unknown8,
                              int unknown9, int unknown10, int brightness, int unknown12,
                              int unknown13, Point2D offset);                  // 0x0049EEA0

// Reads a whole file into a new heap block (released with operator delete).
// Hypothesis: Westwood's Load_Alloc_Data; the file arrives in ECX.
void *__fastcall Load_Alloc_Data(class FileClass &file);            // 0x00495230

#endif
