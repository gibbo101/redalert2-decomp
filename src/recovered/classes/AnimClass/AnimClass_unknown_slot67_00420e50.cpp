// void AnimClass::unknown_slot67(int arg1, int arg2) (0x00420E50, slot 67)
// Draws the animation (TibSun AnimClass::Draw_It) at the screen point arg1
// within the window arg2: skipped when the frame rate is too low for its
// detail level, when hidden or fogged; the type's translucency at enough
// detail, the drawer and brightness of its palette, its cell or its own,
// then the bouncing shadow, the tiled column, the flat or upright frame and
// the shadow frame.
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
#include "shared/cell_class.hpp"
#include "shared/house.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/frame_rate.hpp"
#include "shared/combat.hpp"
#include "shared/palette.hpp"
#include "shared/terrain.hpp"
// @ref ?Unknown_0053D840@@YAIXZ=0053d840
// @ref ?unknown_a6eb1c@@3IA=00a6eb1c
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref _unknown_empty_rect=0084c690
// @ref __real@8@3ffe9999999999999800=0079c270
// @ref __real@8@3ffdcccccccccccccc00=0079c268
// @ref __real@8@3ffccccccccccccccc00=0079c260

void AnimClass::unknown_slot67(int arg1, int arg2)
{
    Point2D const &point = *(Point2D const *)arg1;
    Rect const &cliprect = *(Rect const *)arg2;
    if (unknown_a6eb1c < Unknown_0053D840() && Class->DetailLevel > 1) {
        return;
    }
    if (!unknown_17d && Class->DetailLevel <= unknown_a40b2c && (!unknown_179 || !Class->ShouldFogRemove)) {
        ShapeFileStruct const *shapefile = (ShapeFileStruct const *)unknown_slot26();
        if (shapefile != 0) {
            int flags = unknown_170;
            int shapenum = Class->Start + Stage;
            if (unknown_101) {
                flags |= 4;
            }

            if (Class->TranslucencyDetailLevel <= unknown_a40b2c) {
                if (Class->Translucent) {
                    if (unknown_158 >= 15) return;
                    if (Stage > Class->End * 0.6) {
                        flags |= 6;
                    } else if (Stage > Class->End * 0.4) {
                        flags |= 4;
                    } else if (Stage > Class->End * 0.2) {
                        flags |= 2;
                    }
                } else if (Class->Translucency > 0) {
                    if (unknown_158 >= 15) return;
                    if (Class->Translucency == 25) {
                        flags |= 2;
                    } else if (Class->Translucency == 50) {
                        flags |= 4;
                    } else if (Class->Translucency == 75) {
                        flags |= 6;
                    }
                } else if (unknown_158 != 0) {
                    if (unknown_158 > 15) return;
                    if (unknown_158 > 10) {
                        flags |= 4;
                    } else if (unknown_158 > 5) {
                        flags |= 4;
                    } else {
                        flags |= 2;
                    }
                }
            }

            if ((flags & 1) == 0) {
                flags |= 0x800;
            }

            int height = unknown_slot108();
            int brightness = 1000;
            ConvertClass *convert;

            if (Class->IsVeins) {
                convert = (ConvertClass *)unknown_list_ab6ef8[unknown_player_a35db4->ColorSchemeIndex]->unknown_30c;
                if (!Class->UseNormalLight) {
                    brightness = Map[unknown_slot42()].unknown_10c;
                }
            } else if (unknown_176) {
                CellClass *cellptr = &Map[Cell(unknown_slot42())];
                if (cellptr->unknown_34 == 0) {
                    cellptr->Init_Drawer(0, 0x10000, 0, 1000, 1000, 1000);
                }
                convert = (ConvertClass *)cellptr->unknown_34;
                if (!Class->UseNormalLight) {
                    brightness = cellptr->unknown_10c;
                }
            } else if (unknown_bc != 0) {
                convert = (ConvertClass *)unknown_bc;
                if (!Class->UseNormalLight) {
                    brightness = unknown_e4;
                }
            } else {
                convert = Unit_Draw_Convert_008323C0;
                if (Class->AltPalette) {
                    convert = (ConvertClass *)unknown_list_ab6ef8[0]->unknown_30c;
                }
                if (!Class->UseNormalLight) {
                    brightness = Map[Cell(unknown_slot42())].unknown_10a;
                }
            }

            if (unknown_174) {
                CC_Draw_Shape(unknown_surface_83995c, convert, shapefile, shapenum, point + Point2D(0, Class->YDrawOffset + Unknown_006A2970(height)), cliprect, 0x2601, 0, Class->YDrawOffset - Unknown_006A2970(unknown_slot110()), 0, 1000, 0, 0, Point2D(0, 0));
            }

            if (Class->Tiled) {
                int frameheight = shapefile->Get_Frame_Rect(0).Height;
                Point2D origin = point;
                Point2D drawpoint = origin - Point2D(0, frameheight / 2);
                bool done = false;
                int height_offset = ZAdjust + Class->YDrawOffset - Unknown_006A2970(unknown_slot110()) - 50;
                while (!done) {
                    CC_Draw_Shape(unknown_surface_83995c, Unit_Draw_Convert_008323C0, shapefile, shapenum, Point2D(origin.X, drawpoint.Y + Class->YDrawOffset), unknown_rect_839630, flags | 0x2000, 0, height_offset, 2, brightness, 0, 0, Point2D(0, 0));
                    if (drawpoint.Y < 0) done = true;
                    drawpoint.Y -= frameheight;
                    height_offset -= frameheight + frameheight / 2;
                }
            } else if (Class->Flat) {
                CC_Draw_Shape(unknown_surface_83995c, convert, shapefile, shapenum, point + Point2D(0, Class->YDrawOffset), cliprect, flags | 0x2000, 0, ZAdjust + Class->YDrawOffset - Unknown_006A2970(unknown_slot110()) - 3, 0, brightness, 0, 0, Point2D(0, 0));
            } else {
                CC_Draw_Shape(unknown_surface_83995c, convert, shapefile, shapenum, point + Point2D(0, Class->YDrawOffset), cliprect, flags | 0x2000, 0, ZAdjust + Class->YDrawOffset - Unknown_006A2970(unknown_slot110()) - 2, 2, brightness, 0, 0, Point2D(0, 0));
                if (Class->Shadow) {
                    CC_Draw_Shape(unknown_surface_83995c, convert, shapefile, shapenum + shapefile->Get_Count() / 2, point, cliprect, flags & ~6 | 0x601, 0, -2 - Unknown_006A2970(unknown_slot110()), 0, 1000, 0, 0, Point2D(0, 0));
                }
            }
        }
    }
}
