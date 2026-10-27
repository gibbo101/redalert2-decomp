#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::Fill_Marker(int color) (0x00612230)
// Fills the inside of the node's marker square.
#include "shared/planning.hpp"
#include "shared/surface.hpp"

void PlanningNodeClass::Fill_Marker(int color)
{
    ::Rect view = Unknown_006F1F30();
    ::Rect marker = Rect();
    marker.X += 1;
    marker.Y += 1;
    marker.Width -= 2;
    marker.Height -= 2;
    unknown_surface_839964->Fill_Rect(view, marker, color);
}
