// Clip the update bounds, test the translated drawing area, then dispatch a draw.
#include "shared/building.hpp"
#include "shared/tactical.hpp"
extern bool unknown_flag_a40d13;
extern HWND MainWindow;
extern Rect unknown_rect_839630;
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?MainWindow@@=00b263d8
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Coord_To_Pixel@Tactical@@=006a29d0
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
inline bool Overlap_Draw_Bounds(Rect const &clip,Rect const &draw) {
    return clip.X<(int)((unsigned int)draw.Width+(unsigned int)draw.X)
        && clip.Y<(int)((unsigned int)draw.Height+(unsigned int)draw.Y)
        && (int)((unsigned int)clip.Width+(unsigned int)clip.X)>draw.X
        && (int)((unsigned int)clip.Height+(unsigned int)clip.Y)>draw.Y;
}
inline Rect Offset_Draw_Bounds(Rect const &bounds,Point2D const &pixel);
bool BuildingClass::unknown_slot63(Rect *bounds,bool force,bool alternate)
{
    if(unknown_flag_a40d13 || !MainWindow || ((force || unknown_75) && unknown_74 && !unknown_76)) {
        unknown_75=false;
        *bounds=bounds->Intersect(unknown_rect_839630);
        Point2D origin=Point2D(unknown_rect_839630.X,unknown_rect_839630.Y);

        if(Overlap_Draw_Bounds(*bounds,Offset_Draw_Bounds(unknown_slot73(),origin))) {
            Point2D pixel;
            unknown_tactical_83996c->Coord_To_Pixel(unknown_slot42(),pixel);
            if(bounds->X>unknown_rect_839630.X) {
                pixel.X=(int)((unsigned int)pixel.X+(unsigned int)unknown_rect_839630.X-(unsigned int)bounds->X);
            }
            if(bounds->Y>unknown_rect_839630.Y) {
                pixel.Y=(int)((unsigned int)pixel.Y+(unsigned int)unknown_rect_839630.Y-(unsigned int)bounds->Y);
            }
            if(alternate) {
                if(!unknown_5b7) {
                    unknown_slot284(pixel,*bounds);
                    return true;
                }
            } else {
                // Existing int/int declaration is a32-bit ABI view; original passes two addresses.
                unknown_slot67((int)&pixel,(int)bounds);
            }
            return true;
        }
    }
    return false;
}
