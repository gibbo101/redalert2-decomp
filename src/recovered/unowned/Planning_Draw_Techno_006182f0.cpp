// void __fastcall Planning_Draw_Techno(TechnoClass *techno) (0x006182F0)
// Draws one techno's current order and its first queued planning waypoint: dots,
// a thick line to the destination and a midpoint marker when the leg has an event.
// @ref ?Unknown_006F6750@PlanningEventTargets@@SAHXZ=006f6750
// @ref ?Unknown_006F6760@PlanningEventTargets@@SAHXZ=006f6760
// @ref ??8CoordStruct@@QBE_NABU0@@Z=0061a8b0
// @ref ?Planning_Draw_Dot@@YIXUPoint2D@@H@Z=0061a190
// @ref ?Planning_Centered_Rect@@YI?AVRect@@UPoint2D@@H@Z=006112d0
// @ref ?Planning_Draw_Thick_Line@@YIXUPoint2D@@0HH@Z=0061a6a0
// @ref ?Planning_Draw_Midpoint@@YIXUPoint2D@@0H@Z=0061a2f0
// @ref ??GPoint2D@@QBE?AU0@ABU0@@Z=0047d040
#include "shared/planning.hpp"
#include "shared/tactical.hpp"
#include "shared/surface.hpp"
bool __fastcall Planning_Idle_Mover(TechnoClass *techno);

inline bool Planning_Current_Order(TechnoClass *techno, bool has_nodes)
{
    return techno->unknown_slot91() != 5 && !Planning_Idle_Mover(techno) && (has_nodes || techno->unknown_77);
}

void __fastcall Planning_Draw_Techno(TechnoClass *techno)
{
    PlanningTokenClass *token = (PlanningTokenClass *)techno->unknown_6d1430();
    CoordStruct current_coord = techno->unknown_slot22();
    Point2D start = Planning_Coord_Pixel(current_coord);
    int color = Planning_Techno_Color(techno);
    bool has_nodes = (!token ? 0 : token->Nodes.Count()) > 0;
    bool current_order = Planning_Current_Order(techno, has_nodes);
    int thickness = 4;
    if (token && (token->Owner->Mission == 28 || token->Owner->MissionQueue == 28)) {
        EventClass event = token->Event;
        CoordStruct coord = Planning_Event_Or_Object_Coord(event, techno);
        Point2D end = Planning_Coord_Pixel(coord);
        Planning_Draw_Dot(start, color);
        Planning_Draw_Thick_Line(start, end, 3, color);
        if (((PlanningEventTargets const &)event).unknown_61a2d0() != -1) Planning_Draw_Midpoint(start, end, color);
        Planning_Draw_Dot(end, color);
        return;
    }
    if (current_order) {
        bool alternate = techno->unknown_slot270();
        bool secondary = techno->unknown_slot271();
        CoordStruct coord = techno->unknown_slot241();
        Point2D end = Planning_Coord_Pixel(coord);
        if (techno->unknown_76) {
            Planning_Draw_Dot(end, color);
            return;
        }
        Planning_Draw_Dot(start, color);
        Planning_Draw_Thick_Line(start, end, 3, color);
        int action = -1;
        if (!alternate || secondary) {
            if (techno->unknown_slot91() == 11) action = PlanningEventTargets::Unknown_006F6760();
        } else if (techno->unknown_slot272() == 29) action = PlanningEventTargets::Unknown_006F6750();
        if (action != -1) Planning_Draw_Midpoint(start, end, color);
        Planning_Draw_Dot(end, color);
        if (secondary) {
            CoordStruct next_coord = techno->unknown_slot273();
            Point2D next = Planning_Coord_Pixel(next_coord);
            Planning_Draw_Thick_Line(end, next, 3, color);
            if (techno->unknown_slot272() == 29 && PlanningEventTargets::Unknown_006F6750() != -1)
                Planning_Draw_Midpoint(end, next, color);
            Planning_Draw_Dot(next, color);
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
        Planning_Draw_Dot(start, color);
        Planning_Draw_Thick_Line(start, end, thickness, color);
        if (branch) Planning_Draw_Dot(end, color);
        EventClass event = node->Event_For(techno);
        if (((PlanningEventTargets const &)event).unknown_61a2d0() != -1)
            Planning_Draw_Midpoint(start, end, color);
    }
}
