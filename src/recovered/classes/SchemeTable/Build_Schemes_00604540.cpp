// Build the pair of colour schemes for every registered remap colour,00604540.
#include "shared/scheme_table.hpp"
#include "shared/theater_type.hpp"
#include "shared/convert.hpp"
#include "shared/crt_memory.hpp"
extern "C" char *__cdecl _strupr(char *text);
// The physical static MixFileClass::Retrieve entry: filename in ECX, pointer result in EAX.
void const *__fastcall Retrieve_Palette_Data_005956c0(char const *filename);
extern PaletteClass unknown_palette_837e10;
extern char const Scheme_Palette_Dot_007dbe44[];
extern char const *Scheme_Palette_Extension_007eb5e4;
// @ref __strupr=007961e4
// @ref ?Retrieve_Palette_Data_005956c0@@YIPBXPBD@Z=005956c0
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref ?Scheme_Palette_Dot_007dbe44@@3QBDB=007dbe44
// @ref ?Scheme_Palette_Extension_007eb5e4@@3PBDB=007eb5e4
// @ref ?unknown_palette_837e10@@3VPaletteClass@@A=00837e10

DynamicVectorClass<ColorScheme *> *SchemeTable::Build_Schemes(char const *name)
{
    if (unknown_00 == -1) return 0;
    char filename[256];
    strcpy(filename, name);
    strcat(filename, Theaters[unknown_00].Suffix);
    strcat(filename, Scheme_Palette_Dot_007dbe44);
    strcat(filename, Scheme_Palette_Extension_007eb5e4);
    _strupr(filename);
    PaletteClass palette;
    void const *data = Retrieve_Palette_Data_005956c0(filename);
    if (!data) return 0;
    memcpy(&palette, data, sizeof(palette));
    RGBClass color(0, 0, 0);
    for (int index = 0; index < 256; ++index) {
        color = palette[index];
        palette[index].Set(color.Red << 2, color.Green << 2, color.Blue << 2);
    }
    int count = Colors->Count();
    DynamicVectorClass<ColorScheme *> *schemes = new DynamicVectorClass<ColorScheme *>(20);
    for (int scheme_index = 0; scheme_index < count; ++scheme_index) {
        char const *scheme_name = (*Names)[scheme_index];
        HSVClass color = (*Colors)[scheme_index];
        ColorScheme *normal = new ColorScheme(scheme_name, color, &palette, &unknown_palette_837e10, 1, false);
        normal->Index = scheme_index * 2;
        schemes->Add(normal);
        ColorScheme *dark = new ColorScheme(scheme_name, color, &palette, &unknown_palette_837e10, 53, false);
        dark->Index = scheme_index * 2 + 1;
        schemes->Add(dark);
    }
    return schemes;
}
