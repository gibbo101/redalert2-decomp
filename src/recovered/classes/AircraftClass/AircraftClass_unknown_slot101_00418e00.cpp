// int AircraftClass::unknown_slot101(int arg1, int arg2, int arg3, int arg4, int arg5) (0x00418E00, slot 101)
// Whether the aircraft may enter cell arg1 (0 yes, 7 no): a team member
// stays within its area (0x0055A740); a cell held by an active non-allied
// object (other than a building with Invisible types, or in some modes)
// must pass the cell's test (0x00478760); and some aircraft (+0x372) avoid
// cells the map rejects (0x00568140) outside game mode 0.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A740@MapClass@@QAE_NPAVCellClass@@_N@Z=0055a740
// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140
// @ref ?Unknown_006BA990@TeamClass@@QAE_NXZ=006ba990
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Unknown_00478760@CellClass@@QAE_NHHHHHHH@Z=00478760
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

int AircraftClass::unknown_slot101(int arg1, int arg2, int arg3, int arg4, int arg5)
{
    CellClass *cell = (CellClass *)arg1;
    if (Team != 0 && Team->Unknown_006BA990() && !Map.Unknown_0055A740(cell, 1)) {
        return 0;
    }
    TechnoClass *occupier = cell->Occupier;
    bool active;
    if (occupier != 0) {
        active = occupier->unknown_14_bit0;
    }
    if ((occupier == 0 || !active || occupier->House->Is_Ally(House)
         || (occupier->unknown_1b8 != 2 && unknown_a40774 == 0
             && (occupier->Kind_Of() != 6 || !((BuildingClass *)occupier)->Type->Invisible)))
        && !cell->Unknown_00478760(4, 0, 0, -1, 0, -1, 1)) {
        return 7;
    }
    if (unknown_game_mode_a3d298 == 0 && unknown_372 && !unknown_32c) {
        if (Map.Unknown_00568140(cell->Center_Coord())) {
            return 7;
        }
    }
    return 0;
}
