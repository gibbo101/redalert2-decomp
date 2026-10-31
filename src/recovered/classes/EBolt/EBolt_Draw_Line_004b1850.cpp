#include "shared/ebolt.hpp"
#include "shared/tactical.hpp"
#include "shared/convert.hpp"
#include "shared/surface.hpp"
extern ConvertClass *unknown_drawer_8323c4;
extern Surface *unknown_surface_839964;
extern Rect unknown_rect_839630;
int __fastcall Unknown_006A2970(int height);
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_surface_839964@@3PAVSurface@@A=00839964
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_tactical_83996c@@3PAVTacticalClass@@A=0083996c
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
// @ref ?Coord_To_Pixel@TacticalClass@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
void EBolt::Draw_Line_004B1850(CoordStruct start,CoordStruct end,int color,int first_depth,int second_depth)
{
    Point2D first_pixel,second_pixel;
    unknown_tactical_83996c->Coord_To_Pixel(start,first_pixel);
    unknown_tactical_83996c->Coord_To_Pixel(end,second_pixel);
    int first_z=first_depth-Unknown_006A2970(start.Z)-2;
    int second_z=second_depth-Unknown_006A2970(end.Z)-2;
    int pixel=unknown_drawer_8323c4->Convert(color);
    // The shared Surface slot13 still exposes raw 32-bit arguments.
    unknown_surface_839964->Unknown_Slot13((int)&unknown_rect_839630,(int)&first_pixel,(int)&second_pixel,
        pixel,first_z,second_z,0);
}
