#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Draw_Node_619870(PlanningNodeClass *node) (0x00619870)
// Draws a node: the lines to each branch target, the loop line back to the
// first node and the marker; an order with a cursor shape marks each line.
// @ref ?Planning_Draw_Midpoint_Shape@@YIXUPoint2D@@0HHH@Z=0061a3c0
// @ref ?Planning_Draw_Dashed_Thick_Line@@YIXUPoint2D@@0HH@Z=0061a6f0
// @ref ?Branch_Color@PlanningNodeClass@@QAEHH@Z=006127e0
// @ref ?Loop_Color@PlanningNodeClass@@QAEHXZ=006129b0
#include "shared/planning.hpp"
// Uses Planning_No_Coord and Planning_Node_Color from the 0x00619420 row.
void __fastcall Planning_Draw_Midpoint_Shape(Point2D start, Point2D end, int color, int fill, int frame);

void __fastcall Planning_Draw_Node_619870(PlanningNodeClass *node)
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
        int branch_color = node->Branch_Color(index);
        CoordStruct coord = node->Branch_Coord(index);
        Point2D start = Planning_Coord_Pixel(coord);
        if (coord == Planning_No_Coord()) {
            PlanningBranchClass *branch = node->Branches[index];
            start = Planning_Event_Pixel(&branch->Event, node->Branch_Owner(index));
        }
        Planning_Draw_Dashed_Thick_Line(start, pixel, 4, branch_color);
        if (frame != -1) {
            Planning_Draw_Midpoint_Shape(start, pixel, branch_color, color, frame);
        }
    }
    if (node->unknown_6114e0()) {
        int loop_color = node->Loop_Color();
        CoordStruct coord = node->Own_Branch_Coord();
        Point2D start = Planning_Coord_Pixel(coord);
        if (coord == Planning_No_Coord()) {
            TechnoClass *owner = node->First_Counted_Owner();
            start = Planning_Event_Pixel(&node->Branch.Event, owner);
        }
        Planning_Draw_Dashed_Thick_Line(start, pixel, 4, loop_color);
        if (frame != -1) {
            Planning_Draw_Midpoint_Shape(start, pixel, loop_color, color, frame);
        }
    }
    node->Fill_Marker(node->Color());
}
