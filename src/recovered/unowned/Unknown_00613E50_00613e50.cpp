#define RA2_COORD_EQUAL_MEMBER
// void Unknown_00613E50() (0x00613E50; Planning_Shutdown 0x00613E40's tail jump)
// Tears the planning mode down: deletes every planning token (the lists are
// marked as being torn down so the tokens do not unlist themselves), empties
// the planning lists and counters and forgets the remembered state.
#include "shared/planning.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_flag_a767a5@@3_NA=00a767a5
// @ref ?unknown_flag_a767a4@@3_NA=00a767a4
// @ref ?unknown_flag_a767a6@@3_NA=00a767a6
// @ref ?unknown_counts_a76684@@3PAHA=00a76684
// @ref ?unknown_counts_a766b4@@3PAHA=00a766b4
// @ref ?unknown_node_a7678c@@3PAVPlanningNodeClass@@A=00a7678c
// @ref ?unknown_flag_a76788@@3_NA=00a76788
// @ref ?unknown_flag_a766c8@@3_NA=00a766c8
// @ref ?unknown_a766fc@@3HA=00a766fc
// @ref ?unknown_flag_a76790@@3_NA=00a76790
// @ref ?unknown_a76750@@3HA=00a76750

// The node lists, emptied together (expanded inline).
static inline void Clear_Node_Lists()
{
    PlanningNodeClass::unknown_list_00a76628.Clear();
    PlanningNodeClass::unknown_list_00a766d8.Clear();
}

void Unknown_00613E50()
{
    int count = PlanningTokenClass::unknown_list_00a76738.Count();
    unknown_flag_a767a5 = true;
    unknown_flag_a767a4 = false;
    unknown_flag_a767a6 = false;
    for (int i = 0; i < count; i++) {
        PlanningTokenClass *token = PlanningTokenClass::unknown_list_00a76738[i];
        delete token;
    }
    memset(unknown_counts_a76684, 0, sizeof(unknown_counts_a76684));
    PlanningLists::unknown_list_00a76700.Clear();
    PlanningTokenClass::unknown_list_00a76738.Clear();
    Clear_Node_Lists();
    unknown_node_a7678c = 0;
    unknown_flag_a76790 = false;
    unknown_flag_a76788 = false;
    unknown_a766fc = 0;
    unknown_flag_a766c8 = false;
    unknown_flag_a767a5 = false;
    unknown_a76750 = -1;
    memset(unknown_counts_a766b4, 0, 5 * sizeof(int));
}
