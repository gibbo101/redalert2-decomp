// void __fastcall Init_Theater_00519e70(int theater) -- 0x00519E70
// Body 0x00519E70-0x0051A263 (1012 bytes). Tiberian Sun's Init_Theater: reopens the theater mixfiles,
// loads the theater palette (unknown_palette_837e10, the game palette), copies it to the original
// palette (0x00838110), loads UNIT<suffix>.PAL into the scheme palette and rebuilds every colour
// scheme's converters from the two.
#include "shared/win32_api.hpp"
#include "shared/cd.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/convert.hpp"
#include "shared/anim_type.hpp"
#include "shared/id_source.hpp"
#include "shared/session_state.hpp"
#include "shared/color_scheme.hpp"
#include "shared/techno_type.hpp"
#include "shared/ms_engine.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?unknown_palette_838110@@3VPaletteClass@@A=00838110
// @ref ?unknown_palette_838a10@@3VPaletteClass@@A=00838a10
// @ref ??4PaletteClass@@QAEAAV0@ABV0@@Z=00603080
// @ref ?Unknown_00663B40@ColorScheme@@QAEXPAVPaletteClass@@0HHH@Z=00663b40
// @ref ?Unknown_00603750@@YIXH@Z=00603750
// @ref ?Load_Palettes@TechnoTypeClass@@SIXXZ=006df640
// @ref ??_C@_06IEDF@?$CFs?4PAL?$AA@=007dd8b8
// @ref ??_C@_06JJNO@?$CFs?4MIX?$AA@=007dd8ec
// @ref ??_C@_0BB@GEDM@Init?5theater?5?$CFs?6?$AA@=007dd8d8
// @ref ??_C@_0L@ENDN@ISOGEN?4MIX?$AA@=007dd8c0
// @ref ??_C@_0L@MBCJ@UNIT?$CFs?4PAL?$AA@=007dd8ac
// @ref ??_C@_0M@LBHJ@GENERIC?4MIX?$AA@=007dd8cc

extern PaletteClass unknown_palette_838110;     // 0x00838110 the theater palette as loaded (TS OriginalPalette)
extern PaletteClass unknown_palette_838a10;     // 0x00838A10 the unit palette (TS SchemePalette)
void __fastcall Unknown_00603750(int theater);  // 0x00603750

template<class T> inline T min(T a, T b) { return (a < b) ? a : b; }

void __fastcall Init_Theater_00519e70(int theater)
{
    char fullname[16];
    char shortname[16];
    char isofullname[16];

    wsprintfA(fullname, "%s.MIX", Theaters[theater].Root);
    wsprintfA(isofullname, "%s.MIX", Theaters[theater].IsoRoot);
    wsprintfA(shortname, "%s.MIX", Theaters[theater].Suffix);
    Debug_Printf("Init theater %s\n", Theaters[theater].Name);

    unknown_id_source_a3d290->Theater = theater;
    unknown_session_a3d298.Loading_Progress_00672160(8);

    if (unknown_id_source_a3d290->Theater != 1
        && (unknown_loaded_theater_7d88dc == 1 || unknown_loaded_theater_7d88dc == -1)) {
        if (unknown_theater_mix_8374c8 != 0) {
            delete unknown_theater_mix_8374c8;
        }
        unknown_theater_mix_8374c8 = new MixFileClass<CCFileClass>("GENERIC.MIX", &FastKey);
        unknown_theater_mix_8374c8->Cache();
    }

    if (unknown_id_source_a3d290->Theater != unknown_loaded_theater_7d88dc) {
        if (unknown_theater_mix_8374c0 != 0) {
            delete unknown_theater_mix_8374c0;
        }
        unknown_theater_mix_8374c0 = new MixFileClass<CCFileClass>(fullname, &FastKey);

        if (unknown_theater_mix_8374c4 != 0) {
            delete unknown_theater_mix_8374c4;
        }
        unknown_theater_mix_8374c4 = new MixFileClass<CCFileClass>(shortname, &FastKey);
        unknown_theater_mix_8374c4->Cache();
        unknown_theater_mix_8374c0->Cache();
        unknown_session_a3d298.Loading_Progress_00672160(6);

        if (unknown_theater_mix_8374cc != 0) {
            delete unknown_theater_mix_8374cc;
        }
        unknown_theater_mix_8374cc = new MixFileClass<CCFileClass>(isofullname, &FastKey);

        if (unknown_theater_mix_8374d0 != 0) {
            delete unknown_theater_mix_8374d0;
        }
        unknown_theater_mix_8374d0 = new MixFileClass<CCFileClass>("ISOGEN.MIX", &FastKey);
        unknown_session_a3d298.Loading_Progress_00672160(12);

        wsprintfA(fullname, "%s.PAL", Theaters[theater].Root);
        unsigned char const *ptr = (unsigned char const *)MixFileClass<CCFileClass>::Retrieve(fullname);
        if (ptr != 0) {
            for (int color = 0; color < 256; color++) {
                unsigned char r = (unsigned char)((*ptr++) << 2);
                unsigned char g = (unsigned char)((*ptr++) << 2);
                unsigned char b = (unsigned char)((*ptr++) << 2);
                unknown_palette_837e10[color] = RGBClass(r, g, b);
            }
        } else {
            for (int color = 0; color < 256; color++) {
                unknown_palette_837e10[color] = RGBClass(color, 255 - color, (color << 2) & 0xFF);
            }
        }
        unknown_palette_838110 = unknown_palette_837e10;

        wsprintfA(fullname, "UNIT%s.PAL", Theaters[theater].Suffix);
        PaletteClass const *unitpal = (PaletteClass const *)MixFileClass<CCFileClass>::Retrieve(fullname);
        unknown_481fb0();
        if (unitpal != 0) {
            unknown_palette_838a10 = *unitpal;
        }
        for (int index = 0; index < 256; index++) {
            unknown_palette_838a10[index] = RGBClass(
                (unsigned char)(unknown_palette_838a10[index].Red << 2),
                (unsigned char)(unknown_palette_838a10[index].Green << 2),
                (unsigned char)(unknown_palette_838a10[index].Blue << 2));
        }

        int last_percent = 12;
        int prog_step = ColorSchemes.Count() / (25 - 12);
        for (int s = 0; s < ColorSchemes.Count(); s++) {
            ColorSchemes[s]->Unknown_00663B40(&unknown_palette_838a10, &unknown_palette_837e10, 1000, 1000, 1000);
            int percent = (min(12 + (s / prog_step), 25));
            if (percent != last_percent) {
                unknown_session_a3d298.Loading_Progress_00672160(percent);
                last_percent = percent;
            }
            unknown_481fb0();
        }
        Unknown_00603750(theater);
        TechnoTypeClass::Load_Palettes();
        unknown_session_a3d298.Loading_Progress_00672160(25);
    }
}
