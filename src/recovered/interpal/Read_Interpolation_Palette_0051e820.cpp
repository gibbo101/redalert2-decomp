// Tiberian Sun's interpal.cpp: the 2x interpolation blend table, its palette and the
// 2x scaling copy. PaletteInterpolationTable (0x00A417E4) holds, for every pair of
// palette entries, the entry closest to their average; InterpolationPalette (0x00A417E0)
// is the palette it is built from; InterpolationPaletteChanged (0x00A517E4) asks for a
// rebuild and CopyType (0x00A517E8) picks the assembly copy routine.
#define RGB_DECLARE_TO_HSV
#include "shared/hsv_class.hpp"
#include "shared/rgb_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/surface.hpp"
#include "shared/main_loop.hpp"
#include "shared/convert.hpp"
// @ref _PaletteInterpolationTable=00a417e4
// @ref _InterpolationPalette=00a417e0
// @ref ?InterpolationPaletteChanged@@3_NA=00a517e4
// @ref ?CopyType@@3HA=00a517e8
// @ref _Asm_Interpolate=00799241
// @ref _Asm_Interpolate_Line_Double=007992e6
// @ref _Asm_Interpolate_Line_Interpolate=0079943b

extern "C" {
void __cdecl Asm_Interpolate(unsigned char *src_ptr, unsigned char *dest_ptr, int lines, int src_width,
    int dest_width);                                                    // 0x00799241
void __cdecl Asm_Interpolate_Line_Double(unsigned char *src_ptr, unsigned char *dest_ptr, int lines,
    int src_width, int dest_width);                                     // 0x007992E6
void __cdecl Asm_Interpolate_Line_Interpolate(unsigned char *src_ptr, unsigned char *dest_ptr, int lines,
    int src_width, int dest_width);                                     // 0x0079943B
}

bool InterpolationPaletteChanged;

extern "C" {
unsigned char PaletteInterpolationTable[256][256];
unsigned char *InterpolationPalette;
}

// Reads the blend table from palette_file_name when it exists (0x0051E820).
void __fastcall Read_Interpolation_Palette(char const *palette_file_name)
{
    CCFileClass palette_file(palette_file_name);

    if (palette_file.Is_Available()) {
        palette_file.Open(FILE_RIGHTS_READ);
        palette_file.Read(&PaletteInterpolationTable[0][0], 256 * 256);
        palette_file.Close();
        InterpolationPaletteChanged = false;
    }
}
