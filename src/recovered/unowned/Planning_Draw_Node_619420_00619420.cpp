#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Draw_Node_619420(PlanningNodeClass *node) (0x00619420)
// Draws a highlighted node: thick lines to each branch target (a square on
// the midpoint of a long one), the thick loop line and the outlined marker.
// @ref ?Planning_Draw_Thick_Line@@YIXUPoint2D@@0HH@Z=0061a6a0
// @ref ?Planning_Draw_Midpoint@@YIXUPoint2D@@0H@Z=0061a2f0
#include "shared/planning.hpp"
#include "shared/surface.hpp"
// The coordinate an event without a target reports ((-1, -1, -1)). Hypothesis: a
// default-constructed type whose ctor forwards to CoordStruct's, so the ctor call
// 0x0041B630 stays one inline level down and == reads the temporary directly.
struct Planning_No_Coord : CoordStruct {
    Planning_No_Coord() : CoordStruct(-1, -1, -1) {}
};

// The house colour of a node's first member. Hypothesis: a level of its own, so
// Member_Owner and Techno_Color are depth-two calls at both Draw_Node rows.
inline int Planning_Node_Color(PlanningNodeClass *node)
{
    return Planning_Techno_Color(node->Member_Owner(0));
}

void __fastcall Planning_Draw_Node_619420(PlanningNodeClass *node)
{
    Point2D pixel = node->Pixel();
    int frame = -1;
    if (node->Members.Count() > 0) {
        EventClass event = node->Member_Event(0);
        frame = ((PlanningEventTargets &)event).unknown_61a2d0();
    }
    int color = Planning_Node_Color(node);
    int count = node->Branches.Count();
    for (int index = 0; index < count; index++) {
        CoordStruct coord = node->Branch_Coord(index);
        Point2D start = Planning_Coord_Pixel(coord);
        if (coord == Planning_No_Coord()) {
            PlanningBranchClass *branch = node->Branches[index];
            start = Planning_Event_Pixel(&branch->Event, node->Branch_Owner(index));
        }
        Planning_Draw_Thick_Line(start, pixel, 4, color);
        if (frame != -1) {
            Planning_Draw_Midpoint(start, pixel, color);
        }
    }
    if (node->unknown_6114e0()) {
        CoordStruct coord = node->Own_Branch_Coord();
        Point2D start = Planning_Coord_Pixel(coord);
        if (coord == Planning_No_Coord()) {
            start = Planning_Event_Pixel(&node->Branch.Event, node->First_Counted_Owner());
        }
        Planning_Draw_Thick_Line(start, pixel, 4, color);
        if (frame != -1) {
            Planning_Draw_Midpoint(start, pixel, color);
        }
    }
    node->Draw_Marker(color);
}
