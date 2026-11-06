#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Unknown_00614010() (0x00614010)
// Per-frame planning update, called from the main loop: refreshes the hover,
// drops path nodes whose attack or move target has died, settles the queued
// nodes and shows any pending command refusal.
#include "shared/planning.hpp"

void __fastcall Planning_Hover();   // 0x00615C00

// The two wrappers group real statements. Each moves its statements out of
// the root: the first keeps Planning_Hover a call, the second refuses
// Planning_Refuse at the last refusal arm.
inline void Planning_Update_Hover_00614010()
{
    Planning_Hover();
    if (unknown_node_a766b0 && unknown_objects_a40c60.Count() > 0) {
        unknown_node_a766b0 = 0;
    }
}

inline void Planning_Update_Reset_Flags_00614010()
{
    unknown_flag_a76790 = false;
    unknown_flag_a76788 = false;
    unknown_flag_a766c8 = false;
}

void __fastcall Unknown_00614010()
{
    Planning_Update_Hover_00614010();
    int count = PlanningTokenClass::unknown_list_00a76738.Count();
    for (int index = 0; index < count; ++index) {
        PlanningTokenClass *token = PlanningTokenClass::unknown_list_00a76738[index];
        TechnoClass *owner = token->Owner;
        for (int path_index = token->Nodes.Count() - 1; path_index >= 0; --path_index) {
            PlanningNodeClass *event_node = token->Nodes[path_index];
            EventClass event = event_node->Event_For(token->Owner);
            bool remove = true;
            if (event.Type == 4) {
                if (event.TargetAt(0x0E).Is_Valid()) {
                    remove = event.TargetAt(0x0E).As_Abstract() == 0;
                } else if (event.TargetAt(0x13).Is_Valid()) {
                    remove = event.TargetAt(0x13).As_Abstract() == 0;
                }
            }
            if (!remove) {
                continue;
            }
            PlanningNodeClass *node = token->Node_At(path_index);
            PlanningNodeClass *next_node = node->Next(owner);
            Planning_Queue_Node(next_node);
            token->unknown_6138f0(path_index);
        }
    }
    Planning_Process_Queue();
    int refusal = unknown_a76750;
    if (refusal != -1) {
        Planning_Refuse_Command(refusal);
        unknown_a76750 = -1;
    }
    Planning_Update_Reset_Flags_00614010();
}
