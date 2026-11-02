// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080
// @ref _unknown_geometry_g=00a410b8
// @ref _unknown_geometry_j=00a410a8
#include "shared/hover_locomotion.hpp"
#include "shared/adjacent_cell.hpp"
inline Cell Hover_Adjacent_Cell_004fea20(Cell const &cell,int facing)
{
    return cell+AdjacentCell[facing&7];
}
bool __stdcall HoverLocomotionClass::Push(UnknownFacingDir dir)
{
    if (Is_Powered() && !unknown_70) {
        int facing=Dir_To_8(dir);
        Cell cell=Hover_Adjacent_Cell_004fea20(LinkedTo->unknown_slot104(),facing);
        FootClass *linked=LinkedTo;
        if (linked->unknown_slot101(&Map[cell],-1,-1,0,true)==0) {
            unknown_70=true;
            if (Is_Moving()) {
                LinkedTo->Path[0]=-1;
                if (unknown_24!=unknown_coord_a41080) LinkedTo->unknown_slot59(unknown_24);
                unknown_24=CoordStruct(cell.X*256+128,cell.Y*256+128,0);
                unknown_24.Z=Map.Unknown_0055A280(unknown_24);
                if (Object_Coord(LinkedTo).Z>=unknown_24.Z+unknown_geometry_g*3) unknown_24.Z+=unknown_geometry_j;
                LinkedTo->unknown_slot58(unknown_24);
            } else {
                Move_To(CoordStruct(cell.X*256+128,cell.Y*256+128,0));
            }
            return true;
        }
    }
    return false;
}
