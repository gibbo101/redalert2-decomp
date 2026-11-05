#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Hover() (0x00615C00)
// The node under the mouse becomes the highlighted node when the player may
// extend it; otherwise it is remembered in unknown_a766fc.
#include "shared/planning.hpp"
#include "shared/mouse.hpp"

void __fastcall Planning_Hover()
{
    if (unknown_flag_a76770) {
        return;
    }
    int x = WWMouse->Get_Mouse_X();
    int y = WWMouse->Get_Mouse_Y();
    PlanningNodeClass *node = Planning_Pick_Drawn(x, y);
    if (node != unknown_node_a7678c) {
        unknown_a766fc = 0;
        if (node != 0) {
            if (node->Member_Owner(0)->House != unknown_player_a35db4
                || (unknown_node_a766f8 != 0 && unknown_node_a766f8 != node)
                || Planning_Selection_Node_State(node) != -1) {
                unknown_a766fc = (int)node;
                node = 0;
            }
        }
        unknown_node_a7678c = node;
        if (node != 0) {
            node->Dump();
        }
    }
}
