// ConvertClass *__fastcall unknown_load_drawer_5ac560(Wstring const &filename) (0x005AC560)
// Reads a 256-colour palette (6-bit components) into 0x00838710 and returns
// a new drawer for it; null without a name, file or data.
#include "shared/ms_anim.hpp"
#include "shared/wstring.hpp"
#include "shared/cc_file_class.hpp"
// @ref ?unknown_palette_838710@@3VPaletteClass@@A=00838710
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?Load_Alloc_Data@@YIPAXAAVFileClass@@@Z=00495230
// @ref ??0ConvertClass@@QAE@ABVPaletteClass@@0PAVSurface@@H_N@Z=00483650

ConvertClass *__fastcall unknown_load_drawer_5ac560(Wstring const &filename)
{
    if (filename == 0) {
        return 0;
    }
    CCFileClass file(filename);
    if (!file.Is_Available()) {
        return 0;
    }
    unsigned char *palette = (unsigned char *)Load_Alloc_Data(file);
    if (palette == 0) {
        return 0;
    }
    for (int index = 0; index < 256; index++) {
        unknown_palette_838710[index] = RGBClass(palette[index * 3] << 2, palette[index * 3 + 1] << 2,
                                                 palette[index * 3 + 2] << 2);
    }
    operator delete(palette);
    return new ConvertClass(unknown_palette_838710, unknown_palette_838710, unknown_surface_839950, 1, false);
}
