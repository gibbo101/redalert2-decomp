// bool MSFont::Load(bool sidebar) (0x005B3FD0)
// First font only: FULLFNT3.SHP (mixfile cache, else loaded and owned), the
// SIDEFNT3/FULLFNT3 palette into 0x00838710, colour 0x44, the drawer.
#include "shared/msfont.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ??0ConvertClass@@QAE@ABVPaletteClass@@0PAVSurface@@H_N@Z=00483650
// @ref ??_C@_0CC@ELIN@MSFont?3?5AllocLoaded?5FULLFNT3?4SHP@=007e5da8
// @ref ??_C@_0N@HEOG@FULLFNT3?4SHP?$AA@=007e5dcc
// @ref ??_C@_0N@HGLH@FULLFNT3?4PAL?$AA@=007e5d88
// @ref ??_C@_0N@IKPJ@SIDEFNT3?4PAL?$AA@=007e5d98
// @ref ?Load_Alloc_Data@@YIPAXAAVFileClass@@@Z=00495230
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?unknown_font_count_a71858@@3HA=00a71858
// @ref ?unknown_palette_838710@@3VPaletteClass@@A=00838710
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950

bool MSFont::Load(bool sidebar)
{
    CCFileClass file;

    if (unknown_font_count_a71858 == 0) {
        OwnsShape = false;
        Shape = (ShapeFileStruct *)MixFileClass::Retrieve("FULLFNT3.SHP");
        if (Shape == 0) {
            file.Set_Name("FULLFNT3.SHP");
            Shape = (ShapeFileStruct *)Load_Alloc_Data(file);
            OwnsShape = true;
            Debug_Printf("MSFont: AllocLoaded FULLFNT3.SHP\n");
        }
        if (Shape == 0) {
            return false;
        }
        if (sidebar == true) {
            file.Set_Name("SIDEFNT3.PAL");
        } else {
            file.Set_Name("FULLFNT3.PAL");
        }
        unsigned char *palette = (unsigned char *)Load_Alloc_Data(file);
        if (palette == 0) {
            return false;
        }
        for (int index = 0; index < 256; index++) {
            unknown_palette_838710[index] = RGBClass(palette[index * 3] << 2, palette[index * 3 + 1] << 2, palette[index * 3 + 2] << 2);
        }
        unsigned char red = palette[0xCC] << 2;
        unsigned char blue = palette[0xCE] << 2;
        unsigned char green = palette[0xCD] << 2;
        Color.Red = red;
        Color.Green = green;
        Color.Blue = blue;
        Pixel = (((palette[0xCD] << 2) >> unknown_shift_852fcc) << unknown_shift_852fc8)
              | (((palette[0xCE] << 2) >> unknown_shift_852fc4) << unknown_shift_852fc0)
              | (((palette[0xCC] << 2) >> unknown_shift_852fbc) << unknown_shift_852fb8);
        operator delete(palette);
        Drawer = new ConvertClass(unknown_palette_838710, unknown_palette_838710, unknown_surface_839950, 1, false);
        if (Drawer == 0) {
            return false;
        }
        Width = Shape->Width;
        Height = Shape->Height;
    }
    unknown_check_406f30();
    return true;
}
