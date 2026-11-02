// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0051FC80@HouseClass@@QAE_NXZ=0051fc80
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?While_Moving_004fcbc0@HoverLocomotionClass@@QAEH_N@Z=004fcbc0
// @ref ?Start_Of_Move_004fe0f0@HoverLocomotionClass@@QAEXH@Z=004fe0f0
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080
// @ref _unknown_geometry_j=00a410a8
#include "shared/hover_locomotion.hpp"
#include "shared/house.hpp"
void __stdcall HoverLocomotionClass::Move_To(CoordStruct to)
{
    unknown_18=to;
    if (LinkedTo->unknown_slot202()) return;
    if (Is_Powered() && Is_Ion_Sensitive() && LinkedTo->House->Unknown_0051FC80()) Power_Off();
    unknown_18.Z=Map.Unknown_0055A280(unknown_18);
    if (Loco_Cell(CoordStruct(to.X,to.Y,to.Z))->Flags&0x100) unknown_18.Z+=unknown_geometry_j;
    if (to!=unknown_coord_a41080 && Is_Powered()) {
        if (!Is_Moving_Now()) {
            LinkedTo->unknown_slot306(1.0);
            Start_Of_Move_004fe0f0(0);
            While_Moving_004fcbc0(true);
        } else if (unknown_24==unknown_coord_a41080) {
            unknown_4fed20();
        }
    }
}
