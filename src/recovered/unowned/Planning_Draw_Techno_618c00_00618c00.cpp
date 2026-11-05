// void __fastcall Planning_Draw_Techno_618c00(TechnoClass *techno) (0x00618C00)
// The dashed twin of Planning_Draw_Techno: filled dots, dashed lines and mouse-shape
// midpoint markers in the dim house colour; the first queued leg dims or brightens with the path.
// @ref ?Unknown_006F6750@PlanningEventTargets@@SAHXZ=006f6750
// @ref ?Unknown_006F6760@PlanningEventTargets@@SAHXZ=006f6760
// @ref ??8CoordStruct@@QBE_NABU0@@Z=0061a8b0
// @ref ?unknown_owner_color@@YIHPAUUnknownTechno_00610770@@@Z=00610770
// @ref ?Planning_Inflate@@YIXAAVRect@@H@Z=00612570
// @ref ?Planning_Centered_Rect@@YI?AVRect@@UPoint2D@@H@Z=006112d0
// @ref ?Planning_Draw_Dashed_Thick_Line@@YIXUPoint2D@@0HH@Z=0061a6f0
// @ref ?Planning_Draw_Midpoint_Shape@@YIXUPoint2D@@0HHH@Z=0061a3c0
// @ref ?Planning_Fill_Dot@@YIXUPoint2D@@H@Z=0061a210
#include "shared/planning.hpp"
#include "shared/tactical.hpp"
#include "shared/surface.hpp"
void __fastcall Planning_Draw_Midpoint_Shape(Point2D start, Point2D end, int color, int fill, int frame);
struct UnknownTechno_00610770;
int __fastcall unknown_owner_color(UnknownTechno_00610770 *techno);

inline RGBClass Planning_Owner_House_Color(TechnoClass *techno)
{
    int house = unknown_owner_color((UnknownTechno_00610770 *)techno);
    return Houses[house]->unknown_55e9;
}

inline int Planning_House_Pixel(TechnoClass *techno, RGBClass const &target, int ratio)
{
    return Planning_Adjusted_Pixel(Planning_Owner_House_Color(techno), target, ratio);
}

inline bool Planning_Reached(PlanningTokenClass const *token, int slot)
{
    int first = token->unknown_8c;
    if (first == -1) return false;
    return slot >= first;
}

void __fastcall Planning_Draw_Techno_618c00(TechnoClass *techno)
{
    PlanningTokenClass *token = (PlanningTokenClass *)techno->unknown_6d1430();
    CoordStruct current_coord = techno->unknown_slot22();
    Point2D start = Planning_Coord_Pixel(current_coord);
    int dim = Planning_House_Pixel(techno, unknown_rgb_ab6841, 0x50);
    int bright = Planning_House_Pixel(techno, unknown_rgb_ab6849, 100);
    bool has_nodes = (!token ? 0 : token->Nodes.Count()) > 0;
    bool current_order = Planning_Current_Order(techno, has_nodes);
    int dot;
    int thickness = 4;
    int color = Planning_Techno_Color(techno);
    if (token && (token->Owner->Mission == 28 || token->Owner->MissionQueue == 28)) {
        EventClass event = token->Event;
        CoordStruct coord = Planning_Event_Or_Object_Coord(event, techno);
        Point2D end = Planning_Coord_Pixel(coord);
        dot = dim;
        Planning_Fill_Dot(start, dot);
        Planning_Draw_Dashed_Thick_Line(start, end, 3, dot);
        int frame = ((PlanningEventTargets const &)event).unknown_61a2d0();
        if (frame != -1) Planning_Draw_Midpoint_Shape(start, end, dot, color, frame);
        Planning_Fill_Dot(end, dot);
        return;
    }
    if (current_order) {
        bool alternate = techno->unknown_slot270();
        bool secondary = techno->unknown_slot271();
        CoordStruct coord = techno->unknown_slot241();
        Point2D end = Planning_Coord_Pixel(coord);
        if (techno->unknown_76) {
            Planning_Fill_Dot(end, dim);
            return;
        }
        Planning_Fill_Dot(start, dim);
        Planning_Draw_Dashed_Thick_Line(start, end, 3, dim);
        int frame = -1;
        if (!alternate || secondary) {
            if (techno->unknown_slot91() == 11) frame = PlanningEventTargets::Unknown_006F6760();
        } else if (techno->unknown_slot272() == 29) frame = PlanningEventTargets::Unknown_006F6750();
        if (frame != -1) Planning_Draw_Midpoint_Shape(start, end, dim, color, frame);
        Planning_Fill_Dot(end, dim);
        if (secondary) {
            CoordStruct next_coord = techno->unknown_slot273();
            Point2D next = Planning_Coord_Pixel(next_coord);
            Planning_Draw_Dashed_Thick_Line(end, next, 3, dim);
            if (techno->unknown_slot272() == 29) {
                frame = PlanningEventTargets::Unknown_006F6750();
                if (frame != -1) Planning_Draw_Midpoint_Shape(end, next, dim, color, frame);
            }
            Planning_Fill_Dot(next, dim);
            return;
        }
        if (!has_nodes) return;
        start = end;
        thickness = 3;
    } else if (!has_nodes) {
        return;
    }
    {
        PlanningNodeClass *node = token->Node_At(0);
        Point2D end = node->Pixel();
        PlanningBranchClass *branch = node->Branch_For(techno);
        if (branch) end = Planning_Event_Pixel(&branch->Event, techno);
        dot = Planning_Reached(token, 0) ? bright : dim;
        Planning_Fill_Dot(start, dot);
        Planning_Draw_Dashed_Thick_Line(start, end, thickness, dot);
        if (branch) Planning_Fill_Dot(end, dot);
        EventClass event = node->Event_For(techno);
        int frame = ((PlanningEventTargets const &)event).unknown_61a2d0();
        if (frame != -1) Planning_Draw_Midpoint_Shape(start, end, dot, color, frame);
    }
}
