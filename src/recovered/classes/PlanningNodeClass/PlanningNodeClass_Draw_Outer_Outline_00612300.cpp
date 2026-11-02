#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::Draw_Outer_Outline(int color) (0x00612300)
// Outlines the grown node marker three times, each one pixel further in.
#include "shared/planning.hpp"
#include "shared/surface.hpp"

void PlanningNodeClass::Draw_Outer_Outline(int color)
{
    ::Rect view = Unknown_006F1F30();
    ::Rect rect = Outer_Rect();
    for (int ring = 0; ring < 3; ring++) {
        unknown_surface_839964->Draw_Rect(view, rect, color);
        Planning_Inflate(rect, -1);
    }
}
