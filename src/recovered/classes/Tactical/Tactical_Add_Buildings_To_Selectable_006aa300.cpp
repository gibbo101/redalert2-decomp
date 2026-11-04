// void Tactical::Add_Buildings_To_Selectable(Rect rect) (0x006AA300): lists every building of the map that shows within the
// view rectangle in the object pixels table (TibSun Tactical::Add_Buildings_To_Selectable).
#include "shared/tactical.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"

void Tactical::Add_Buildings_To_Selectable(Rect rect)
{
    Point2D top_left;
    Point2D bottom_right;
    top_left.X = rect.X + TacPixelX;
    top_left.Y = rect.Y + TacPixelY;
    bottom_right.X = rect.X + TacPixelX + rect.Width;
    bottom_right.Y = rect.Y + TacPixelY + rect.Height;

    for (int i = 0; i < unknown_BuildingClass_list_00a40af8.Count(); i++) {
        BuildingClass *bptr = unknown_BuildingClass_list_00a40af8[i];
        if (bptr->unknown_7d && bptr->unknown_74 && !bptr->Type->InvisibleInGame) {
            CoordStruct coord = bptr->Coord;
            Point2D point = Coord_To_Pixel_Absolute(coord);
            if (point.X >= top_left.X && point.X <= bottom_right.X && point.Y >= top_left.Y && point.Y <= bottom_right.Y) {
                Point2D view(TacPixelX, TacPixelY);
                point = point - view;
                Unknown_006AA510(bptr, point.X, point.Y);
            }
        }
    }
}
