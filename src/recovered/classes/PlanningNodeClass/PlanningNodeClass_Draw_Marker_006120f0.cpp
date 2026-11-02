#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::Draw_Marker(int color) (0x006120F0)
// Outlines the node marker; a marker on the tactical view is listed among
// the drawn nodes.
#include "shared/planning.hpp"
#include "shared/surface.hpp"

void PlanningNodeClass::Draw_Marker(int color)
{
    ::Rect view = Unknown_006F1F30();
    ::Rect marker = Rect();
    unknown_surface_839964->Draw_Rect(view, marker, color);
    if (view.Is_Overlapping(marker)) {
        unknown_list_00a766d8.Add(this);
    }
}
