#define RA2_COORD_EQUAL_MEMBER
// bool __stdcall Planning_Mouse_Move_00617900(int x, int y) (0x00617900)
#include "shared/planning.hpp"
// The game screen as this unit sees it (the full screen headers, shared/mouse_class.hpp
// and shared/map_view.hpp, change the unit's declaration and initializer counts).
struct MouseShapeHeader {
    short unknown_00;
    short Width;
    short Height;
    short FrameCount;
};
class MouseClass {
public:
    virtual void Set_Default_Mouse(int mouse, bool wsmall = false);   // 0x0059F060
    static MouseShapeHeader const *MouseShapes;
};
extern MouseClass Map;                          // 0x008324E0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Set_Default_Mouse@MouseClass@@UAEXH_N@Z=0059f060

bool __stdcall Planning_Mouse_Move_00617900(int x, int y)
{
    if (!unknown_flag_a767a4) {
        return false;
    }
    if (unknown_flag_a76770) {
        return false;
    }
    PlanningNodeClass *remembered = unknown_node_a766f8;
    PlanningNodeClass *node = Planning_Node_At(x, y);
    if (remembered == 0 && node == 0) {
        return false;
    }
    if (remembered == 0 || node == remembered) {
        Map.Set_Default_Mouse(0, true);
    } else {
        Map.Set_Default_Mouse(0, false);
    }
    return true;
}
