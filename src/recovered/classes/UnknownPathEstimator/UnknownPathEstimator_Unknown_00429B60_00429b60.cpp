// UnknownPathEstimator::Unknown_00429B60() (0x00429B60): the subzone search
// (Tiberian Sun's Find_Path_Hierarchical): each layer from the coarsest
// searches the subzone graph inside the corridor the coarser layer found and
// records its subzone path in +0xBC.
#include "shared/path_estimator.hpp"
#include "shared/subzone_tracking.hpp"
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/zone_table.hpp"
// @ref ?Unknown_00567D20@MapClass@@QAEHPAVHouseClass@@HHH@Z=00567d20
// @ref ?Heapify@UnknownPathEstimatorBlock@@QAEXH@Z=0042b560
// @ref _unknown_path_passability_scores_79c4a4=0079c4a4
// The search cost of each passability (0x0079C4A4).
extern "C" float const unknown_path_passability_scores_79c4a4[8];

bool UnknownPathEstimator::Unknown_00429B60(Cell const &from, Cell const &to, int zone, FootClass *foot)
{
    int *pass_table = unknown_table_7e00c4[zone];
    double threat_avoidance = foot != 0 ? foot->unknown_4cafb0() : 0.0;
    HouseClass *house = foot != 0 ? foot->House : 0;
    bool avoid_threats = threat_avoidance > 0.00001;

    for (int layer = 2; layer >= 0; layer--) {
        unknown_68->Clear();

        short *start_subzones = (short *)(Map.unknown_6c + Map.Unknown_0054FAB0(from) * 10);
        int start_subzone = start_subzones[layer];
        short *end_subzones = (short *)(Map.unknown_6c + Map.Unknown_0054FAB0(to) * 10);
        int end_subzone = end_subzones[layer];

        bool is_coarse = layer == 2;
        int *coarser_final_ids;
        if (!is_coarse) {
            coarser_final_ids = unknown_40[layer + 1];
        } else {
            coarser_final_ids = 0;
        }

        int *final_ids = unknown_40[layer];
        int *working_ids = unknown_4c[layer];
        float *costs = (float *)unknown_58[layer];
        final_ids[start_subzone] = unknown_28;
        final_ids[end_subzone] = unknown_28;

        if (start_subzone == end_subzone) {
            if (layer == 0) {
                UnknownPathHierNode *node = &((UnknownPathHierNode *)unknown_64)[0];
                node->Depth = 0;
                node->SubzoneID = start_subzone;
            }
            unknown_bc[layer][0] = start_subzone;
            unknown_c74[layer] = 1;
        } else {
            int node_count = 0;
            UnknownPathHierNode *start_node = &((UnknownPathHierNode *)unknown_64)[0];
            start_node->ParentIndex = -1;
            start_node->SubzoneID = start_subzone;
            start_node->Score = 0.0;
            start_node->Depth = 0;

            unknown_68->Insert(*start_node);
            node_count++;
            working_ids[start_subzone] = unknown_28;
            costs[start_subzone] = 0.0;

            UnknownPathHierNode *best_node = unknown_68->Extract_Min();
            bool no_banned_edges = unknown_74[layer].Count() == 0;

            while (best_node != 0) {
                int from_subzone = best_node->SubzoneID;
                if (from_subzone == end_subzone) {
                    break;
                }

                SubzoneConnectionStruct *connection = &Map.SubzoneTracking[layer][from_subzone].Connections[0];
                int conn_count = Map.SubzoneTracking[layer][from_subzone].Connections.Count();
                for (int conn_idx = 0; conn_idx < conn_count; conn_idx++) {
                    int threat = 0;
                    int to_subzone = connection[conn_idx].unknown_00;
                    bool is_cross_block = connection[conn_idx].unknown_04;
                    int passability = Map.SubzoneTracking[layer][to_subzone].unknown_1c;
                    int to_coarser_subzone = (unsigned short)Map.SubzoneTracking[layer][to_subzone].unknown_18;

                    if (avoid_threats) {
                        threat = Map.Unknown_00567D20(house, layer, from_subzone, to_subzone) * threat_avoidance;
                    }

                    double extra_score = is_cross_block ? 0.001 : 0.0;

                    float score = unknown_path_passability_scores_79c4a4[passability] + best_node->Score + (double)threat + extra_score;

                    if ((working_ids[to_subzone] != unknown_28 || costs[to_subzone] > score) && (is_coarse || coarser_final_ids[to_coarser_subzone] == unknown_28 || passability == 1) && pass_table[passability] == 1) {
                        if (!no_banned_edges) {
                            unsigned short first = from_subzone;
                            unsigned short second = to_subzone;
                            if (second < first) {
                                unsigned short swap = first;
                                first = second;
                                second = swap;
                            }
                            unsigned key = ((unsigned)first << 16) | second;
                            DynamicVectorClass<unsigned int> &list = unknown_74[layer];
                            bool banned = false;
                            for (int index = list.Count() - 1; index >= 0; index--) {
                                if (list[index] == key) {
                                    banned = true;
                                    break;
                                }
                            }
                            if (banned) {
                                continue;
                            }
                        }
                        UnknownPathHierNode *new_node = &((UnknownPathHierNode *)unknown_64)[node_count];
                        new_node->ParentIndex = best_node - (UnknownPathHierNode *)unknown_64;
                        new_node->SubzoneID = to_subzone;
                        new_node->Score = score;
                        new_node->Depth = best_node->Depth + 1;
                        unknown_68->Insert(*new_node);
                        working_ids[to_subzone] = unknown_28;
                        costs[to_subzone] = score;
                        node_count++;
                    }
                }
                best_node = unknown_68->Extract_Min();
            }

            if (best_node == 0) {
                return false;
            }

            UnknownPathHierNode *tail_node = best_node;
            while (best_node->ParentIndex != -1) {
                final_ids[best_node->SubzoneID] = unknown_28;
                best_node = &((UnknownPathHierNode *)unknown_64)[best_node->ParentIndex];
            }

            int path_count = tail_node->Depth + 1;
            unknown_c74[layer] = path_count;
            path_count--;
            while (path_count > 0) {
                unknown_bc[layer][path_count] = tail_node->SubzoneID;
                tail_node = &((UnknownPathHierNode *)unknown_64)[tail_node->ParentIndex];
                path_count--;
            }

            unknown_bc[layer][0] = tail_node->SubzoneID;
        }
    }
    return true;
}
