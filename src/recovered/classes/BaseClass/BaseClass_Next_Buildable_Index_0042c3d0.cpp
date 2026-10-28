// int BaseClass::Next_Buildable_Index(int type) (0x0042C3D0)
// The first node not yet built (of a type, -1 any) or -1. Outside the
// campaign a flagged node is taken only when the house may build it now
// (0x004F64C0), and its cell is reset for a new placement.
#include "shared/base.hpp"
#include "shared/techno.hpp"
// @ref ?unknown_func_4f64c0@HouseClass@@QAE_NABVBaseNodeClass@@@Z=004f64c0

int BaseClass::Next_Buildable_Index(int type)
{
    for (int index = 0; index < Nodes.Count(); index++) {
        if (type == -1) {
            if (!Is_Built(index)) {
                if (unknown_game_mode_a3d298 == 0 || !Nodes[index].unknown_08) {
                    return index;
                }
                if (House->unknown_func_4f64c0(Nodes[index])) {
                    Nodes[index].Cell = unknown_geometry_k;
                    return index;
                }
            }
        } else if (Nodes[index].Type == type && !Is_Built(index)) {
            return index;
        }
    }
    return -1;
}
