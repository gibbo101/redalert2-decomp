// void SidebarClass::unknown_slot50() (0x0067BFC0, slot 50)
// Frees the allocated sidebar shapes and the buttons' shapes.
#include "shared/sidebar.hpp"
// @ref ?unknown_slot50@PowerClass@@UAEXXZ=0061c580
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_shapes_abcd20@@3PAPBXA=00abcd20
// @ref ?unknown_shapes_allocated_abcd40@@3PA_NA=00abcd40
// @ref ?Free_Shape@ShapeButtonClass@@QAEXXZ=006751a0

void SidebarClass::unknown_slot50()
{
    PowerClass::unknown_slot50();
    if (unknown_shapes_allocated_abcd40[0]) {
        operator delete((void *)unknown_shapes_abcd20[0]);
        unknown_shapes_allocated_abcd40[0] = false;
    }
    if (unknown_shapes_allocated_abcd40[1]) {
        operator delete((void *)unknown_shapes_abcd20[1]);
        unknown_shapes_allocated_abcd40[1] = false;
    }
    if (unknown_shapes_allocated_abcd40[2]) {
        operator delete((void *)unknown_shapes_abcd20[2]);
        unknown_shapes_allocated_abcd40[2] = false;
    }
    if (unknown_shapes_allocated_abcd40[3]) {
        operator delete((void *)unknown_shapes_abcd20[3]);
        unknown_shapes_allocated_abcd40[3] = false;
    }
    if (unknown_shapes_allocated_abcd40[4]) {
        operator delete((void *)unknown_shapes_abcd20[4]);
        unknown_shapes_allocated_abcd40[4] = false;
    }
    if (unknown_shapes_allocated_abcd40[5]) {
        operator delete((void *)unknown_shapes_abcd20[5]);
        unknown_shapes_allocated_abcd40[5] = false;
    }
    if (unknown_shapes_allocated_abcd40[6]) {
        operator delete((void *)unknown_shapes_abcd20[6]);
        unknown_shapes_allocated_abcd40[6] = false;
    }
    if (unknown_shapes_allocated_abcd40[7]) {
        operator delete((void *)unknown_shapes_abcd20[7]);
        unknown_shapes_allocated_abcd40[7] = false;
    }
    unknown_button_ab96b8.Free_Shape();
    unknown_button_abcc58.Free_Shape();
    for (int index = 0; index < 4; index++) {
        unknown_buttons_ab9508[index].Free_Shape();
    }
    unknown_button_abcbe8.Free_Shape();
    unknown_button_abccc0.Free_Shape();
}
