// bool Tactical::Contains_Selectable_Buildings(Rect rect) (0x006AA180): whether any building on the map shows within the view
// rectangle (TibSun Tactical::Contains_Selectable_Buildings).
#include "shared/tactical.hpp"
#include "shared/building_class.hpp"

bool Tactical::Contains_Selectable_Buildings(Rect rect)
{
    Point2D top_left;
    Point2D bottom_right;
    top_left.X = rect.X + TacPixelX;
    top_left.Y = rect.Y + TacPixelY;
    bottom_right.X = rect.X + TacPixelX + rect.Width;
    bottom_right.Y = rect.Y + TacPixelY + rect.Height;

    for (int i = 0; i < unknown_BuildingClass_list_00a40af8.Count(); i++) {
        BuildingClass *bptr = unknown_BuildingClass_list_00a40af8[i];
        if (bptr->unknown_7d && bptr->unknown_75 && bptr->unknown_74) {
            Point2D point = Coord_To_Pixel_Absolute(bptr->unknown_slot42());
            if (point.X >= top_left.X && point.X <= bottom_right.X && point.Y >= top_left.Y && point.Y <= bottom_right.Y) {
                return true;
            }
        }
    }
    return false;
}
