// UnknownPathEstimator::Unknown_0042A840() (0x0042A840): records the subzone
// pairs around a subzone's step on a layer's +0xBC path.
#include "shared/path_estimator.hpp"
#include "shared/map_view.hpp"
#include "shared/subzone_tracking.hpp"
// @ref ?Add@?$DynamicVectorClass@I@@QAE_NABI@Z=0042b0f0

void UnknownPathEstimator::Unknown_0042A840(unsigned subzone, int layer)
{
    int count = unknown_c74[layer];
    if (count <= 1) {
        unknown_38 = false;
        return;
    }
    int found = -1;
    for (int index = 0; index < count; index++) {
        if (unknown_bc[layer][index] == subzone) {
            found = index;
            break;
        }
    }
    if (found == -1) {
        unknown_38 = false;
    } else {
        unsigned short second;
        unsigned short first;
        if (found == count - 1) {
            second = unknown_bc[layer][found];
            first = unknown_bc[layer][found - 1];
        } else {
            second = unknown_bc[layer][found + 1];
            first = unknown_bc[layer][found];
        }
        Unknown_0042A7D0(second, first, layer);
        DynamicVectorClass<SubzoneConnectionStruct> &to = Map.SubzoneTracking[layer][second].Connections;
        DynamicVectorClass<SubzoneConnectionStruct> &from = Map.SubzoneTracking[layer][first].Connections;
        for (int other = to.Count() - 1; other >= 0; other--) {
            unsigned short next = to[other].unknown_00;
            if (next != first) {
                for (int index = from.Count() - 1; index >= 0; index--) {
                    if (from[index].unknown_00 == next) {
                        Unknown_0042A7D0(first, next, layer);
                    }
                }
            }
        }
    }
}
