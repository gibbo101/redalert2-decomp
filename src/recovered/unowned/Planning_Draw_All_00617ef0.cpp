#define RA2_COORD_EQUAL_MEMBER
// void Planning_Draw_All() (0x00617EF0)
// Draws the planning mode for the player's allies: every node's paths, then
// every node's filled marker, then every planned techno.
#include "shared/planning.hpp"
#include "shared/surface.hpp"
// @ref ?Planning_Draw_Node_619870@@YIXPAVPlanningNodeClass@@@Z=00619870
// @ref ?Planning_Draw_Techno_618c00@@YIXPAVTechnoClass@@@Z=00618c00

// Fills a node marker shrunk by a pixel (file-static helper; hypothesis: the
// original expands one more charged level here, which keeps Planning_Centered_Rect
// and PlanningNodeClass::Coord out of line).
static inline void Planning_Fill_Inner_Marker(PlanningNodeClass *node, int color)
{
    ::Rect view = Unknown_006F1F30();
    ::Rect marker = node->Rect();
    Planning_Inflate(marker, -1);
    unknown_surface_839964->Fill_Rect(view, marker, color);
}

void Planning_Draw_All()
{
    int count = PlanningNodeClass::unknown_list_00a76628.Count();
    int i;
    for (i = 0; i < count; i++) {
        PlanningNodeClass *node = PlanningNodeClass::unknown_list_00a76628[i];
        if (node->House()->Is_Ally(unknown_player_a35db4)) {
            Planning_Draw_Node_619870(node);
        }
    }
    for (i = 0; i < count; i++) {
        PlanningNodeClass *node = PlanningNodeClass::unknown_list_00a76628[i];
        if (node->House()->Is_Ally(unknown_player_a35db4)) {
            Planning_Fill_Inner_Marker(node, node->Color());
        }
    }
    int technos = unknown_list_a40c20.Count();
    for (i = 0; i < technos; i++) {
        TechnoClass *techno = unknown_list_a40c20[i];
        if (techno->House->Is_Ally(unknown_player_a35db4)) {
            Planning_Draw_Techno_618c00(techno);
        }
    }
}
