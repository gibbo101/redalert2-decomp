#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass *__fastcall Planning_Find_Node(int house, int id, CoordStruct coord) (0x00615FB0)
// The node of unknown_list_00a76628 at a coordinate with the given id
// (-1: any) and house (-1: any).
#include "shared/planning.hpp"

PlanningNodeClass *__fastcall Planning_Find_Node(int house, int id, CoordStruct coord)
{
    int count = PlanningNodeClass::unknown_list_00a76628.Count();
    for (int i = 0; i < count; i++) {
        PlanningNodeClass *node = PlanningNodeClass::unknown_list_00a76628[i];
        CoordStruct here = node->Coord();
        if (here.X == coord.X && here.Y == coord.Y && here.Z == coord.Z && (id == -1 || id == node->unknown_18)) {
            HouseClass *owner_side = node->Members[0]->Owner->House;
            int owner_house = owner_side->ArrayIndex;
            if (owner_side->Unknown_004F52B0() && unknown_player_a35db4) {
                owner_house = unknown_player_a35db4->ArrayIndex;
            }
            if (house == -1 || house == owner_house) {
                return node;
            }
        }
    }
    return 0;
}
