// void __fastcall Unknown_006F3A20(Surface *surface, Rect const &window, bool arg3) -- 0x006F3A20
// Runs 0x006F3650, then 0x006F3930 with the drawer at 0x00AC1188 and the shapes at 0x00AC1128
// and 0x00AC1010 (hypothesis).
#include "shared/rect.hpp"
// @ref ?Unknown_006F3650@@YIXPAVSurface@@ABVRect@@_N@Z=006f3650
// @ref ?Unknown_006F3930@@YIXPAVSurface@@ABVRect@@PAVConvertClass@@PBUShapeFileStruct@@3@Z=006f3930
// @ref ?unknown_drawer_ac1188@@3PAVConvertClass@@A=00ac1188
// @ref ?unknown_shape_ac1128@@3PAUShapeFileStruct@@A=00ac1128
// @ref ?unknown_shape_ac1010@@3PAUShapeFileStruct@@A=00ac1010
class Surface;
class ConvertClass;
struct ShapeFileStruct;
void __fastcall Unknown_006F3650(Surface *surface, Rect const &window, bool arg3);
void __fastcall Unknown_006F3930(Surface *surface, Rect const &window, ConvertClass *drawer, ShapeFileStruct const *shape640, ShapeFileStruct const *shape);
extern ConvertClass *unknown_drawer_ac1188;
extern ShapeFileStruct *unknown_shape_ac1128;
extern ShapeFileStruct *unknown_shape_ac1010;

void __fastcall Unknown_006F3A20(Surface *surface, Rect const &window, bool arg3)
{
    Unknown_006F3650(surface, window, arg3);
    Unknown_006F3930(surface, window, unknown_drawer_ac1188, unknown_shape_ac1128, unknown_shape_ac1010);
}
