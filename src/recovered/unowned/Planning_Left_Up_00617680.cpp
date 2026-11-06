#define RA2_COORD_EQUAL_MEMBER
// bool __stdcall Planning_Left_Up_00617680(Point2D point) (0x00617680)
// The left button came up: over the remembered node it ends the drag; over a node of the
// selected paths it is taken; otherwise the remembered node is dropped.
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
// @ref ?Planning_Unknown_617af0@@YAXXZ=00617af0
// @ref ?Planning_Selection_Node_State@@YIHPAVPlanningNodeClass@@@Z=00617a10

void Planning_Unknown_617af0();

bool __stdcall Planning_Left_Up_00617680(Point2D point)
{
    if (!Planning_Is_Active()) {
        return false;
    }
    PlanningNodeClass *remembered = Planning_Get_a766f8();
    PlanningNodeClass *node = Planning_Node_At(point.X, point.Y);
    if (node != 0 && node == remembered) {
        Map.Set_Default_Mouse(0, true);
        Planning_Unknown_617af0();
    } else {
        PlanningNodeClass *picked = Planning_Pick_Node(point.X, point.Y);
        if (picked != 0 && Planning_Selection_Node_State(picked) != -1) {
            return true;
        }
        Planning_Set_a766f8(0);
    }
    return remembered != 0 || node != 0;
}
