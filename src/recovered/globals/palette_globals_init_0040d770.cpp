// Global palettes, the mixfile key, a random generator and screen rectangles defined in the unit
// at 0x0040CE70 after the Map global and its lists (.CRT$XCU 0x007C9170-0x007C91A4). The first
// nine initializers run PaletteClass's constructors (the inline default one zeroes 256 RGB
// entries; black 0x00837510 and white 0x00838410 fill through 0x00602FD0).
#define RA2_PALETTE_CONSTRUCTORS
#include "shared/convert.hpp"
#include "shared/pkey.hpp"
#include "shared/random2.hpp"
#include "shared/rect.hpp"
// @ref ??0PaletteClass@@QAE@ABVRGBClass@@@Z=00602fd0
// @ref ?unknown_palette_838710@@3VPaletteClass@@A=00838710
// @ref ?unknown_palette_837e10@@3VPaletteClass@@A=00837e10
// @ref ?unknown_palette_838a10@@3VPaletteClass@@A=00838a10
// @ref ?unknown_palette_837510@@3VPaletteClass@@A=00837510
// @ref ?unknown_palette_838410@@3VPaletteClass@@A=00838410
// @ref ?unknown_palette_838110@@3VPaletteClass@@A=00838110
// @ref ?unknown_palette_837b10@@3VPaletteClass@@A=00837b10
// @ref ?unknown_palette_838d10@@3VPaletteClass@@A=00838d10
// @ref ?unknown_palette_837810@@3VPaletteClass@@A=00837810
// @ref ?FastKey@@3VPKey@@A=00839010
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ??0Random2Class@@QAE@I@Z=00638790
// @ref ?unknown_rect_839610@@3VRect@@A=00839610
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_window_839640@@3VRect@@A=00839640
// @ref ?XMP_Init@@YIXPAKKH@Z=005a7ca0

PaletteClass unknown_palette_838710;
PaletteClass unknown_palette_837e10;
PaletteClass unknown_palette_838a10;
PaletteClass unknown_palette_837510(RGBClass(0, 0, 0));
PaletteClass unknown_palette_838410(RGBClass(255, 255, 255));
PaletteClass unknown_palette_838110;
PaletteClass unknown_palette_837b10;
PaletteClass unknown_palette_838d10;
PaletteClass unknown_palette_837810;
// The key the mixfiles are opened with (0x00839010).
PKey FastKey;
// A random number generator seeded with 0 (0x00839218).
Random2Class unknown_random_839218(0);
// An empty rectangle (0x00839610).
Rect unknown_rect_839610(0, 0, 0, 0);
// The tactical area: X, Y, width, height (0x00839630).
Rect unknown_rect_839630(0, 0, 640, 400);
// A screen-sized clipping window (0x00839640).
Rect unknown_window_839640(0, 0, 640, 400);
